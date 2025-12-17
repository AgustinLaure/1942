#include "player.h"

#include "raylib.h"
#include "raymath.h"
#include "screen.h"

namespace player
{
	//InitialConfig
	static const shape::Rectangle constHitBoxShape = shape::init(5, 10, {0,0});
	static const float constInitialSpeed = 100.f;
	static const float constInitialDamage = 1.f;
	static const float constInitialHp = 3.f;
	static const Color constInitialColor = WHITE;
	
	//Controls
	static const KeyboardKey shootKey = KEY_SPACE;
	static const KeyboardKey moveUpKey = KEY_W;
	static const KeyboardKey moveLeftKey = KEY_A;
	static const KeyboardKey moveDownKey = KEY_S;
	static const KeyboardKey moveRightKey = KEY_D;

	void action(Player& player, float deltaTime);
	void shoot();
	void move(Player& player, float deltaTime);
	bool isOutScreen(const Player player);
	
	Player init()
	{
		Player newPlayer;

		newPlayer.hitBox = constHitBoxShape;
		newPlayer.dir = { 0.f,0.f };
		newPlayer.speed = constInitialSpeed;
		newPlayer.damage = constInitialDamage;
		newPlayer.hp = constInitialHp;

		newPlayer.color = constInitialColor;

		return newPlayer;
	}

	void update(Player& player, float deltaTime)
	{
		action(player,deltaTime);
	}

	void draw(const Player player)
	{
		DrawRectangle(static_cast<int>(player.hitBox.pos.x), static_cast<int>(player.hitBox.pos.y), static_cast<int>(player.hitBox.width), static_cast<int>(player.hitBox.height), player.color);
	}

	void action(Player & player, float deltaTime)
	{
		move(player, deltaTime);
		shoot();
	}

	void shoot()
	{
		if (IsKeyDown(shootKey))
		{

		}
	}

	void move(Player& player, float delta)
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
