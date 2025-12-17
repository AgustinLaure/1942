#include "label.h"

namespace label
{
	Font Label::fonts[maxFonts];

	Label init(const Vector2 pos, const std::string text, const FontName font, const float fontSize, const float spacing, const Color color)
	{
		for (int i = 0; i < maxFonts; i++)
		{
			if (!IsFontValid(Label::fonts[i]))
			{
				Label::fonts[i] = LoadFont(fontRoutes[i].c_str());
			}
		}

		Label newLabel;

		newLabel.pos = pos;
		newLabel.text = text;
		newLabel.fontSize = fontSize;
		newLabel.fontId = static_cast<int>(font);
		newLabel.spacing = spacing;
		newLabel.color = color;

		return newLabel;
	}

	void draw(const Label label)
	{
		DrawTextEx(GetFontDefault(), label.text.c_str(), label.pos, label.fontSize, label.spacing, label.color);
	}

	void deinit()
	{
		for (int i = 0; i < maxFonts; i++)
		{
			if (IsFontValid(Label::fonts[i]))
			{
				UnloadFont(Label::fonts[i]);
			}
		}
	}
}
