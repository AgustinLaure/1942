#include "player.h"

#include "raymath.h"

#include "screen.h"
#include "renderer.h"

namespace player
{
	Texture2D Player::sprite;
	Sound Player::lowHpSound;
	Sound Player::explosion;

	//InitialConfig
	static const Vector2 constIniPos = { screen::width / 2, screen::height - 125.f };
	static const shape::Rectangle constHitBoxShape = shape::initRectangle(75, 75, constIniPos);
	static const float constScoreAddPerHit = 5.f;
	static const float constScoreAddPerKill = 13.f;

	//Shoot
	static const Vector2 constShootDir = { 0,-1 };
	static const Vector2 constCenterBulletSpawnOffset = { constHitBoxShape.width / 2, -10.f };
	static const Vector2 constBulletSpawnOffset = { 10.f,5.f };
	static const float constShootCooldown = 0.5f;
	static const int constMaxBulletsPerShot = 5;

	//Sound
	static const float timeBetweenlowHpSound = 1.f;

	static const float lowHpSoundScale = 0.f;
	static const float explosionSoundScale = 0.2f;

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

	static const std::string spriteRoute = "res/sprites/player/player_plane.png";
	static const std::string lowHpRoute = "res/sounds/sfx/player/low_hp.wav";
	static const std::string explosionRoute = "res/sounds/sfx/player/explosion.wav";

	Player init()
	{
		if (!IsTextureValid(Player::sprite))
		{
			Player::sprite = LoadTexture(spriteRoute.c_str());
		}
		if (!IsSoundValid(Player::explosion))
		{
			Player::explosion = LoadSound(explosionRoute.c_str());
			SetSoundVolume(Player::explosion, explosionSoundScale);
		}
		if (!IsSoundValid(Player::lowHpSound))
		{
			Player::lowHpSound = LoadSound(lowHpRoute.c_str());
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
		UnloadTexture(Player::sprite);
		UnloadSound(Player::lowHpSound);
		UnloadSound(Player::explosion);
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
		player.score += constScoreAddPerHit;
	}

	void scoreAddKill(Player& player)
	{
		player.score += constScoreAddPerKill;
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
			bullet::Bullet* availableBullets[constMaxBulletsPerShot];

			int counter = 0;
			for (int i = 0; i < maxBulletsPool; i++)
			{
				if (!player.bullets[i].isAlive)
				{
					availableBullets[counter] = &player.bullets[i];
					counter++;
					if (counter >= constMaxBulletsPerShot)
					{
						break;
					}
				}
			}

			if (counter >= constMaxBulletsPerShot)
			{
				float row = 0.f;
				float current = 1.f;
				for (int i = 0; i < constMaxBulletsPerShot; i++)
				{
					Vector2 bulletPos = player.hitBox.pos + constCenterBulletSpawnOffset;
					float newX = bulletPos.x + constBulletSpawnOffset.x * row * current;
					float newY = bulletPos.y + constBulletSpawnOffset.y * row;
					bulletPos = {newX, newY};

					if (i % 2 == 0)
					{
						row++;
					}

					if (i != 0)
					{
						current *= -1;
					}

					bullet::shoot(*availableBullets[i], bulletPos, constShootDir);
				}

				player.shootCooldown = constShootCooldown;
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
		PlaySound(Player::explosion);

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
