#pragma once

#include <string>

#include "raylib.h"

namespace label
{
	enum class FontName
	{
		Militar
	};

	static const int maxFonts = 1;
	const std::string fontRoutes[maxFonts]
	{
		"res/fonts/militar_font.otf"
	};

	struct Label
	{
		static Font fonts[maxFonts];

		Vector2 pos = { 0,0 };
		std::string text = " ";
		float fontSize = 0.0f;
		float spacing = 0.0f;
		int fontId = 0;
		Color color = WHITE;
	};

	Label init(const Vector2 pos, const std::string text, const FontName font, const float fontSize, const float spacing, const Color color);
	void draw(const Label label);
	void deinit();
}

