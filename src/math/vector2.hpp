#ifndef VECTOR2_HPP
#define VECTOR2_HPP

namespace Toodeloo
{
	namespace Math
	{
		struct Vector2
			: boost::addable<Vector2
			, boost::subtractable<Vector2
			, boost::multipliable<Vector2
			, boost::multipliable<Vector2, float
			, boost::dividable<Vector2
			, boost::dividable<Vector2, float
			> > > > > >
		{
			Vector2() : x(0.0), y(0.0) { }
			Vector2(float x, float y) : x(x), y(y) { }
			Vector2(const Vector2& v) : x(v.x), y(v.y) { }

			Vector2& operator+=(const Vector2&);
			Vector2& operator-=(const Vector2&);
			Vector2& operator*=(float);
			Vector2& operator*=(const Vector2&);
			Vector2& operator/=(float);
			Vector2& operator=(const Vector2&);

			Vector2 operator-() const
			{
				return Vector2(-x, -y);
			}

			float x, y;
		};
	}
}

#endif

