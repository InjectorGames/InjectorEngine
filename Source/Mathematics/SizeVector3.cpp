#include "Injector/Mathematics/SizeVector3.hpp"

namespace Injector
{
	SizeVector3::SizeVector3() :
		x(0), y(0), z(0)
	{}
	SizeVector3::SizeVector3(size_t xyz) :
		x(xyz), y(xyz), z(xyz)
	{}
	SizeVector3::SizeVector3(size_t _x, size_t _y, size_t _z) :
		x(_x), y(_y), z(_z)
	{}
	SizeVector3::SizeVector3(const SizeVector2& vector, size_t _z) :
		x(vector.x), y(vector.y), z(_z)
	{}
	SizeVector3::SizeVector3(size_t _x, const SizeVector2& vector) :
		x(_x), y(vector.x), z(vector.y)
	{}

    SizeVector2 SizeVector3::getSizeVector2() const noexcept
    {
        return SizeVector2(x, y);
    }

	bool SizeVector3::operator==(const SizeVector3& vector) const noexcept
	{
		return x == vector.x && y == vector.y && z == vector.z;
	}
	bool SizeVector3::operator!=(const SizeVector3& vector) const noexcept
	{
		return !(*this == vector);
	}

	const SizeVector3 SizeVector3::zero = SizeVector3(0);
	const SizeVector3 SizeVector3::one = SizeVector3(1);
	const SizeVector3 SizeVector3::maximum = SizeVector3(SIZE_MAX);
}
