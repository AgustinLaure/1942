#pragma once

#include "raylib.h"

#include "shape.h"

namespace bullet
{
	struct Bullet
	{
		bool isAlive;
		shape::Rectangle hitBox;
		Vector2 dir;
		float speed;
		Color color;
	};

	enum class BulletType
	{
		Normal
	};

	struct BulletPreset
	{
		shape::Rectangle hitBox;
		float speed;
		Color color;
	};

	static const int maxBulletPresets = 1;
	const BulletPreset bulletPresets[maxBulletPresets] =
	{
		{ //Normal

		{				//Hitbox
			10.f,		//Width
			5.f,		//Height
			{0.f,0.f}	//Pos
		},
		650.f,			//Speed
		WHITE			//Color
		}
	};

	Bullet init(const BulletPreset preset, const Vector2 dir);
	void update(Bullet& bullet, const float delta);
	void draw(const Bullet bullet);
	void shoot(Bullet& bullet, const Vector2 pos, const Vector2 dir);
	void onCollision(Bullet& bullet);
}

