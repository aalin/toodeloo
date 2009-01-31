#ifndef VECTOR3_HPP
#define VECTOR3_HPP

namespace Toodeloo
{
	namespace Math
	{
		struct Vector3
			: boost::addable<Vector3
			  , boost::subtractable<Vector3
			  , boost::multipliable<Vector3
			  , boost::multipliable<Vector3, float
			  , boost::dividable<Vector3
			  , boost::dividable<Vector3, float
			  > > > > > >
		{
			Vector3() : x(0.0), y(0.0), z(0.0) { }
			Vector3(float x, float y, float z) : x(x), y(y), z(z) { }
			Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) { }

			Vector3& operator+=(const Vector3&);
			Vector3& operator-=(const Vector3&);
			Vector3& operator*=(float);
			Vector3& operator*=(const Vector3&);
			Vector3& operator/=(float);
			Vector3& operator=(const Vector3&);

			Vector3 operator-() const
			{
				return Vector3(-x, -y, -z);
			}

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

