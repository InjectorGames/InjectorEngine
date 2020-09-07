#include "Injector/Mathematics/IntVector2.hpp"
#include <cmath>

namespace Injector
{
	IntVector2::IntVector2() :
		x(0), y(0)
	{}
	IntVector2::IntVector2(int xy) :
		x(xy), y(xy)
	{}
	IntVector2::IntVector2(int _x, int _y) :
		x(_x), y(_y)
	{}

	int IntVector2::getDotProduct(const IntVector2& vector) const noexcept
	{
		auto result = *this * vector;
		return vector.x + vector.y;
	}
	float IntVector2::getLength() const noexcept
	{
		return sqrtf(static_cast<float>(getDotProduct(*this)));
	}
	float IntVector2::getDistance(const IntVector2& vector) const noexcept
	{
		return sqrtf(static_cast<float>(getDotProduct(*this - vector)));
	}
	IntVector2 IntVector2::getReflected(const IntVector2& normal) const noexcept
	{
		return *this - normal * getDotProduct(normal) * 2;
	}

	bool IntVector2::operator==(const IntVector2& vector) const noexcept
	{
		return x == vector.x && y == vector.y;
	}
	bool IntVector2::operator!=(const IntVector2& vector) const noexcept
	{
		return !(*this == vector);
	}

	IntVector2& IntVector2::operator--() noexcept
	{
		--x; --y;
		return *this;
	}
	IntVector2& IntVector2::operator++() noexcept
	{
		++x; ++y;
		return *this;
	}
	IntVector2 IntVector2::operator--(int) noexcept
	{
		auto result = IntVector2(*this);
		--x; --y;
		return result;
	}
	IntVector2 IntVector2::operator++(int) noexcept
	{
		auto result = IntVector2(*this);
		++x; ++y;
		return result;
	}
	IntVector2 IntVector2::operator-() const noexcept
	{
		return IntVector2(-x, -y);
	}

	IntVector2 IntVector2::operator-(const IntVector2& vector) const noexcept
	{
		return IntVector2(x - vector.x, y - vector.y);
	}
	IntVector2 IntVector2::operator+(const IntVector2& vector) const noexcept
	{
		return IntVector2(x + vector.x, y + vector.y);
	}
	IntVector2 IntVector2::operator/(const IntVector2& vector) const noexcept
	{
		return IntVector2(x / vector.x, y / vector.y);
	}
	IntVector2 IntVector2::operator*(const IntVector2& vector) const noexcept
	{
		return IntVector2(x * vector.x, y * vector.y);
	}
	IntVector2 IntVector2::operator%(const IntVector2& vector) const noexcept
	{
		return IntVector2(x % vector.x, y % vector.y);
	}
	IntVector2 IntVector2::operator|(const IntVector2& vector) const noexcept
	{
		return IntVector2(x | vector.x, y | vector.y);
	}
	IntVector2 IntVector2::operator&(const IntVector2& vector) const noexcept
	{
		return IntVector2(x & vector.x, y & vector.y);
	}
	IntVector2 IntVector2::operator^(const IntVector2& vector) const noexcept
	{
		return IntVector2(x ^ vector.x, y ^ vector.y);
	}
	IntVector2 IntVector2::operator<<(const IntVector2& vector) const noexcept
	{
		return IntVector2(x << vector.x, y << vector.y);
	}
	IntVector2 IntVector2::operator>>(const IntVector2& vector) const noexcept
	{
		return IntVector2(x >> vector.x, y >> vector.y);
	}
	IntVector2& IntVector2::operator-=(const IntVector2& vector) noexcept
	{
		x -= vector.x;
		y -= vector.y;
		return *this;
	}
	IntVector2& IntVector2::operator+=(const IntVector2& vector) noexcept
	{
		x += vector.x;
		y += vector.y;
		return *this;
	}
	IntVector2& IntVector2::operator/=(const IntVector2& vector) noexcept
	{
		x /= vector.x;
		y /= vector.y;
		return *this;
	}
	IntVector2& IntVector2::operator*=(const IntVector2& vector) noexcept
	{
		x *= vector.x;
		y *= vector.y;
		return *this;
	}
	IntVector2& IntVector2::operator%=(const IntVector2& vector) noexcept
	{
		x %= vector.x;
		y %= vector.y;
		return *this;
	}
	IntVector2& IntVector2::operator|=(const IntVector2& vector) noexcept
	{
		x |= vector.x;
		y |= vector.y;
		return *this;
	}
	IntVector2& IntVector2::operator&=(const IntVector2& vector) noexcept
	{
		x &= vector.x;
		y &= vector.y;
		return *this;
	}
	IntVector2& IntVector2::operator^=(const IntVector2& vector) noexcept
	{
		x ^= vector.x;
		y ^= vector.y;
		return *this;
	}
	IntVector2& IntVector2::operator<<=(const IntVector2& vector) noexcept
	{
		x <<= vector.x;
		y <<= vector.y;
		return *this;
	}
	IntVector2& IntVector2::operator>>=(const IntVector2& vector) noexcept
	{
		x >>= vector.x;
		y >>= vector.y;
		return *this;
	}

	IntVector2 IntVector2::operator-(int value) const noexcept
	{
		return IntVector2(x - value, y - value);
	}
	IntVector2 IntVector2::operator+(int value) const noexcept
	{
		return IntVector2(x + value, y + value);
	}
	IntVector2 IntVector2::operator/(int value) const noexcept
	{
		return IntVector2(x / value, y / value);
	}
	IntVector2 IntVector2::operator*(int value) const noexcept
	{
		return IntVector2(x * value, y * value);
	}
	IntVector2 IntVector2::operator%(int value) const noexcept
	{
		return IntVector2(x % value, y % value);
	}
	IntVector2 IntVector2::operator|(int value) const noexcept
	{
		return IntVector2(x | value, y | value);
	}
	IntVector2 IntVector2::operator&(int value) const noexcept
	{
		return IntVector2(x & value, y & value);
	}
	IntVector2 IntVector2::operator^(int value) const noexcept
	{
		return IntVector2(x ^ value, y ^ value);
	}
	IntVector2 IntVector2::operator<<(int value) const noexcept
	{
		return IntVector2(x << value, y << value);
	}
	IntVector2 IntVector2::operator>>(int value) const noexcept
	{
		return IntVector2(x >> value, y >> value);
	}
	IntVector2& IntVector2::operator-=(int value) noexcept
	{
		x -= value;
		y -= value;
		return *this;
	}
	IntVector2& IntVector2::operator+=(int value) noexcept
	{
		x += value;
		y += value;
		return *this;
	}
	IntVector2& IntVector2::operator/=(int value) noexcept
	{
		x /= value;
		y /= value;
		return *this;
	}
	IntVector2& IntVector2::operator*=(int value) noexcept
	{
		x *= value;
		y *= value;
		return *this;
	}
	IntVector2& IntVector2::operator%=(int value) noexcept
	{
		x %= value;
		y %= value;
		return *this;
	}
	IntVector2& IntVector2::operator|=(int value) noexcept
	{
		x |= value;
		y |= value;
		return *this;
	}
	IntVector2& IntVector2::operator&=(int value) noexcept
	{
		x &= value;
		y &= value;
		return *this;
	}
	IntVector2& IntVector2::operator^=(int value) noexcept
	{
		x ^= value;
		y ^= value;
		return *this;
	}
	IntVector2& IntVector2::operator<<=(int value) noexcept
	{
		x <<= value;
		y <<= value;
		return *this;
	}
	IntVector2& IntVector2::operator>>=(int value) noexcept
	{
		x >>= value;
		y >>= value;
		return *this;
	}

	const IntVector2 IntVector2::zero = IntVector2(0);
	const IntVector2 IntVector2::minusOne = IntVector2(-1);
	const IntVector2 IntVector2::one = IntVector2(1);
}
