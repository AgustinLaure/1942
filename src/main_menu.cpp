#include "main_menu.h"

#include "raylib.h"

#include "title_screen.h"
#include "rules_screen.h"
#include "credits_screen.h"

namespace mainMenu
{
	static mainMenuScreen::Screens currentScreen = mainMenuScreen::Screens::Title;

	namespace objects
	{
		Music menuMusic;
	}

	void mainMenu(gameScene::Scenes& currentGameScene)
	{
		if (!IsMusicStreamPlaying(objects::menuMusic))
		{
			PlayMusicStream(objects::menuMusic);
		}

		UpdateMusicStream(objects::menuMusic);

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
		objects::menuMusic = LoadMusicStream("res/sound/music/menu.ogg");
		SetMusicVolume(objects::menuMusic, 0.1f);
		objects::menuMusic.looping = true;

		titleScreen::init();
		rulesScreen::init();
		creditsScreen::init();
	}

	void deinit()
	{
		UnloadMusicStream(objects::menuMusic);

		titleScreen::deinit();
		rulesScreen::deinit();
		creditsScreen::deinit();
	}
}
