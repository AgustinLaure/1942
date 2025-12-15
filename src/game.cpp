#include "game.h"

#include "raylib.h"

#include "screen.h"

namespace game
{
	static bool isRunning = true;
	static Color backgroundColor = BLACK;

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
		
	}

	static void draw()
	{
		BeginDrawing();
		ClearBackground(backgroundColor);

		//Draw

		EndDrawing();
	}

	static void deinit()
	{
		screen::closeWindow();
	}
}
