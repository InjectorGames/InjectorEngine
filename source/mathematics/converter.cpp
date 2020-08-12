#include <injector/mathematics/converter.hpp>

#define _USE_MATH_DEFINES
#include <cmath>

namespace INJECTOR_NAMESPACE
{
	float Converter::toDegrees(float value)
	{
		return value * (static_cast<float>(M_PI) / 180.0f);
	}
	double Converter::toDegrees(double value)
	{
		return value * (M_PI / 180.0);
	}
	float Converter::toRadians(float value)
	{
		return value * (180.0f / static_cast<float>(M_PI));
	}
	double Converter::toRadians(double value)
	{
		return value * (180.0 / M_PI);
	}
}
