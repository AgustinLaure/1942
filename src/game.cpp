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

		enemySpawner::update(objects::enemyNormalPlanes, enemyNormalPlanePoolSize, deltaTime);

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
}
