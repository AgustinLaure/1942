#include "game.h"

#include "screen.h"
#include "game_scene.h"
#include "playing.h"
#include "main_menu.h"

namespace game
{
	static bool isRunning = true;
	static float deltaTime = 0.f;

	static gameScene::Scenes currentScene = gameScene::Scenes::MainMenu;

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
		screen::openWindow();
		InitAudioDevice();

		SetExitKey(KEY_NULL);

		playing::init();
		mainMenu::init();
	}

	static void loop()
	{
		while (!WindowShouldClose() && currentScene != gameScene::Scenes::Exit)
		{
			deltaTime = GetFrameTime();

			switch (currentScene)
			{
			case gameScene::Scenes::Playing:
				playing::playing(currentScene, deltaTime);
				break;

			case gameScene::Scenes::MainMenu:
				mainMenu::mainMenu(currentScene);
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

		CloseAudioDevice();
		screen::closeWindow();
	}
}
