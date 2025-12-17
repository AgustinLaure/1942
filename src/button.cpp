#include "button.h"

#include "raylib.h"

namespace button
{
	const MouseButton actionButton = MOUSE_LEFT_BUTTON;

	Sound Button::onSelect;

	void init(Button& button, const float width, const float height, const Vector2 pos, const std::string text, const float fontSize, const float spacing, const Color textColor, const Color bckgColor)
	{
		Button::onSelect = LoadSound("res/sound/sfx/ui/selectSound.ogg");
		button.body.width = width;
		button.body.height = height;
		button.body.pos = pos;
		button.text.pos = button.body.pos;
		button.text.text = text;
		button.text.fontSize = fontSize;
		button.text.spacing = spacing;
		button.text.color = textColor;
		button.color = bckgColor;
		button.isPressed = false;
	}

	void update(Button& button)
	{
		button.isPressed = false;

		if (IsMouseButtonDown(actionButton))
		{
			if (shape::isPointCollidingRect(GetMousePosition(), button.body))
			{
				button.isPressed = true;
				PlaySound(Button::onSelect);
			}
		}
	}

	void draw(const Button button)
	{
		DrawTextEx(GetFontDefault(), button.text.text.c_str(), button.text.pos, button.text.fontSize, button.text.spacing, button.text.color);
	}
}
