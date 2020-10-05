#pragma once
#include "Injector/Mathematics/Vector/SizeVector2.hpp"

namespace Injector
{
	struct SizeVector3 final
	{
		size_t x, y, z;

		SizeVector3() noexcept;
		explicit SizeVector3(size_t xyz) noexcept;
		SizeVector3(size_t x, size_t y, size_t z) noexcept;
		SizeVector3(const SizeVector2& vectorS, size_t z) noexcept;
		SizeVector3(size_t x, const SizeVector2& vector) noexcept;

		std::string getString() const noexcept;
		SizeVector2 getSizeVector2() const noexcept;

		bool operator==(const SizeVector3& vector) const noexcept;
		bool operator!=(const SizeVector3& vector) const noexcept;

		static const SizeVector3 zero;
		static const SizeVector3 one;
		static const SizeVector3 maximum;

		static bool less(
			const SizeVector3& a,
			const SizeVector3& b) noexcept;
	};
}
