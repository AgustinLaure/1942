#pragma once

#include "shape.h"

namespace player
{
	struct Player
	{
		shape::Rectangle hitBox;

		Vector2 dir = {};
		float speed = 0.f;
		float damage = 0.f;
		float hp = 0.f;

		Color color;
	};

	Player init();
	void update(Player& player, float deltaTime);
	void draw(const Player player);
}

