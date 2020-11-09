#pragma once
#include "Injector/Mathematics/Vector/Vector4.hpp"

namespace Injector
{
	class Color
	{
	 public:
		static Vector4 toVector(
			uint8_t r,
			uint8_t g,
			uint8_t b,
			uint8_t a) noexcept;
		static void toRGBA(
			const Vector4& vector,
			uint8_t& r,
			uint8_t& g,
			uint8_t& b,
			uint8_t& a) noexcept;
	};
}