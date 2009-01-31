#include "../common.hpp"

namespace Toodeloo
{
	namespace Math
	{
		Vector3&
			Vector3::operator+=(const Vector3& v)
			{
				x += v.x;
				y += v.y;
				z += v.z;
				return *this;
			}

		Vector3&
			Vector3::operator=(const Vector3& v)
			{
				x = v.x;
				y = v.y;
				z = v.z;
				return *this;
			}

		Vector3&
			Vector3::operator-=(const Vector3& v)
			{
				x -= v.x;
				y -= v.y;
				z -= v.z;
				return *this;
			}

		Vector3&
			Vector3::operator*=(float f)
			{
				x *= f;
				y *= f;
				z *= f;
				return *this;
			}

		Vector3&
			Vector3::operator*=(const Vector3& v)
			{
				x *= v.x;
				y *= v.y;
				z *= v.z;
				return *this;
			}

		Vector3&
			Vector3::operator/=(float f)
			{
				x /= f;
				y /= f;
				z /= f;
				return *this;
			}

		float
			Vector3::getMagnitude() const
			{
				return std::fabs(this->dotProduct(*this));
			}

		float
			Vector3::dotProduct(const Vector3& v) const
			{
				return x * v.x +
					y * v.y +
					z * v.z;
			}

		Vector3
			Vector3::crossProduct(const Vector3& v) const
			{
				return Vector3(
						y * v.z - z * v.y,
						z * v.x - x * v.z,
						x * v.y - y * v.x
						);
			}


		Vector3
			Vector3::getNormalized() const
			{
				return Vector3(*this).normalize();
			}

		Vector3&
			Vector3::normalize()
			{
				float magnitude = getMagnitude();
				if(magnitude < std::numeric_limits<float>::epsilon())
					return *this;

				x /= magnitude;
				y /= magnitude;
				z /= magnitude;

				return *this;
			}
	}
}
