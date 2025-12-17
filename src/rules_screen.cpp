#include "rules_screen.h"

#include "screen.h"
#include "button.h"

namespace rulesScreen
{
	static const Color backgroundColor = BLACK;

	static const label::FontName rulesFont = label::FontName::Militar;
	static const Color rulesColor = WHITE;

	static const Vector2 rules1Pos = {100, 100};
	static const std::string rules1Text = "-Dodge and shoot down as many planes as you can";
	static const int rules1FontSize = 38;
	static const int rules1Spacing = 2;

	static const Vector2 rules2Pos = { 100, 200 };
	static const std::string rules2Text = "-WASD move in all direction";
	static const int rules2FontSize = 40;
	static const int rules2Spacing = 2;

	static const Vector2 rules3Pos = { 100, 300 };
	static const std::string rules3Text = "-SPACEBAR shoot";
	static const int rules3FontSize = 40;
	static const int rules3Spacing = 2;

	static const Vector2 rules4Pos = { 100, 400 };
	static const std::string rules4Text = "-ESCAPE pause";
	static const int rules4FontSize = 40;
	static const int rules4Spacing = 2;

	//AllButtons
	static const label::FontName buttonFont = label::FontName::Militar;
	static const Color buttonTextColor = WHITE;
	static const Color buttonBoxColor = RED;

	//BackButton
	static const Vector2 backPos = { screen::width / 2 - 67, screen::height - 130 };
	static const float backWidth = 135.f;
	static const float backHeight = 50.f;
	static const std::string backText = "Back";
	static const int backFontSize = 60;
	static const int backSpacing = 2;

	namespace objects
	{
		static label::Label rules1;
		static label::Label rules2;
		static label::Label rules3;
		static label::Label rules4;

		static button::Button backButton;
	}

	static void update(mainMenuScreen::Screens& currentMainMenuScreen);
	static void draw();

	void rulesScreen(mainMenuScreen::Screens& currentMainMenuScreen)
	{
		update(currentMainMenuScreen);
		draw();
	}

	void init()
	{
		objects::rules1 = label::init(rules1Pos,rules1Text,rulesFont,rules1FontSize,rules1Spacing,rulesColor);
		objects::rules2 = label::init(rules2Pos,rules2Text,rulesFont,rules2FontSize,rules2Spacing,rulesColor);
		objects::rules3 = label::init(rules3Pos,rules3Text,rulesFont,rules3FontSize,rules3Spacing,rulesColor);
		objects::rules4 = label::init(rules4Pos,rules4Text,rulesFont,rules4FontSize,rules4Spacing,rulesColor);

		objects::backButton = button::init(backWidth, backHeight, backPos, backText, buttonFont, backFontSize, backSpacing, buttonTextColor, buttonBoxColor);
	}

	static void update(mainMenuScreen::Screens& currentMainMenuScreen)
	{
		button::update(objects::backButton);

		if (objects::backButton.isPressed)
		{
			currentMainMenuScreen = mainMenuScreen::Screens::Title;
		}
	}

	static void draw()
	{
		BeginDrawing();
		ClearBackground(backgroundColor);

		label::draw(objects::rules1);
		label::draw(objects::rules2);
		label::draw(objects::rules3);
		label::draw(objects::rules4);

		button::draw(objects::backButton);

		EndDrawing();
	}
}