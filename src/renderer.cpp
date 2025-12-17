#include "renderer.h"

namespace renderer
{
	void drawSprite(Texture2D& texture, const shape::Rectangle shape, const Color color)
	{
		DrawTexturePro(texture, { 0,0,static_cast<float>(texture.width), static_cast<float>(texture.height) }, { shape.pos.x, shape.pos.y, shape.width,shape.height }, { 0.f,0.f }, 0, color);
	}
}
