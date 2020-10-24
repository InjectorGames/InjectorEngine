#pragma once
#include <string>
#include <cstdlib>

namespace Injector
{
	struct SizeVector2 final
	{
		size_t x, y;

		SizeVector2() noexcept;
		explicit SizeVector2(size_t xy) noexcept;
		SizeVector2(size_t x, size_t y) noexcept;

		std::string getString() const noexcept;

		bool operator==(const SizeVector2& vector) const noexcept;
		bool operator!=(const SizeVector2& vector) const noexcept;

		// (0, 0)
		static const SizeVector2 zero;
		// (1, 1)
		static const SizeVector2 one;
		// (SIZE_MAX, SIZE_MAX)
		static const SizeVector2 maximum;

		static bool less(
			const SizeVector2& a,
			const SizeVector2& b) noexcept;
	};
}
