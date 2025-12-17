#include "credits_screen.h"

#include "screen.h"
#include "button.h"

namespace creditsScreen
{
	static const Color backgroundColor = BLACK;

	static const label::FontName creditFont = label::FontName::Militar;
	static const Color creditsColor = WHITE;

	static const Vector2 credits1Pos = { 100, 100 };
	static const std::string credits1Text = "Developer:        Agustin Laure ";
	static const int credits1FontSize = 40;
	static const int credits1Spacing = 2;

	static const Vector2 credits2Pos = { 100, 200 };
	static const std::string credits2Text = "Assets from: ";
	static const int credits2FontSize = 40;
	static const int credits2Spacing = 2;

	static const Vector2 credits3Pos = { 400, 200 };
	static const std::string credits3Text = "[ kenney - interface-sounds ]";
	static const int credits3FontSize = 40;
	static const int credits3Spacing = 2;

	static const Vector2 credits4Pos = { 400, 300 };
	static const std::string credits4Text = "[ sir-raitan - itchio ]";
	static const int credits4FontSize = 40;
	static const int credits4Spacing = 2;

	static const Vector2 credits5Pos = { 400, 400 };
	static const std::string credits5Text = "[ ansimuz - itchio ]";
	static const int credits5FontSize = 40;
	static const int credits5Spacing = 2;

	static const Vector2 credits6Pos = { 400, 500 };
	static const std::string credits6Text = "[ ef9 - itchio ]";
	static const int credits6FontSize = 40;
	static const int credits6Spacing = 2;

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
		static label::Label credits4;
		static label::Label credits5;
		static label::Label credits6;

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
		objects::credits4 = label::init(credits4Pos, credits4Text, creditFont, credits4FontSize, credits4Spacing, creditsColor);
		objects::credits5 = label::init(credits5Pos, credits5Text, creditFont, credits5FontSize, credits5Spacing, creditsColor);
		objects::credits6 = label::init(credits6Pos, credits6Text, creditFont, credits6FontSize, credits6Spacing, creditsColor);

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
		label::draw(objects::credits4);
		label::draw(objects::credits5);
		label::draw(objects::credits6);

		button::draw(objects::backButton);

		EndDrawing();
	}
}
