#include <injector/int_vector2.hpp>

#include <cmath>

namespace INJECTOR_NAMESPACE
{
	IntVector2::IntVector2(int _x, int _y) :
		x(_x), y(_y)
	{}

	float IntVector2::getMagnitude()
	{
		return std::sqrtf(static_cast<float>(x * x + y * y));
	}
	int IntVector2::getDot(const IntVector2& other)
	{
		return x * other.x + y * other.y;
	}
	float IntVector2::getDistance(const IntVector2& other)
	{
		return std::sqrtf(static_cast<float>(
			x - other.x * x - other.x +
			y - other.y * y - other.y));
	}

	bool IntVector2::operator==(const IntVector2& other)
	{
		return x == other.x && y == other.y;
	}
	bool IntVector2::operator!=(const IntVector2& other)
	{
		return x != other.x && y != other.y;
	}

	IntVector2& IntVector2::operator--()
	{
		--x;
		--y;
		return *this;
	}
	IntVector2& IntVector2::operator++()
	{
		++x;
		++y;
		return *this;
	}
	IntVector2 IntVector2::operator--(int)
	{
		auto result = IntVector2(*this);
		--x;
		--y;
		return result;
	}
	IntVector2 IntVector2::operator++(int)
	{
		auto result = IntVector2(*this);
		++x;
		++y;
		return result;
	}

	IntVector2 IntVector2::operator-(const IntVector2& other)
	{
		return IntVector2(x - other.x, y - other.y);
	}
	IntVector2 IntVector2::operator+(const IntVector2& other)
	{
		return IntVector2(x + other.x, y + other.y);
	}
	IntVector2 IntVector2::operator/(const IntVector2& other)
	{
		return IntVector2(x / other.x, y / other.y);
	}
	IntVector2 IntVector2::operator*(const IntVector2& other)
	{
		return IntVector2(x * other.x, y * other.y);
	}
	IntVector2 IntVector2::operator%(const IntVector2& other)
	{
		return IntVector2(x % other.x, y % other.y);
	}
	IntVector2 IntVector2::operator|(const IntVector2& other)
	{
		return IntVector2(x | other.x, y | other.y);
	}
	IntVector2 IntVector2::operator&(const IntVector2& other)
	{
		return IntVector2(x & other.x, y & other.y);
	}
	IntVector2 IntVector2::operator^(const IntVector2& other)
	{
		return IntVector2(x ^ other.x, y ^ other.y);
	}
	IntVector2 IntVector2::operator<<(const IntVector2& other)
	{
		return IntVector2(x << other.x, y << other.y);
	}
	IntVector2 IntVector2::operator>>(const IntVector2& other)
	{
		return IntVector2(x >> other.x, y >> other.y);
	}
	IntVector2& IntVector2::operator-=(const IntVector2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}
	IntVector2& IntVector2::operator+=(const IntVector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	IntVector2& IntVector2::operator/=(const IntVector2& other)
	{
		x /= other.x;
		y /= other.y;
		return *this;
	}
	IntVector2& IntVector2::operator*=(const IntVector2& other)
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}
	IntVector2& IntVector2::operator%=(const IntVector2& other)
	{
		x %= other.x;
		y %= other.y;
		return *this;
	}
	IntVector2& IntVector2::operator|=(const IntVector2& other)
	{
		x |= other.x;
		y |= other.y;
		return *this;
	}
	IntVector2& IntVector2::operator&=(const IntVector2& other)
	{
		x &= other.x;
		y &= other.y;
		return *this;
	}
	IntVector2& IntVector2::operator^=(const IntVector2& other)
	{
		x ^= other.x;
		y ^= other.y;
		return *this;
	}
	IntVector2& IntVector2::operator<<=(const IntVector2& other)
	{
		x <<= other.x;
		y <<= other.y;
		return *this;
	}
	IntVector2& IntVector2::operator>>=(const IntVector2& other)
	{
		x >>= other.x;
		y >>= other.y;
		return *this;
	}

	IntVector2 IntVector2::operator-(int value)
	{
		return IntVector2(x - value, y - value);
	}
	IntVector2 IntVector2::operator+(int value)
	{
		return IntVector2(x + value, y + value);
	}
	IntVector2 IntVector2::operator/(int value)
	{
		return IntVector2(x / value, y / value);
	}
	IntVector2 IntVector2::operator*(int value)
	{
		return IntVector2(x * value, y * value);
	}
	IntVector2 IntVector2::operator%(int value)
	{
		return IntVector2(x % value, y % value);
	}
	IntVector2 IntVector2::operator|(int value)
	{
		return IntVector2(x | value, y | value);
	}
	IntVector2 IntVector2::operator&(int value)
	{
		return IntVector2(x & value, y & value);
	}
	IntVector2 IntVector2::operator^(int value)
	{
		return IntVector2(x ^ value, y ^ value);
	}
	IntVector2 IntVector2::operator<<(int value)
	{
		return IntVector2(x << value, y << value);
	}
	IntVector2 IntVector2::operator>>(int value)
	{
		return IntVector2(x >> value, y >> value);
	}
	IntVector2& IntVector2::operator-=(int value)
	{
		x -= value;
		y -= value;
		return *this;
	}
	IntVector2& IntVector2::operator+=(int value)
	{
		x += value;
		y += value;
		return *this;
	}
	IntVector2& IntVector2::operator/=(int value)
	{
		x /= value;
		y /= value;
		return *this;
	}
	IntVector2& IntVector2::operator*=(int value)
	{
		x *= value;
		y *= value;
		return *this;
	}
	IntVector2& IntVector2::operator%=(int value)
	{
		x %= value;
		y %= value;
		return *this;
	}
	IntVector2& IntVector2::operator|=(int value)
	{
		x |= value;
		y |= value;
		return *this;
	}
	IntVector2& IntVector2::operator&=(int value)
	{
		x &= value;
		y &= value;
		return *this;
	}
	IntVector2& IntVector2::operator^=(int value)
	{
		x ^= value;
		y ^= value;
		return *this;
	}
	IntVector2& IntVector2::operator<<=(int value)
	{
		x <<= value;
		y <<= value;
		return *this;
	}
	IntVector2& IntVector2::operator>>=(int value)
	{
		x >>= value;
		y >>= value;
		return *this;
	}
}
