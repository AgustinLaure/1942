#include "enemy_spawner.h"

#include "screen.h"

const float EPSILON = 0.00001f;

namespace enemySpawner
{
	static const float constInitialEnemySpawnCooldown = 1.f;
	static float enemySpawnCooldown = constInitialEnemySpawnCooldown;

	static const Vector2 constEnemyDir = { 0.f, 1.f };

	static void spawnEnemy(enemyNormalPlane::EnemyNormalPlane enemyNormalPlanes[], const int enemyNormalPlanePoolSize);
	static void launchEnemyNormalPlane(enemyNormalPlane::EnemyNormalPlane enemyNormalPlanes[], const int enemyNormalPlanePoolSize, const Vector2 chosenPos);
	static Vector2 getEnemySpawnPos(const float planeWidth);

	void update(enemyNormalPlane::EnemyNormalPlane enemyNormalPlanes[], const int enemyNormalPlanePoolSize, const float deltaTime)
	{
		enemySpawnCooldown -= deltaTime;

		if (enemySpawnCooldown < EPSILON)
		{
			spawnEnemy(enemyNormalPlanes, enemyNormalPlanePoolSize);
			enemySpawnCooldown = constInitialEnemySpawnCooldown;
		}
	}

	static void spawnEnemy(enemyNormalPlane::EnemyNormalPlane enemyNormalPlanes[], const int enemyNormalPlanePoolSize)
	{
		enemies::EnemyTypes chosenType = static_cast<enemies::EnemyTypes>(GetRandomValue(0, enemies::enemyTypes - 1));

		switch (chosenType)
		{
		case enemies::EnemyTypes::Normal:
			launchEnemyNormalPlane(enemyNormalPlanes, enemyNormalPlanePoolSize, getEnemySpawnPos(enemyNormalPlane::constWidth));
			break;

		default:

			break;
		}
	}

	static void launchEnemyNormalPlane(enemyNormalPlane::EnemyNormalPlane enemyNormalPlanes[] , const int enemyNormalPlanePoolSize, const Vector2 chosenPos)
	{
		enemyNormalPlane::EnemyNormalPlane* availablePlane = nullptr;

		for (int i = 0; i < enemyNormalPlanePoolSize; i++)
		{
			if (!enemyNormalPlanes[i].isAlive)
			{
				availablePlane = &enemyNormalPlanes[i];
				break;
			}
		}

		enemyNormalPlane::launch(*availablePlane, chosenPos, constEnemyDir);
	}

	static Vector2 getEnemySpawnPos(const float planeWidth)
	{
		return { static_cast<float>(GetRandomValue(static_cast<int>(planeWidth), screen::width - static_cast<int>(planeWidth))), 1.f };
	}

	void reset()
	{
		enemySpawnCooldown = constInitialEnemySpawnCooldown;
	}
}