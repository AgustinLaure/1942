#include "game.h"

#include "screen.h"
#include "game_scene.h"
#include "playing.h"
#include "main_menu.h"

namespace game
{
	static bool isRunning = true;
	static float deltaTime = 0.f;

	static gameScene::Scenes currentScene = gameScene::Scenes::Playing;

	static void game();
	static void init();
	static void loop();
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
		playing::init();
		mainMenu::init();
	}

	static void loop()
	{
		while (!WindowShouldClose() && isRunning)
		{
			deltaTime = GetFrameTime();

			switch (currentScene)
			{
			case gameScene::Scenes::Playing:
				playing::playing(deltaTime);
				break;

			case gameScene::Scenes::MainMenu:
				break;

			default:
				break;
			}
		}
	}
	
	static void deinit()
	{
		playing::deinit();
		mainMenu::deinit();

		screen::closeWindow();
	}
}
