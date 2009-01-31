#include "common.hpp"

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

