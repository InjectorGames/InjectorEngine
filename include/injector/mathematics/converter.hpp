#pragma once

namespace Injector::Mathematics
{
	class Converter
	{
	public:
		static float toDegrees(float radians);
		static double toDegrees(double radians);
		static float toRadians(float degrees);
		static double toRadians(double degrees);
	};
}
