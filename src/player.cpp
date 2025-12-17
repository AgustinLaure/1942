#include "player.h"

#include "raylib.h"

namespace player
{
	static const shape::Rectangle constHitBoxShape = shape::init(5, 10, {0,0});
	static const float constInitialSpeed = 10.f;
	static const float constInitialDamage = 1.f;
	static const float constInitialHp = 3.f;
	static const Color constInitialColor = WHITE;

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
		player;
		
	}

	void draw(const Player player)
	{
		DrawRectangle(static_cast<int>(player.hitBox.pos.x), static_cast<int>(player.hitBox.pos.y), static_cast<int>(player.hitBox.width), static_cast<int>(player.hitBox.height), player.color);
	}
}
