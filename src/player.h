#pragma once

#include "bullet.h"

namespace player
{
	static const int maxBulletsPool = 50;
	struct Player
	{
		shape::Rectangle hitBox;

		Vector2 dir = {};
		float speed = 0.f;
		float damage = 0.f;
		float hp = 0.f;
		
		bullet::Bullet bullets[maxBulletsPool];
		float shootCooldown = 0.f;

		Color color;
	};

	Player init();
	void update(Player& player, float deltaTime);
	void draw(Player player);
}

