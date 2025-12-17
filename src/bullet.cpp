#include "bullet.h"

#include "raymath.h"

#include "screen.h"

namespace bullet
{
	Texture2D Bullet::sprite;
	Sound Bullet::impact;

	static const std::string spriteRoute = "res/sprites/bullet/bullet.png";
	static const std::string impactRoute = "res/sounds/sfx/bullet/impact.wav";

	static const float impactVolumeScale = 0.2f;

	static void move(Bullet& bullet, const float delta);
	static void checkOutBounds(Bullet& bullet);
	static void die(Bullet& bullet);

	Bullet init(const BulletPreset preset, const Vector2 dir)
	{
		if (!IsTextureValid(Bullet::sprite))
		{
			Bullet::sprite = LoadTexture(spriteRoute.c_str());
		}
		if (!IsSoundValid(Bullet::impact))
		{
			Bullet::impact = LoadSound(impactRoute.c_str());
			SetSoundVolume(Bullet::impact, impactVolumeScale);
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
		if (IsTextureValid(Bullet::sprite))
		{
			UnloadTexture(Bullet::sprite);
		}

		if (IsSoundValid(Bullet::impact))
		{
			UnloadSound(Bullet::impact);
		}
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
		PlaySound(Bullet::impact);
	}
}
