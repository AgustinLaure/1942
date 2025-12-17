#include "vector.h"

#include "raymath.h"

namespace vector
{
	float getMagnitude(const Vector2 v)
	{
		float magnitude = static_cast<float>(sqrt(v.x * v.x + v.y * v.y));

		return magnitude;
	}

	Vector2 getNormalized(const Vector2 v)
	{
		Vector2 normalized = v;

		float vMagnitude = getMagnitude(v);

		if (vMagnitude > 0)
		{
			normalized.x /= vMagnitude;
			normalized.y /= vMagnitude;
		}
		else
		{
			normalized.x = 0;
			normalized.y = 0;
		}

		return normalized;
	}

	float getDegreeFromTwoPoints(const Vector2 pos1, const Vector2 pos2)
	{
		float degree = 0.0f;

		double op = pos2.y - pos1.y;
		double ad = pos2.x - pos1.x;

		degree = static_cast<float>(atan2(op, ad));

		degree *= RAD2DEG;

		return degree;
	}
	
	Vector2 getDegreeToVector2(float degree)
	{
		degree *= DEG2RAD;

		Vector2 dir = { cosf(degree), sinf(degree) };

		return dir;
	}
}
