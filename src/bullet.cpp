#include "bullet.h"

#include "raymath.h"

#include "screen.h"

namespace bullet
{
	static void move(Bullet& bullet, const float delta);
	static void checkOutBounds(Bullet& bullet);

	Bullet init(const BulletPreset preset, const Vector2 dir)
	{
		Bullet newBullet;

		newBullet.isAlive = false;
		newBullet.hitBox = preset.hitBox;
		newBullet.dir = dir;
		newBullet.speed = preset.speed;
		newBullet.color = preset.color;

		return newBullet;
	}

	void update(Bullet& bullet, const float delta)
	{
		move(bullet, delta);
	}

	void draw(const Bullet bullet)
	{
		DrawRectangle(static_cast<int>(bullet.hitBox.pos.x), static_cast<int>(bullet.hitBox.pos.y), static_cast<int>(bullet.hitBox.width), static_cast<int>(bullet.hitBox.height), bullet.color);
	}

	void shoot(Bullet& bullet, const Vector2 pos ,const Vector2 dir)
	{
		bullet.hitBox.pos = { pos.x - bullet.hitBox.width / 2, pos.y - bullet.hitBox.height/2 };
		bullet.dir = dir;
		bullet.isAlive = true;
	}

	void onCollision(Bullet& bullet)
	{
		bullet.isAlive = false;
	}

	static void move(Bullet& bullet, const float delta)
	{
		bullet.hitBox.pos += bullet.dir * bullet.speed * delta;

		checkOutBounds(bullet);
	}

	static void checkOutBounds(Bullet& bullet)
	{
		Vector2 bulletCenter = { bullet.hitBox.pos.x + bullet.hitBox.width / 2, bullet.hitBox.pos.y + bullet.hitBox.height / 2 };

		if (screen::isPointOutScreen(bulletCenter))
		{
			bullet.isAlive = false;
		}
	}
}
