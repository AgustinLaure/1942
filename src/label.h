#pragma once

#include <string>

#include "raylib.h"

namespace label
{
	struct Label
	{
		Vector2 pos = { 0,0 };
		std::string text = " ";
		Font font;
		float fontSize = 0.0f;
		float spacing = 0.0f;
		Color color = WHITE;
	};

	Label init(const Vector2 pos, const std::string text, const std::string fontRoute, const float fontSize, const float spacing, const Color color);
	void draw(const Label label);
	void deinit(Label& label);
}

