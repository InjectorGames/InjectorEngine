#include "Injector/Mathematics/Color.hpp"

namespace Injector
{
	Vector4 Color::toVector(
		uint8_t r,
		uint8_t g,
		uint8_t b,
		uint8_t a) noexcept
	{
		return Vector4(
			static_cast<float>(r) / 255.0f,
			static_cast<float>(g) / 255.0f,
			static_cast<float>(b) / 255.0f,
			static_cast<float>(a) / 255.0f);
	}
	void Color::toRGBA(
		const Vector4& vector,
		uint8_t& r,
		uint8_t& g,
		uint8_t& b,
		uint8_t& a) noexcept
	{
		r = static_cast<uint8_t>(vector.x * 255.0f);
		g = static_cast<uint8_t>(vector.y * 255.0f);
		b = static_cast<uint8_t>(vector.z * 255.0f);
		a = static_cast<uint8_t>(vector.w * 255.0f);
	}
}
