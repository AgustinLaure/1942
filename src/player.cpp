#include "player.h"

#include "raymath.h"

#include "screen.h"

namespace player
{
	//InitialConfig
	static const shape::Rectangle constHitBoxShape = shape::initRectangle(50, 101, { 0,0 });
	static const Vector2 constBulletSpawnOffset = { constHitBoxShape.width / 2, -10.f };
	static const float constShootCooldown = 0.5f;

	static const Vector2 constShootDir = { 0,-1 };
	static const float constInitialSpeed = 500.f;
	static const float constInitialDamage = 1.f;
	static const float constInitialHp = 3.f;
	static const Color constInitialColor = WHITE;

	//Controls
	static const KeyboardKey shootKey = KEY_SPACE;
	static const KeyboardKey moveUpKey = KEY_W;
	static const KeyboardKey moveLeftKey = KEY_A;
	static const KeyboardKey moveDownKey = KEY_S;
	static const KeyboardKey moveRightKey = KEY_D;

	static void updateBullets(bullet::Bullet bullets[], const float delta);
	static void drawBullets(bullet::Bullet bullets[]);
	static void action(Player& player, float deltaTime);
	static void shoot(Player& player);
	static void move(Player& player, float deltaTime);

	Player init()
	{
		Player newPlayer;

		newPlayer.hitBox = constHitBoxShape;
		newPlayer.dir = { 0.f,0.f };
		newPlayer.speed = constInitialSpeed;
		newPlayer.damage = constInitialDamage;
		newPlayer.hp = constInitialHp;

		for (int i = 0; i < maxBulletsPool; i++)
		{
			newPlayer.bullets[i] = bullet::init(bullet::bulletPresets[static_cast<int>(bullet::BulletType::Normal)], { 0,0 });
		}
		newPlayer.shootCooldown = 0.f;

		newPlayer.color = constInitialColor;

		return newPlayer;
	}

	void update(Player& player, float deltaTime)
	{
		player.shootCooldown -= deltaTime;

		action(player, deltaTime);

		updateBullets(player.bullets, deltaTime);
	}

	void draw(Player player)
	{
		drawBullets(player.bullets);

		DrawRectangle(static_cast<int>(player.hitBox.pos.x), static_cast<int>(player.hitBox.pos.y), static_cast<int>(player.hitBox.width), static_cast<int>(player.hitBox.height), player.color);
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

	static void action(Player& player, float deltaTime)
	{
		move(player, deltaTime);
		shoot(player);
	}

	static void shoot(Player& player)
	{
		if (IsKeyDown(shootKey) && player.shootCooldown < EPSILON)
		{
			for (int i = 0; i < maxBulletsPool; i++)
			{
				if (!player.bullets[i].isAlive)
				{
					bullet::shoot(player.bullets[i], player.hitBox.pos + constBulletSpawnOffset, constShootDir);
					player.shootCooldown = constShootCooldown;

					return;
				}
			}
		}
	}

	static void move(Player& player, float delta)
	{
		player.dir = { 0,0 };

		if (IsKeyDown(moveUpKey))
		{
			player.dir.y = -1;
		}
		if (IsKeyDown(moveDownKey))
		{
			player.dir.y = 1;
		}
		if (IsKeyDown(moveLeftKey))
		{
			player.dir.x = -1;
		}
		if (IsKeyDown(moveRightKey))
		{
			player.dir.x = 1;
		}

		Vector2 nextPos = player.hitBox.pos + (player.dir * player.speed * delta);

		if (!screen::isRectangleOutScreen(nextPos, player.hitBox.width, player.hitBox.height))
		{
			player.hitBox.pos = nextPos;
		}
	}
}
