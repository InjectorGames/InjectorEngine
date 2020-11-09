#pragma once

namespace Injector
{
	class Angle
	{
	 public:
		static float toDegrees(float radians) noexcept;
		static double toDegrees(double radians) noexcept;

		static float toRadians(float degrees) noexcept;
		static double toRadians(double degrees) noexcept;
	};
}
