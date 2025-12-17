#include "main_menu.h"

#include "raylib.h"

#include "title_screen.h"
#include "rules_screen.h"
#include "credits_screen.h"

namespace mainMenu
{
	static mainMenuScreen::Screens currentScreen = mainMenuScreen::Screens::Title;

	void mainMenu(gameScene::Scenes& currentGameScene)
	{
		switch (currentScreen)
		{
		case mainMenuScreen::Screens::Title:
			titleScreen::titleScreen(currentGameScene, currentScreen);
			break;

		case mainMenuScreen::Screens::Rules:
			rulesScreen::rulesScreen(currentScreen);
			break;

		case mainMenuScreen::Screens::Credits:
			creditsScreen::creditsScreen(currentScreen);
			break;

		default:
			break;
		}
	}

	void init()
	{
		titleScreen::init();
		rulesScreen::init();
		creditsScreen::init();
	}

	void deinit()
	{
		titleScreen::deinit();
		rulesScreen::deinit();
		creditsScreen::deinit();
	}
}
