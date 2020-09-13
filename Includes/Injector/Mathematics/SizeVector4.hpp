#pragma once
#include "Injector/Mathematics/SizeVector3.hpp"

namespace Injector
{
	struct SizeVector4
	{
		size_t x, y, z, w;

		SizeVector4();
		SizeVector4(size_t xyzw);
		SizeVector4(size_t x, size_t y, size_t z, size_t w);
		SizeVector4(const SizeVector2& vector, size_t z, size_t w);
		SizeVector4(size_t x, const SizeVector2& vector, size_t w);
		SizeVector4(size_t x, size_t y, const SizeVector2& vector);
		SizeVector4(const SizeVector3& vector, size_t w);
		SizeVector4(size_t x, const SizeVector3& vector);

		SizeVector2 getSizeVector2() const noexcept;
		SizeVector3 getSizeVector3() const noexcept;

		bool operator==(const SizeVector4& vector) const noexcept;
		bool operator!=(const SizeVector4& vector) const noexcept;

		static const SizeVector4 zero;
		static const SizeVector4 one;
		static const SizeVector4 maximum;
	};
}
