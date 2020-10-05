#include "Injector/Mathematics/Vector/SizeVector3.hpp"
#include <sstream>

namespace Injector
{
	SizeVector3::SizeVector3() noexcept :
		x(0),
		y(0),
		z(0)
	{
	}
	SizeVector3::SizeVector3(
		size_t xyz) noexcept :
		x(xyz),
		y(xyz),
		z(xyz)
	{
	}
	SizeVector3::SizeVector3(
		size_t _x,
		size_t _y,
		size_t _z) noexcept :
		x(_x),
		y(_y),
		z(_z)
	{
	}
	SizeVector3::SizeVector3(
		const SizeVector2& vector,
		size_t _z) noexcept :
		x(vector.x),
		y(vector.y),
		z(_z)
	{
	}
	SizeVector3::SizeVector3(
		size_t _x,
		const SizeVector2& vector) noexcept :
		x(_x),
		y(vector.x),
		z(vector.y)
	{
	}

	std::string SizeVector3::getString() const noexcept
	{
		auto ss = std::stringstream();
		ss << x << " " << y << " " << z;
		return ss.str();
	}
	SizeVector2 SizeVector3::getSizeVector2() const noexcept
	{
		return SizeVector2(x, y);
	}

	bool SizeVector3::operator==(const SizeVector3& vector) const noexcept
	{
		return
			x == vector.x &&
			y == vector.y &&
			z == vector.z;
	}
	bool SizeVector3::operator!=(const SizeVector3& vector) const noexcept
	{
		return
			x != vector.x ||
			y != vector.y ||
			z != vector.z;
	}

	const SizeVector3 SizeVector3::zero = SizeVector3(0);
	const SizeVector3 SizeVector3::one = SizeVector3(1);
	const SizeVector3 SizeVector3::maximum = SizeVector3(SIZE_MAX);

	bool SizeVector3::less(
		const SizeVector3& a,
		const SizeVector3& b) noexcept
	{
		return std::tie(a.x, a.y, a.z) <
			std::tie(b.x, b.y, b.z);
	}
}
