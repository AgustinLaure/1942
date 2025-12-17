#include "screen.h"

namespace screen
{
	static const std::string name = "1942";

	void openWindow()
	{
		InitWindow(width, height, name.c_str());
	}

	void closeWindow()
	{
		CloseWindow();
	}

	bool isPointOutScreen(const Vector2 pos)
	{
		return pos.x < 0 || pos.x > width || pos.y < 0 || pos.y > height;
	}

	bool isRectangleOutScreen(const Vector2 rectPos, const float rectWidth, const float rectHeight)
	{
		Vector2 rectTopLeft = rectPos;
		Vector2 rectTopRight = { rectPos.x + rectWidth, rectPos.y };
		Vector2 rectBotLeft = { rectPos.x, rectPos.y + rectHeight };
		Vector2 rectBotRight = { rectPos.x + rectWidth, rectPos.y + rectHeight };

		return isPointOutScreen(rectTopLeft) || isPointOutScreen(rectTopRight) 
			|| isPointOutScreen(rectBotLeft) || isPointOutScreen(rectBotRight);
	}
}
