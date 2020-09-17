#pragma once

namespace Injector
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
