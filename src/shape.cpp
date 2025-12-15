#include "shape.h"

namespace shape
{
	Rectangle init(const float width, const float height, const Vector2 pos)
	{
		Rectangle newRect;

		newRect.width = width;
		newRect.height = height;
		newRect.pos = pos;

		return newRect;
	}

	bool isRectOnRect(const Vector2 rect1Pos, const int rect1Width, const int rect1Height, const Vector2 rect2Pos, const int rect2Width, const int rect2Height)
	{
		return (rect1Pos.x <= rect2Pos.x + rect2Width
			&& rect1Pos.x + rect1Width >= rect2Pos.x
			&& rect1Pos.y <= rect2Pos.y + rect2Height
			&& rect1Pos.y + rect1Height >= rect2Pos.y);
	}

	bool isPointCollidingRect(const Vector2 p, const Rectangle rect)
	{
		return p.x <= rect.pos.x + rect.width && p.x >= rect.pos.x &&
			p.y <= rect.pos.y + rect.height && p.y >= rect.pos.y;
	}
}
