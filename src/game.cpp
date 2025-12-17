#include "game.h"

#include "player.h"
#include "enemy_spawner.h"
#include "screen.h"

namespace game
{
	static bool isRunning = true;
	static Color backgroundColor = BLACK;
	static float deltaTime = 0.f;

	static const int enemyNormalPlanePoolSize = 30;
	//etc

	namespace objects
	{
		static player::Player player;
		static enemyNormalPlane::EnemyNormalPlane enemyNormalPlanes[enemyNormalPlanePoolSize];
	}

	static void game();
	static void init();
	static void loop();
	static void update();
	static void draw();
	static void deinit();
	static void updateEnemies(const player::Player player);
	static void drawEnemies();
	static void handleCollisions();

	void runGame()
	{
		game();
	}

	static void game()
	{
		init();

		loop();

		deinit();
	}

	static void init()
	{
		objects::player = player::init();

		for (int i = 0; i < enemyNormalPlanePoolSize; i++)
		{
			objects::enemyNormalPlanes[i] = enemyNormalPlane::init();
		}

		screen::openWindow();
	}

	static void loop()
	{
		while (!WindowShouldClose() && isRunning)
		{
			deltaTime = GetFrameTime();
			update();
			draw();
		}
	}

	static void update()
	{
		player::update(objects::player, deltaTime);
		enemySpawner::update(objects::enemyNormalPlanes, enemyNormalPlanePoolSize, deltaTime);
		updateEnemies(objects::player);
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

	static void deinit()
	{
		screen::closeWindow();
	}

	static void updateEnemies(const player::Player player)
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
