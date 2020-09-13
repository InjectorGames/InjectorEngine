#include "Injector/Mathematics/SizeVector2.hpp"

namespace Injector
{
	SizeVector2::SizeVector2() :
		x(0), y(0)
	{}
	SizeVector2::SizeVector2(size_t xy) :
		x(xy), y(xy)
	{}
	SizeVector2::SizeVector2(size_t _x, size_t _y) :
		x(_x), y(_y)
	{}

	bool SizeVector2::operator==(const SizeVector2& vector) const noexcept
	{
		return x == vector.x && y == vector.y;
	}
	bool SizeVector2::operator!=(const SizeVector2& vector) const noexcept
	{
		return !(*this == vector);
	}

	const SizeVector2 SizeVector2::zero = SizeVector2(0);
	const SizeVector2 SizeVector2::one = SizeVector2(1);
	const SizeVector2 SizeVector2::maximum = SizeVector2(SIZE_MAX);
}
