#pragma once

#include "vector.h"

namespace shape
{
	struct Rectangle
	{
		float width = 0.0f;
		float height = 0.0f;
		Vector2 pos = { 0,0 };
	};

	Rectangle initRectangle(const float width, const float height, const Vector2 pos);
	Vector2 getRectangleCenter(const Rectangle rectangle);
	bool isRectOnRect(const Vector2 rect1Pos, const int rect1Width, const int rect1Height, const Vector2 rect2Pos, const int rect2Width, const int rect2Height);
	bool isPointCollidingRect(const Vector2 p, const Rectangle rect);
}


