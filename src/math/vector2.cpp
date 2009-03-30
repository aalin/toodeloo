#include "../common.hpp"

namespace Toodeloo
{
	namespace Math
	{
		Vector2&
		Vector2::operator+=(const Vector2& v)
		{
			x += v.x;
			y += v.y;
			return *this;
		}

		Vector2&
		Vector2::operator=(const Vector2& v)
		{
			x = v.x;
			y = v.y;
			return *this;
		}

		Vector2&
		Vector2::operator-=(const Vector2& v)
		{
			x -= v.x;
			y -= v.y;
			return *this;
		}

		Vector2&
		Vector2::operator*=(float f)
		{
			x *= f;
			y *= f;
			return *this;
		}

		Vector2&
		Vector2::operator*=(const Vector2& v)
		{
			x *= v.x;
			y *= v.y;
			return *this;
		}

		Vector2&
		Vector2::operator/=(float f)
		{
			x /= f;
			y /= f;
			return *this;
		}
	}
}

