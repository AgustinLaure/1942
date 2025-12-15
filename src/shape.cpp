#include "shape.h"

namespace shape
{
	bool isRectOnRect(Vector2 rect1Pos, int rect1Width, int rect1Height, Vector2 rect2Pos, int rect2Width, int rect2Height)
	{
		return (rect1Pos.x <= rect2Pos.x + rect2Width
			&& rect1Pos.x + rect1Width >= rect2Pos.x
			&& rect1Pos.y <= rect2Pos.y + rect2Height
			&& rect1Pos.y + rect1Height >= rect2Pos.y);
	}

	bool isPointCollidingRect(Vector2 p, Rectangle rect)
	{
		return p.x <= rect.pos.x + rect.width && p.x >= rect.pos.x &&
			p.y <= rect.pos.y + rect.height && p.y >= rect.pos.y;
	}
}
