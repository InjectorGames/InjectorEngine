#include <injector/mathematics/converter.hpp>

#define _USE_MATH_DEFINES
#include <cmath>

namespace INJECTOR_NAMESPACE
{
	float Converter::toDegrees(float radians)
	{
		return radians * (180.0f / static_cast<float>(M_PI));
	}
	double Converter::toDegrees(double radians)
	{
		return radians * (180.0 / M_PI);
	}
	float Converter::toRadians(float degrees)
	{
		return degrees * (static_cast<float>(M_PI) / 180.0f);
	}
	double Converter::toRadians(double degrees)
	{
		return degrees * (M_PI / 180.0);
	}
}
