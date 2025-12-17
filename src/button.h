#pragma once

#include "shape.h"
#include "label.h"

namespace button
{
	struct Button
	{
		static Sound onSelect;
		shape::Rectangle body;
		label::Label text;
		Color color = WHITE;
		bool isPressed = false;
	};

	Button init(const float width, const float height, const Vector2 pos, const std::string text, const label::FontName font, const float fontSize, const float spacing, const Color textColor, const Color bckgColor);
	void update(Button& button);
	void draw(const Button button);
	void deinit();
}

