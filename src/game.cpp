#include "game.h"

//const float EPSILON = 0.00001f;

#include "player.h"
#include "enemy_normal_plane.h"
#include "screen.h"

#include "raymath.h"

namespace game
{
	static bool isRunning = true;
	static Color backgroundColor = BLACK;
	static float deltaTime = 0.f;

	const float constInitialEnemySpawnCooldown = 0.3f;
	static float enemySpawnCooldown = constInitialEnemySpawnCooldown;

	//Enemies
	static const int enemyTypes = 1;
	enum class EnemyTypes
	{
		Normal
	};

	static const int enemyNormalPlanePoolSize = 30;
	//etc

	static const Vector2 constEnemyDir = { 0.f, 1.f };

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

	static void spawnEnemy();
	static void launchEnemyNormalPlane(const Vector2 chosenPos);
	static Vector2 getEnemySpawnPos(const float planeWidth);

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

		enemySpawnCooldown -= deltaTime;

		if (enemySpawnCooldown < EPSILON)
		{
			spawnEnemy();
			enemySpawnCooldown = constInitialEnemySpawnCooldown;
		}

		updateEnemies(objects::player);
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
			if (objects::enemyNormalPlanes[i].isAlive)
			{
				enemyNormalPlane::update(objects::enemyNormalPlanes[i], player, deltaTime);
			}
		}
	}

	static void drawEnemies()
	{
		for (int i = 0; i < enemyNormalPlanePoolSize; i++)
		{
			if (objects::enemyNormalPlanes[i].isAlive)
			{
				enemyNormalPlane::draw(objects::enemyNormalPlanes[i]);
			}
		}
	}

	static void spawnEnemy()
	{
		EnemyTypes chosenType = static_cast<EnemyTypes>(GetRandomValue(0, enemyTypes-1));

		switch (chosenType)
		{
		case game::EnemyTypes::Normal:
			launchEnemyNormalPlane(getEnemySpawnPos(enemyNormalPlane::constWidth));
			break;

		default:

			break;
		}
	}

	static void launchEnemyNormalPlane(const Vector2 chosenPos)
	{
		enemyNormalPlane::EnemyNormalPlane* availablePlane = nullptr;

		for (int i = 0; i < enemyNormalPlanePoolSize; i++)
		{
			if (!objects::enemyNormalPlanes[i].isAlive)
			{
				availablePlane = &objects::enemyNormalPlanes[i];
				break;
			}
		}

		enemyNormalPlane::launch(*availablePlane, chosenPos, constEnemyDir);
	}

	static Vector2 getEnemySpawnPos(const float planeWidth)
	{
		return { static_cast<float>(GetRandomValue(static_cast<int>(planeWidth), screen::width - static_cast<int>(planeWidth))), 1.f };
	}
}
