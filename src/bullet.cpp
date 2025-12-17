#include "bullet.h"

#include "raymath.h"

#include "screen.h"
#include "renderer.h"

namespace bullet
{
	Texture2D Bullet::sprite;

	static void move(Bullet& bullet, const float delta);
	static void checkOutBounds(Bullet& bullet);
	static void die(Bullet& bullet);

	Bullet init(const BulletPreset preset, const Vector2 dir)
	{
		if (!IsTextureValid(Bullet::sprite))
		{
			Bullet::sprite = LoadTexture(preset.spriteRoute.c_str());
		}

		Bullet newBullet;

		newBullet.isAlive = false;
		newBullet.hitBox = preset.hitBox;
		newBullet.dir = dir;
		newBullet.speed = preset.speed;
		newBullet.damage = preset.damage;
		newBullet.color = preset.color;

		return newBullet;
	}

	void deinit()
	{
		UnloadTexture(Bullet::sprite);
	}

	void update(Bullet& bullet, const float delta)
	{
		if (bullet.isAlive)
		{
			move(bullet, delta);
		}
	}

	void draw(Bullet& bullet)
	{
		if (bullet.isAlive)
		{
			DrawRectangle(static_cast<int>(bullet.hitBox.pos.x), static_cast<int>(bullet.hitBox.pos.y), static_cast<int>(bullet.hitBox.width), static_cast<int>(bullet.hitBox.height), bullet.color);
			renderer::drawSprite(bullet.sprite, bullet.hitBox, bullet.color);
		}
	}

	void shoot(Bullet& bullet, const Vector2 pos, const Vector2 dir)
	{
		bullet.hitBox.pos = { pos.x - bullet.hitBox.width / 2, pos.y - bullet.hitBox.height / 2 };
		bullet.dir = dir;
		bullet.isAlive = true;
	}

	void onCollision(Bullet& bullet)
	{
		die(bullet);
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

	static void die(Bullet& bullet)
	{
		bullet.isAlive = false;
	}
}
