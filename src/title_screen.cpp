#include "title_screen.h"

#include "screen.h"
#include "button.h"

static const Color backgroundColor = BLACK;

namespace titleScreen
{
	//Title
	static const std::string titleText = "1942";
	static const int titleFontSize = 120;
	static const label::FontName titleFont = label::FontName::Militar;
	static const Vector2 titlePos = { screen::width / 2 - 100, 100 };
	static const int titleSpacing = 3;
	static const Color titleColor = WHITE;

	//Version
	static const std::string versionText = "v1.0";
	static const int versionFontSize = 30;
	static const label::FontName versionFont = label::FontName::Militar;
	static const Vector2 versionPos = { screen::width - 100, screen::height-50};
	static const int versionSpacing = 3;
	static const Color versionColor = WHITE;

	//AllButtons
	static const label::FontName buttonFont = label::FontName::Militar;
	static const Color buttonTextColor = WHITE;
	static const Color buttonBoxColor = RED;

	//PlayButton
	static const Vector2 playPos = { 150, screen::height - 200 };
	static const float playWidth = 114.f;
	static const float playHeight = 50.f;
	static const std::string playText = "Play";
	static const int playFontSize = 60;
	static const int playSpacing = 2;

	//RulesButton
	static const Vector2 rulesPos = { 350, screen::height - 200 };
	static const float rulesWidth = 146.f;
	static const float rulesHeight = 50.f;
	static const std::string rulesText = "Rules";
	static const int rulesFontSize = 60;
	static const int rulesSpacing = 2;

	//CreditButton
	static const Vector2 creditsPos = { 550, screen::height - 200 };
	static const float creditsWidth = 200.f;
	static const float creditsHeight = 50.f;
	static const std::string creditsText = "Credits";
	static const int creditsFontSize = 60;
	static const int creditsSpacing = 2;

	//Exitutton
	static const Vector2 exitPos = { 800, screen::height - 200 };
	static const float exitWidth = 102.f;
	static const float exitHeight = 50.f;
	static const std::string exitText = "Exit";
	static const int exitFontSize = 60;
	static const int exitSpacing = 2;

	namespace objects
	{
		static label::Label title;
		static label::Label version;

		static button::Button playButton;
		static button::Button rulesButton;
		static button::Button creditsButton;
		static button::Button exitButton;
	}

	static void update(gameScene::Scenes& currentGameScene, mainMenuScreen::Screens& currentMainMenuScreen);
	static void draw();

	void titleScreen(gameScene::Scenes& currentGameScene, mainMenuScreen::Screens& currentMainMenuScreen)
	{
		update(currentGameScene, currentMainMenuScreen);
		draw();
	}

	void init()
	{
		objects::title = label::init(titlePos, titleText, titleFont, titleFontSize, titleSpacing, titleColor);
		objects::version = label::init(versionPos, versionText, versionFont, versionFontSize, versionSpacing, versionColor);

		objects::playButton = button::init(playWidth, playHeight, playPos, playText, buttonFont, playFontSize, playSpacing, buttonTextColor, buttonBoxColor);
		objects::rulesButton = button::init(rulesWidth, rulesHeight, rulesPos, rulesText, buttonFont, rulesFontSize, rulesSpacing, buttonTextColor, buttonBoxColor);
		objects::creditsButton = button::init(creditsWidth, creditsHeight, creditsPos, creditsText, buttonFont, creditsFontSize, creditsSpacing, buttonTextColor, buttonBoxColor);
		objects::exitButton = button::init(exitWidth, exitHeight, exitPos, exitText, buttonFont, exitFontSize, exitSpacing, buttonTextColor, buttonBoxColor);
	}

	static void update(gameScene::Scenes& currentGameScene, mainMenuScreen::Screens& currentMainMenuScreen)
	{
		if (objects::playButton.isPressed)
		{
			currentGameScene = gameScene::Scenes::Playing;
		}
		if (objects::exitButton.isPressed)
		{
			currentGameScene = gameScene::Scenes::Exit;
		}
		if (objects::rulesButton.isPressed)
		{
			currentMainMenuScreen = mainMenuScreen::Screens::Rules;
		}
		if (objects::creditsButton.isPressed)
		{
			currentMainMenuScreen = mainMenuScreen::Screens::Credits;
		}

		button::update(objects::playButton);
		button::update(objects::rulesButton);
		button::update(objects::creditsButton);
		button::update(objects::exitButton);
	}

	static void draw()
	{
		BeginDrawing();
		ClearBackground(backgroundColor);

		label::draw(objects::title);
		label::draw(objects::version);

		button::draw(objects::playButton);
		button::draw(objects::rulesButton);
		button::draw(objects::creditsButton);
		button::draw(objects::exitButton);

		EndDrawing();
	}
}
