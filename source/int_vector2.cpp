#include <injector/int_vector2.hpp>
#include <cmath>

namespace INJECTOR_NAMESPACE
{
	IntVector2::IntVector2() :
		x(0), y(0)
	{}
	IntVector2::IntVector2(int _x, int _y) :
		x(_x), y(_y)
	{}

	float IntVector2::getMagnitude() const noexcept
	{
		return std::sqrtf(static_cast<float>(x * x + y * y));
	}
	int IntVector2::getDot(const IntVector2& other) const noexcept
	{
		return x * other.x + y * other.y;
	}
	float IntVector2::getDistance(const IntVector2& other) const noexcept
	{
		return std::sqrtf(static_cast<float>(
			x - other.x * x - other.x +
			y - other.y * y - other.y));
	}
	IntVector2 IntVector2::getNegative() const noexcept
	{
		return IntVector2(-x, -y);
	}

	bool IntVector2::operator==(const IntVector2& other) const noexcept
	{
		return x == other.x && y == other.y;
	}
	bool IntVector2::operator!=(const IntVector2& other) const noexcept
	{
		return x != other.x || y != other.y;
	}

	IntVector2& IntVector2::operator--() noexcept
	{
		--x;
		--y;
		return *this;
	}
	IntVector2& IntVector2::operator++() noexcept
	{
		++x;
		++y;
		return *this;
	}
	IntVector2 IntVector2::operator--(int) noexcept
	{
		auto result = IntVector2(*this);
		--x;
		--y;
		return result;
	}
	IntVector2 IntVector2::operator++(int) noexcept
	{
		auto result = IntVector2(*this);
		++x;
		++y;
		return result;
	}

	IntVector2 IntVector2::operator-(const IntVector2& other) const noexcept
	{
		return IntVector2(x - other.x, y - other.y);
	}
	IntVector2 IntVector2::operator+(const IntVector2& other) const noexcept
	{
		return IntVector2(x + other.x, y + other.y);
	}
	IntVector2 IntVector2::operator/(const IntVector2& other) const noexcept
	{
		return IntVector2(x / other.x, y / other.y);
	}
	IntVector2 IntVector2::operator*(const IntVector2& other) const noexcept
	{
		return IntVector2(x * other.x, y * other.y);
	}
	IntVector2 IntVector2::operator%(const IntVector2& other) const noexcept
	{
		return IntVector2(x % other.x, y % other.y);
	}
	IntVector2 IntVector2::operator|(const IntVector2& other) const noexcept
	{
		return IntVector2(x | other.x, y | other.y);
	}
	IntVector2 IntVector2::operator&(const IntVector2& other) const noexcept
	{
		return IntVector2(x & other.x, y & other.y);
	}
	IntVector2 IntVector2::operator^(const IntVector2& other) const noexcept
	{
		return IntVector2(x ^ other.x, y ^ other.y);
	}
	IntVector2 IntVector2::operator<<(const IntVector2& other) const noexcept
	{
		return IntVector2(x << other.x, y << other.y);
	}
	IntVector2 IntVector2::operator>>(const IntVector2& other) const noexcept
	{
		return IntVector2(x >> other.x, y >> other.y);
	}
	IntVector2& IntVector2::operator=(const IntVector2& other) noexcept
	{
		x = other.x;
		y = other.y;
		return *this;
	}
	IntVector2& IntVector2::operator-=(const IntVector2& other) noexcept
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}
	IntVector2& IntVector2::operator+=(const IntVector2& other) noexcept
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	IntVector2& IntVector2::operator/=(const IntVector2& other) noexcept
	{
		x /= other.x;
		y /= other.y;
		return *this;
	}
	IntVector2& IntVector2::operator*=(const IntVector2& other) noexcept
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}
	IntVector2& IntVector2::operator%=(const IntVector2& other) noexcept
	{
		x %= other.x;
		y %= other.y;
		return *this;
	}
	IntVector2& IntVector2::operator|=(const IntVector2& other) noexcept
	{
		x |= other.x;
		y |= other.y;
		return *this;
	}
	IntVector2& IntVector2::operator&=(const IntVector2& other) noexcept
	{
		x &= other.x;
		y &= other.y;
		return *this;
	}
	IntVector2& IntVector2::operator^=(const IntVector2& other) noexcept
	{
		x ^= other.x;
		y ^= other.y;
		return *this;
	}
	IntVector2& IntVector2::operator<<=(const IntVector2& other) noexcept
	{
		x <<= other.x;
		y <<= other.y;
		return *this;
	}
	IntVector2& IntVector2::operator>>=(const IntVector2& other) noexcept
	{
		x >>= other.x;
		y >>= other.y;
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
	IntVector2& IntVector2::operator=(int value) noexcept
	{
		x = value;
		y = value;
		return *this;
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

	const IntVector2 IntVector2::zero = IntVector2(0, 0);
	const IntVector2 IntVector2::minusOne = IntVector2(-1, -1);
	const IntVector2 IntVector2::one = IntVector2(1, 1);
}
