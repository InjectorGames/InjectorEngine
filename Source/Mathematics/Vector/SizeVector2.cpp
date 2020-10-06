#include "Injector/Mathematics/Vector/SizeVector2.hpp"

#include <tuple>
#include <sstream>

namespace Injector
{
	SizeVector2::SizeVector2() noexcept :
		x(0),
		y(0)
	{
	}
	SizeVector2::SizeVector2(
		size_t xy) noexcept :
		x(xy),
		y(xy)
	{
	}
	SizeVector2::SizeVector2(
		size_t _x,
		size_t _y) noexcept :
		x(_x),
		y(_y)
	{
	}

	std::string SizeVector2::getString() const noexcept
	{
		auto ss = std::stringstream();
		ss << x << " " << y;
		return ss.str();
	}

	bool SizeVector2::operator==(const SizeVector2& vector) const noexcept
	{
		return
			x == vector.x &&
			y == vector.y;
	}
	bool SizeVector2::operator!=(const SizeVector2& vector) const noexcept
	{
		return
			x != vector.x ||
			y != vector.y;
	}

	const SizeVector2 SizeVector2::zero = SizeVector2(0);
	const SizeVector2 SizeVector2::one = SizeVector2(1);
	const SizeVector2 SizeVector2::maximum = SizeVector2(SIZE_MAX);

	bool SizeVector2::less(
		const SizeVector2& a,
		const SizeVector2& b) noexcept
	{
		return std::tie(a.x, a.y) <
			std::tie(b.x, b.y);
	}
}
