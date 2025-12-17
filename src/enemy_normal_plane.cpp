#include "enemy_normal_plane.h"

#include "raymath.h"

#include "screen.h"
#include "renderer.h"

namespace enemyNormalPlane
{
	Texture2D EnemyNormalPlane::sprite;
	Sound EnemyNormalPlane::explosion;

	//Config
	static const float constHeight = 30.f;
	static const float constBulletSpawnOffset = 10.f;

	static const float constInitialSpeed = 200.f;
	static const float constInitialDamage = 1.f;
	static const float constInitialHp = 2.f;
	static const Color constInitialColor = WHITE;
	static const float constInitialShootcooldown = 0.5f;
	static const float constInitialShootImprecision = 1.f; //Degrees
	static const float constInitialCrashDamage = 3.f;

	//Sound
	static const float explosionVolumeScale = 0.3f;

	static const std::string spriteRoute = "res/sprites/enemies/normal_enemy.png";
	static const std::string explosionRoute = "res/sounds/sfx/enemy/explosion.wav";

	EnemyNormalPlane init()
	{
		if (!IsTextureValid(EnemyNormalPlane::sprite))
		{
			EnemyNormalPlane::sprite = LoadTexture(spriteRoute.c_str());
		}

		if (!IsSoundValid(EnemyNormalPlane::explosion))
		{
			EnemyNormalPlane::explosion = LoadSound(explosionRoute.c_str());
			SetSoundVolume(EnemyNormalPlane::explosion, explosionVolumeScale);
		}

		EnemyNormalPlane newPlane;

		newPlane.isAlive = false;

		newPlane.hitBox = shape::initRectangle(constWidth, constHeight, { 0.f,0.f });
		newPlane.dir = { 0.f, 0.f };
		newPlane.speed = constInitialSpeed;
		newPlane.damage = constInitialDamage;
		newPlane.hp = constInitialHp;

		for (int i = 0; i < maxBulletsPool; i++)
		{
			newPlane.bullets[i] = bullet::init(bullet::bulletPresets[static_cast<int>(bullet::BulletType::Normal)], { 0.f,0.f });
		}

		newPlane.shootCooldown = 0.f;
		newPlane.color = constInitialColor;

		return newPlane;
	}

	void deinit()
	{
		UnloadTexture(EnemyNormalPlane::sprite);
		UnloadSound(EnemyNormalPlane::explosion);
	}

	static void updateBullets(bullet::Bullet bullets[], const float deltaTime);
	static void drawBullets(bullet::Bullet bullets[]);
	static void shoot(EnemyNormalPlane& plane, const player::Player player);
	static void move(EnemyNormalPlane& plane, const float deltaTime);
	static Vector2 getShootDir(EnemyNormalPlane& plane, const Vector2 playerCenter);
	static void outScreen(EnemyNormalPlane& plane);
	static void takeDamage(EnemyNormalPlane& plane, const float damage);
	static void die(EnemyNormalPlane& plane);

	void update(EnemyNormalPlane& plane, const player::Player player, const float deltaTime)
	{
		if (plane.isAlive)
		{
			plane.shootCooldown -= deltaTime;

			move(plane, deltaTime);
			shoot(plane, player);

			outScreen(plane);
		}

		updateBullets(plane.bullets, deltaTime);
	}

	void draw(EnemyNormalPlane& plane)
	{
		drawBullets(plane.bullets);

		if (plane.isAlive)
		{
			renderer::drawSprite(plane.sprite, plane.hitBox, plane.color);
		}
	}

	void launch(EnemyNormalPlane& plane, const Vector2 pos, const Vector2 dir)
	{
		plane.hp = constInitialHp;
		plane.hitBox.pos = pos;
		plane.dir = dir;
		plane.isAlive = true;
	}

	void onHit(EnemyNormalPlane& plane, const float damage)
	{
		takeDamage(plane, damage);
	}

	void onCrash(EnemyNormalPlane& plane)
	{
		takeDamage(plane, constInitialCrashDamage);
	}

	static void updateBullets(bullet::Bullet bullets[], const float delta)
	{
		for (int i = 0; i < maxBulletsPool; i++)
		{
			if (bullets[i].isAlive)
			{
				bullet::update(bullets[i], delta);
			}
		}
	}

	static void drawBullets(bullet::Bullet bullets[])
	{
		for (int i = 0; i < maxBulletsPool; i++)
		{
			if (bullets[i].isAlive)
			{
				bullet::draw(bullets[i]);
			}
		}
	}

	static void shoot(EnemyNormalPlane& plane, const player::Player player)
	{
		if (plane.shootCooldown < EPSILON)
		{
			for (int i = 0; i < maxBulletsPool; i++)
			{
				if (!plane.bullets[i].isAlive)
				{
					Vector2 shootDir = getShootDir(plane, shape::getRectangleCenter(player.hitBox));

					bullet::shoot(plane.bullets[i], shape::getRectangleCenter(plane.hitBox) + shootDir * constBulletSpawnOffset, shootDir);
					plane.shootCooldown = constInitialShootcooldown;

					return;
				}
			}
		}
	}

	static void move(EnemyNormalPlane& plane, const float delta)
	{
		plane.hitBox.pos += plane.dir * plane.speed * delta;
	}

	static Vector2 getShootDir(EnemyNormalPlane& plane, const Vector2 playerCenter)
	{
		float targetDegree = vector::getDegreeFromTwoPoints(plane.hitBox.pos, playerCenter);

		targetDegree = static_cast<float>(GetRandomValue(static_cast<int>(targetDegree - constInitialShootImprecision), static_cast<int>(targetDegree + constInitialShootImprecision)));

		return vector::getDegreeToVector2(targetDegree);
	}

	static void outScreen(EnemyNormalPlane& plane)
	{
		if (screen::isPointOutScreen(shape::getRectangleCenter(plane.hitBox)))
		{
			plane.isAlive = false;
		}
	}

	static void takeDamage(EnemyNormalPlane& plane, const float damage)
	{
		plane.hp -= damage;

		if (plane.hp <= EPSILON)
		{
			plane.hp = 0;
			die(plane);
		}
	}

	static void die(EnemyNormalPlane& plane)
	{
		plane.isAlive = false;
		PlaySound(EnemyNormalPlane::explosion);
	}
}