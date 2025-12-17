#pragma once

#include "raylib.h"

#include "shape.h"

namespace renderer
{
	void drawSprite(Texture2D& texture, const shape::Rectangle shape, const Color color);
}

