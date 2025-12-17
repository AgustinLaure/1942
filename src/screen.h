#pragma once

#include <string>
#include "vector.h"

namespace screen
{
	void openWindow();
	void closeWindow();
	bool isPointOutScreen(const Vector2 pos);
	bool isRectangleOutScreen(const Vector2 pos, const float width, const float height);
}

