#ifndef VECTOR2_HPP
#define VECTOR2_HPP

namespace Toodeloo
{
	namespace Math
	{
		struct Vector2
		{
			Vector2() : x(0.0), y(0.0) { }
			Vector2(float x, float y) : x(x), y(y) { }
			Vector2(const Vector2& v) : x(v.x), y(v.y) { }

			float x, y;
		};
	}
}

#endif

