#include "Injector/Mathematics/Angle.hpp"

#define _USE_MATH_DEFINES
#include <cmath>

namespace Injector
{
	float Angle::toDegrees(float radians) noexcept
	{
		return radians * (180.0f / static_cast<float>(M_PI));
	}
	double Angle::toDegrees(double radians) noexcept
	{
		return radians * (180.0 / M_PI);
	}

	float Angle::toRadians(float degrees) noexcept
	{
		return degrees * (static_cast<float>(M_PI) / 180.0f);
	}
	double Angle::toRadians(double degrees) noexcept
	{
		return degrees * (M_PI / 180.0);
	}
}
