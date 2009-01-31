#include <cmath>
#include "math.hpp"
#include "angle.hpp"

namespace Toodeloo
{
	namespace Math
	{
		float
			Radians::getFullCircle() const
			{
				return 2 * Toodeloo::Math::PI;
			}

		float
			Degrees::getFullCircle() const
			{
				return 360.0;
			}

			float
			Angle::cos() const
			{
				return std::cos(Radians(*this).value());
			}

		float
			Angle::sin() const
			{
				return std::sin(Radians(*this).value());
			}

		float
			Angle::tan() const
			{
				return std::tan(Radians(*this).value());
			}
	}
}
