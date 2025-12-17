#include "credits_screen.h"

#include "screen.h"
#include "button.h"

namespace creditsScreen
{
	static const Color backgroundColor = BLACK;

	static const label::FontName creditFont = label::FontName::Militar;
	static const Color creditsColor = WHITE;

	static const Vector2 credits1Pos = { 100, 100 };
	static const std::string credits1Text = "kenney - interface-sounds";
	static const int credits1FontSize = 55;
	static const int credits1Spacing = 2;

	static const Vector2 credits2Pos = { 100, 200 };
	static const std::string credits2Text = "asd";
	static const int credits2FontSize = 55;
	static const int credits2Spacing = 2;

	static const Vector2 credits3Pos = { 100, 300 };
	static const std::string credits3Text = "das";
	static const int credits3FontSize = 55;
	static const int credits3Spacing = 2;

	//AllButtons
	static const label::FontName buttonFont= label::FontName::Militar;
	static const Color buttonTextColor = WHITE;
	static const Color buttonBoxColor = RED;

	//BackButton
	static const Vector2 backPos = { screen::width/2 - 67, screen::height - 130 };
	static const float backWidth = 135.f;
	static const float backHeight = 50.f;
	static const std::string backText = "Back";
	static const int backFontSize = 60;
	static const int backSpacing = 2;

	namespace objects
	{
		static label::Label credits1;
		static label::Label credits2;
		static label::Label credits3;

		static button::Button backButton;
	}

	static void update(mainMenuScreen::Screens& currentMainMenuScreen);
	static void draw();

	void creditsScreen(mainMenuScreen::Screens& currentMainMenuScreen)
	{
		update(currentMainMenuScreen);
		draw();
	}

	void init()
	{
		objects::credits1 = label::init(credits1Pos, credits1Text, creditFont, credits1FontSize, credits1Spacing, creditsColor);
		objects::credits2 = label::init(credits2Pos, credits2Text, creditFont, credits2FontSize, credits2Spacing, creditsColor);
		objects::credits3 = label::init(credits3Pos, credits3Text, creditFont, credits3FontSize, credits3Spacing, creditsColor);

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

		label::draw(objects::credits1);
		label::draw(objects::credits2);
		label::draw(objects::credits3);

		button::draw(objects::backButton);

		EndDrawing();
	}
}
