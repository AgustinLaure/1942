#include "main_menu.h"

#include "raylib.h"

#include "button.h"
#include "screen.h"

static const Color backgroundColor = BLACK;

namespace mainMenu
{
	enum class Screens
	{
		MainMenu,
		Rules,
		Credits
	};

	static Screens currentScreen = Screens::MainMenu;

	//Title
	static const std::string titleText = "1942";
	static const std::string titleFontRoute = "res/fonts/militar_font.otf";
	static const int titleFontSize = 120;
	static const Vector2 titlePos = { screen::width / 2 - 100, 100 };
	static const int titleSpacing = 3;
	static const Color titleColor = WHITE;

	//AllButtons
	static const float buttonWidth = 200.f;
	static const float buttonHeight = 50.f;
	static const std::string buttonFontRoute = "res/fonts/militar_font.otf";
	static const Color buttonTextColor = WHITE;
	static const Color buttonBoxColor = RED;

	//PlayButton
	static const Vector2 playPos = { 150, screen::height - 200 };
	static const std::string playText = "Play";
	static const int playFontSize = 60;
	static const int playSpacing = 2;

	//RulesButton
	static const Vector2 rulesPos = { 350, screen::height - 200 };
	static const std::string rulesText = "Rules";
	static const int rulesFontSize = 60;
	static const int rulesSpacing = 2;

	//CreditButton
	static const Vector2 creditsPos = { 550, screen::height - 200 };
	static const std::string creditsText = "Credits";
	static const int creditsFontSize = 60;
	static const int creditsSpacing = 2;

	//Exitutton
	static const Vector2 exitPos = { 800, screen::height - 200 };
	static const std::string exitText = "Exit";
	static const int exitFontSize = 60;
	static const int exitSpacing = 2;


	namespace objects
	{
		static label::Label title;

		static button::Button playButton;
		static button::Button rulesButton;
		static button::Button creditsButton;
		static button::Button exitButton;
	}

	static void update(gameScene::Scenes& currentGameScene);
	static void draw();

	void mainMenu(gameScene::Scenes& currentGameScene)
	{
		update(currentGameScene);
		draw();
	}

	void init()
	{
		objects::title = label::init(titlePos, titleText, titleFontRoute, titleFontSize, titleSpacing, titleColor);
		objects::playButton = button::init(buttonWidth, buttonHeight, playPos, playText, buttonFontRoute, playFontSize, playSpacing, buttonTextColor, buttonBoxColor);
		objects::rulesButton = button::init(buttonWidth, buttonHeight, rulesPos, rulesText, buttonFontRoute, rulesFontSize, rulesSpacing, buttonTextColor, buttonBoxColor);
		objects::creditsButton = button::init(buttonWidth, buttonHeight, creditsPos, creditsText, buttonFontRoute, creditsFontSize, creditsSpacing, buttonTextColor, buttonBoxColor);
		objects::exitButton = button::init(buttonWidth, buttonHeight, exitPos, exitText, buttonFontRoute, exitFontSize, exitSpacing, buttonTextColor, buttonBoxColor);
	}

	void deinit()
	{
		label::deinit(objects::title);

		button::deinit(objects::playButton);
	}

	static void update(gameScene::Scenes& currentGameScene)
	{
		if (objects::playButton.isPressed)
		{
			currentGameScene = gameScene::Scenes::Playing;
		}
		if (objects::exitButton.isPressed)
		{
			currentGameScene = gameScene::Scenes::Exit;
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
		button::draw(objects::playButton);
		button::draw(objects::rulesButton);
		button::draw(objects::creditsButton);
		button::draw(objects::exitButton);

		EndDrawing();
	}
}
