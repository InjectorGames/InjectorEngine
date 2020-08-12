#pragma once
#include <injector/defines.hpp>

namespace INJECTOR_NAMESPACE
{
	class Converter
	{
	public:
		static float toDegrees(float value);
		static double toDegrees(double value);
		static float toRadians(float value);
		static double toRadians(double value);
	};
}
