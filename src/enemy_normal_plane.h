#pragma once

#include "bullet.h"
#include "player.h"

namespace enemyNormalPlane
{
	const float constWidth = 50.f;

	static const int maxBulletsPool = 50;
	struct EnemyNormalPlane
	{
		static Sound explosion;

		bool isAlive = false;

		shape::Rectangle hitBox = {};

		Vector2 dir = {};
		float speed = 0.f;
		float damage = 0.f;
		float hp = 0.f;

		bullet::Bullet bullets[maxBulletsPool] = {};
		float shootCooldown = 0.f;

		static Texture2D sprite;

		Color color = WHITE;
	};

	EnemyNormalPlane init();
	void deinit();
	void update(EnemyNormalPlane& plane, const player::Player player, const float deltaTime);
	void draw(EnemyNormalPlane& plane);
	void launch(EnemyNormalPlane& plane, const Vector2 pos, const Vector2 dir);
	void onHit(EnemyNormalPlane& plane, const float damage);
	void onCrash(EnemyNormalPlane& plane);
}

