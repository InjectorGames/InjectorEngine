#pragma once
#include "Vector4.hpp"

namespace Injector
{
	class Color
	{
	 public:
		static FloatVector4 toVector(
			uint8_t r,
			uint8_t g,
			uint8_t b,
			uint8_t a) noexcept;
		static FloatVector4 toVector(
			const ByteVector4& rgba) noexcept;

		static void toRGBA(
			const FloatVector4& vector,
			uint8_t& r,
			uint8_t& g,
			uint8_t& b,
			uint8_t& a) noexcept;
		static void toRGBA(
			const FloatVector4& vector,
			ByteVector4& rgba) noexcept;
	};
}