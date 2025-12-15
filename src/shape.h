#pragma once

#include "raylib.h"

namespace shape
{
	struct Rectangle
	{
		float width = 0.0f;
		float height = 0.0f;
		Vector2 pos = { 0,0 };
	};

	bool isRectOnRect(Vector2 rect1Pos, int rect1Width, int rect1Height, Vector2 rect2Pos, int rect2Width, int rect2Height);
	bool isPointCollidingRect(Vector2 p, Rectangle rect);
}


