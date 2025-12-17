#pragma once

#include "raylib.h"

namespace vector
{
	float getMagnitude(const Vector2 v);
	Vector2 getNormalized(const Vector2 v);
	float getDegreeFromTwoPoints(Vector2 pos1, Vector2 pos2);
	Vector2 getDegreeToVector2(float degree);
}

