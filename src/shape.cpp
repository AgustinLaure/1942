#include "shape.h"

namespace shape
{
	Rectangle initRectangle(const float width, const float height, const Vector2 pos)
	{
		Rectangle newRect;

		newRect.width = width;
		newRect.height = height;
		newRect.pos = pos;

		return newRect;
	}

	Vector2 getRectangleCenter(const Rectangle rectangle)
	{
		return { rectangle.pos.x + rectangle.width / 2, rectangle.pos.y + rectangle.height / 2 };
	}

	bool isRectOnRect(const Rectangle rect1, const Rectangle rect2)
	{
		return (rect1.pos.x <= rect2.pos.x + rect2.width
			&& rect1.pos.x + rect1.width >= rect2.pos.x
			&& rect1.pos.y <= rect2.pos.y + rect2.height
			&& rect1.pos.y + rect1.height >= rect2.pos.y);
	}

	bool isPointCollidingRect(const Vector2 p, const Rectangle rect)
	{
		return p.x <= rect.pos.x + rect.width && p.x >= rect.pos.x &&
			p.y <= rect.pos.y + rect.height && p.y >= rect.pos.y;
	}
}
