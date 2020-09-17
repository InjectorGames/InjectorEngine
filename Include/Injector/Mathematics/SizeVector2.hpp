#pragma once
#include <cstdlib>

namespace Injector
{
	struct SizeVector2
	{
		size_t x, y;

		SizeVector2();
		SizeVector2(size_t xy);
		SizeVector2(size_t x, size_t y);

		bool operator==(const SizeVector2& vector) const noexcept;
		bool operator!=(const SizeVector2& vector) const noexcept;

		static const SizeVector2 zero;
		static const SizeVector2 one;
		static const SizeVector2 maximum;
	};
}
