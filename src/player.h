#pragma once

#include "bullet.h"

namespace player
{
	static const int maxBulletsPool = 50;
	struct Player
	{
		static Sound explosion;

		bool isAlive = true;

		shape::Rectangle hitBox = {};

		Vector2 dir = {};
		float speed = 0.f;
		float damage = 0.f;
		float hp = 0.f;
		float score = 0.f;
		static Texture2D sprite;

		float lowHpCooldown;
		static Sound lowHpSound;
		
		bullet::Bullet bullets[maxBulletsPool];
		float shootCooldown = 0.f;

		Color color = WHITE;
	};

	Player init();
	void deinit();
	void update(Player& player, float deltaTime);
	void draw(Player player);
	void onHit(Player& player, const float damage);
	void onCrash(Player& player);
	void scoreAddHit(Player& player);
	void scoreAddKill(Player& player);
}

