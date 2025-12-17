#pragma once

#include <string>

#include "raylib.h"

#include "shape.h"

namespace bullet
{
	struct Bullet
	{
		static Sound impact;

		bool isAlive = false;
		shape::Rectangle hitBox = {};
		Vector2 dir = {};
		float speed = 0.f;
		float damage = 0.f;
		Color color = WHITE;
		static Texture2D sprite;
	};

	enum class BulletType
	{
		Normal,
		Slow
	};

	struct BulletPreset
	{
		shape::Rectangle hitBox;
		float speed;
		float damage;
		Color color;
	};

	static const int maxBulletPresets = 2;
	const BulletPreset bulletPresets[maxBulletPresets] =
	{
		{ //Normal

		{										//Hitbox
			5.f,								//Width
			10.f,								//Height
			{0.f,0.f}							//Pos
		},
		650.f,									//Speed
		1.f,
		WHITE,									//Color
		},
		{ //Slow

		{										//Hitbox
			5.f,								//Width
			10.f,								//Height
			{0.f,0.f}							//Pos
		},
		300.f,									//Speed
		1.f,
		WHITE,									//Color
		}

	};

	Bullet init(const BulletPreset preset, const Vector2 dir);
	void deinit();
	void update(Bullet& bullet, const float delta);
	void draw(Bullet& bullet);
	void shoot(Bullet& bullet, const Vector2 pos, const Vector2 dir);
	void onCollision(Bullet& bullet);
}

