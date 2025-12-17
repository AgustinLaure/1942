#pragma once

#include "enemies.h"

namespace enemySpawner
{
	const float constInitialEnemySpawnCooldown = 0.3f;
	static float enemySpawnCooldown = constInitialEnemySpawnCooldown;

	void update(enemyNormalPlane::EnemyNormalPlane enemyNormalPlanes[], const int enemyNormalPlanePoolSize, const float deltaTime);
}

