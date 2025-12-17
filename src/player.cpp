#include "player.h"

#include "raymath.h"

#include "screen.h"
#include "renderer.h"

namespace player
{
	Texture2D Player::sprite;
	Sound Player::lowHpSound;

	//InitialConfig
	static const shape::Rectangle constHitBoxShape = shape::initRectangle(75, 75, { 0,0 });
	static const Vector2 constBulletSpawnOffset = { constHitBoxShape.width / 2, -10.f };
	static const float constShootCooldown = 0.5f;
	static const float scoreAddPerHit = 5.f;
	static const float scoreAddPerKill = 13.f;

	static const float timeBetweenlowHpSound = 1.f;
	static const float lowHpSoundScale = 0.3f;

	static const Vector2 constShootDir = { 0,-1 };
	static const float constInitialSpeed = 500.f;
	static const float constInitialDamage = 1.f;
	static const float constInitialHp = 1.f;
	static const Color constInitialColor = WHITE;
	static const float constInitialCrashDamage = 2.f;

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
	static void takeDamage(Player& player, const float damage);
	static void die(Player& player);
	static void lowHpSound(Player& player, const float delta);

	static std::string playerSpriteRoute = "res/sprites/player/player_plane.png";

	Player init()
	{
		if (!IsTextureValid(Player::sprite))
		{
			Player::sprite = LoadTexture(playerSpriteRoute.c_str());
		}
		if (!IsSoundValid(Player::lowHpSound))
		{
			Player::lowHpSound = LoadSound("res/sounds/sfx/player/low_hp.wav");
		}

		Player newPlayer;

		newPlayer.isAlive = true;

		newPlayer.hitBox = constHitBoxShape;
		newPlayer.dir = { 0.f,0.f };
		newPlayer.speed = constInitialSpeed;
		newPlayer.damage = constInitialDamage;
		newPlayer.hp = constInitialHp;

		SetSoundVolume(newPlayer.lowHpSound, lowHpSoundScale);

		for (int i = 0; i < maxBulletsPool; i++)
		{
			newPlayer.bullets[i] = bullet::init(bullet::bulletPresets[static_cast<int>(bullet::BulletType::Normal)], { 0,0 });
		}
		newPlayer.shootCooldown = 0.f;

		newPlayer.color = constInitialColor;

		return newPlayer;
	}

	void deinit()
	{
		//for (int i = 0; i < maxBulletsPool; i++)
		//{
		//	bullet::deinit(player.bullets[i]);
		//}
		UnloadTexture(Player::sprite);
		UnloadSound(Player::lowHpSound);
	}

	void update(Player& player, float deltaTime)
	{
		player.shootCooldown -= deltaTime;

		action(player, deltaTime);

		updateBullets(player.bullets, deltaTime);

		if (player.hp < constInitialHp / 2)
		{
			lowHpSound(player, deltaTime);
		}
	}

	void draw(Player player)
	{
		drawBullets(player.bullets);
		DrawRectangle(static_cast<int>(player.hitBox.pos.x), static_cast<int>(player.hitBox.pos.y), static_cast<int>(player.hitBox.width), static_cast<int>(player.hitBox.height), player.color);

		renderer::drawSprite(player.sprite, player.hitBox, WHITE);
	}

	void onHit(Player& player, const float damage)
	{
		takeDamage(player, damage);
	}

	void onCrash(Player& player)
	{
		takeDamage(player, constInitialCrashDamage);
	}

	void scoreAddHit(Player& player)
	{
		player.score += scoreAddPerHit;
	}

	void scoreAddKill(Player& player)
	{
		player.score += scoreAddPerKill;
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

	static void takeDamage(Player& player, const float damage)
	{
		player.hp -= damage;

		if (player.hp <= EPSILON)
		{
			player.hp = 0;
			die(player);
		}
	}

	static void die(Player& player)
	{
		player.isAlive = false;
	}

	static void lowHpSound(Player& player, const float delta)
	{
		player.lowHpCooldown -= delta;

		if (player.lowHpCooldown < EPSILON && player.hp < constInitialHp)
		{
			player.lowHpCooldown = timeBetweenlowHpSound;
			PlaySound(player.lowHpSound);
		}
	}
}
