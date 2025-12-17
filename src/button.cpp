#include "button.h"

#include "raymath.h"

namespace button
{
	static const MouseButton actionButton = MOUSE_LEFT_BUTTON;

	Sound Button::onSelect;

	Button init(const float width, const float height, const Vector2 pos, const std::string text, const label::FontName font, const float fontSize, const float spacing, const Color textColor, const Color bckgColor)
	{
		if (Button::onSelect.frameCount < EPSILON)
		{
			Button::onSelect = LoadSound("res/sounds/sfx/ui/selectSound.ogg");
			SetSoundVolume(Button::onSelect, 0.1f);
		}

		Button newButton;

		newButton.body.width = width;
		newButton.body.height = height;
		newButton.body.pos = pos;
		newButton.text = label::init(newButton.body.pos, text, font, fontSize, spacing, textColor);
		newButton.color = bckgColor;
		newButton.isPressed = false;

		return newButton;
	}

	void update(Button& button)
	{
		button.isPressed = false;

		if (IsMouseButtonPressed(actionButton))
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
		DrawRectangleLines(static_cast<int>(button.body.pos.x), static_cast<int>(button.body.pos.y), static_cast<int>(button.body.width), static_cast<int>(button.body.height), button.color);
	}

	void deinit()
	{
		if (Button::onSelect.frameCount < EPSILON)
		{
			if (IsSoundValid(Button::onSelect))
			{
				UnloadSound(Button::onSelect);
			}
		}
	}
}
