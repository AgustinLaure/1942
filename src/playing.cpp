#include "playing.h"

#include "player.h"
#include "enemy_spawner.h"
#include "screen.h"

namespace playing
{
	static Color backgroundColor = BLACK;

	static const int enemyNormalPlanePoolSize = 30;

	namespace objects
	{
		static player::Player player;
		static enemyNormalPlane::EnemyNormalPlane enemyNormalPlanes[enemyNormalPlanePoolSize];
	}

	static void update(const float deltaTime);
	static void draw();
	static void updateEnemies(const player::Player player, const float deltaTime);
	static void drawEnemies();
	static void handleCollisions();

	void playing(const float deltaTime)
	{
		update(deltaTime);
		draw();
	}

	void init()
	{
		playing::objects::player = player::init();

		for (int i = 0; i < enemyNormalPlanePoolSize; i++)
		{
			objects::enemyNormalPlanes[i] = enemyNormalPlane::init();
		}

		screen::openWindow();
	}

	void deinit()
	{

	}

	static void update(const float deltaTime)
	{
		player::update(objects::player, deltaTime);
		enemySpawner::update(objects::enemyNormalPlanes, enemyNormalPlanePoolSize, deltaTime);
		updateEnemies(objects::player, deltaTime);
		handleCollisions();
	}

	static void draw()
	{
		BeginDrawing();
		ClearBackground(backgroundColor);

		player::draw(objects::player);
		drawEnemies();

		EndDrawing();
	}

	static void updateEnemies(const player::Player player, const float deltaTime)
	{
		for (int i = 0; i < enemyNormalPlanePoolSize; i++)
		{
			enemyNormalPlane::update(objects::enemyNormalPlanes[i], player, deltaTime);
		}
	}

	static void drawEnemies()
	{
		for (int i = 0; i < enemyNormalPlanePoolSize; i++)
		{
			enemyNormalPlane::draw(objects::enemyNormalPlanes[i]);
		}
	}

	static void handleCollisions()
	{
		//Player bullets to enemy

		for (int i = 0; i < enemyNormalPlanePoolSize; i++)
		{
			enemyNormalPlane::EnemyNormalPlane* currentEnemyNormalPlane = &objects::enemyNormalPlanes[i];

			//Self bullets to player
			for (int j = 0; j < enemyNormalPlane::maxBulletsPool; j++)
			{
				bullet::Bullet* currentBullet = &currentEnemyNormalPlane->bullets[j];

				if (currentBullet->isAlive)
				{
					if (shape::isRectOnRect(objects::player.hitBox, currentBullet->hitBox))
					{
						player::onHit(objects::player, currentBullet->damage);
						bullet::onCollision(*currentBullet);
					}
				}
			}

			if (currentEnemyNormalPlane->isAlive)
			{
				//Self to player bullets

				for (int j = 0; j < player::maxBulletsPool; j++)
				{
					bullet::Bullet* currentBullet = &objects::player.bullets[j];

					if (currentBullet->isAlive)
					{
						if (shape::isRectOnRect(currentEnemyNormalPlane->hitBox, currentBullet->hitBox))
						{
							enemyNormalPlane::onHit(*currentEnemyNormalPlane, currentBullet->damage);
							bullet::onCollision(*currentBullet);
						}
					}
				}

				//Self to player

				if (shape::isRectOnRect(currentEnemyNormalPlane->hitBox, objects::player.hitBox))
				{
					player::onCrash(objects::player);
					enemyNormalPlane::onCrash(*currentEnemyNormalPlane);
				}
			}
		}
	}
}
