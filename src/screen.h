#pragma once

#include <string>

#include "vector.h"

namespace screen
{
	const int width = 1040;
	const int height = 720;

	void openWindow();
	void closeWindow();
	bool isPointOutScreen(const Vector2 pos);
	bool isRectangleOutScreen(const Vector2 pos, const float width, const float height);
}

