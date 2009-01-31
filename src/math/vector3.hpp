#ifndef VECTOR3_HPP
#define VECTOR3_HPP

namespace Toodeloo
{
	namespace Math
	{
		struct Vector3
		{
			Vector3() : x(0.0), y(0.0), z(0.0) { }
			Vector3(float x, float y, float z) : x(x), y(y), z(z) { }
			Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) { }

			float getMagnitude() const;

			float dotProduct(const Vector3& v) const;
			Vector3 crossProduct(const Vector3& v) const;

			Vector3 getNormalized() const;
			Vector3& normalize();

			float x, y, z;
		};
	}
}

#endif

