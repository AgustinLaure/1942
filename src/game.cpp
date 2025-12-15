#include "game.h"

#include "raylib.h"

#include "screen.h"
#include "player.h"

namespace game
{
	static bool isRunning = true;
	static Color backgroundColor = BLACK;

	namespace objects
	{
		static player::Player player;
	}

	static void game();
	static void init();
	static void loop();
	static void update();
	static void draw();
	static void deinit();

	void runGame()
	{
		game();
	}

	static void game()
	{
		init();

		loop();

		deinit();
	}

	static void init()
	{
		objects::player = player::init();

		screen::openWindow();
	}

	static void loop()
	{
		while (!WindowShouldClose() && isRunning)
		{
			update();
			draw();
		}
	}

	static void update()
	{
		player::update(objects::player);
	}

	static void draw()
	{
		BeginDrawing();
		ClearBackground(backgroundColor);

		player::draw(objects::player);

		EndDrawing();
	}

	static void deinit()
	{
		screen::closeWindow();
	}
}
