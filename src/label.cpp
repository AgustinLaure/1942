#include "label.h"

namespace label
{
	Label init(const Vector2 pos, const std::string text, const Font font, const float fontSize, const float spacing, const Color color)
	{
		Label newLabel;

		newLabel.pos = pos;
		newLabel.text = text;
		newLabel.font = font;
		newLabel.fontSize = fontSize;
		newLabel.spacing = spacing;
		newLabel.color = color;

		return newLabel;
	}
	
	void draw(const Label label)
	{
		DrawTextEx(GetFontDefault(), label.text.c_str(), label.pos, label.fontSize, label.spacing, label.color);
	}
}
