#include <injector/int_vector3.hpp>

#include <cmath>

namespace INJECTOR_NAMESPACE
{
	IntVector3::IntVector3(int _x, int _y, int _z) :
		x(_x), y(_y), z(_z)
	{}
	IntVector3::IntVector3(const IntVector2& other, int _z) :
		x(other.x), y(other.y), z(_z)
	{}

	float IntVector3::getMagnitude()
	{
		return std::sqrtf(static_cast<float>(x * x + y * y + z * z));
	}
	int IntVector3::getDot(const IntVector3& other)
	{
		return x * other.x + y * other.y + z * other.z;
	}
	float IntVector3::getDistance(const IntVector3& other)
	{
		return std::sqrtf(static_cast<float>(
			x - other.x * x - other.x +
			y - other.y * y - other.y +
			z - other.z * z - other.z));
	}
	IntVector3 IntVector3::getCross(const IntVector3& other)
	{
		return IntVector3(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x);
	}

	bool IntVector3::operator==(const IntVector3& other)
	{
		return x == other.x && y == other.y && z == other.z;
	}
	bool IntVector3::operator!=(const IntVector3& other)
	{
		return x != other.x && y != other.y && z != other.z;
	}

	IntVector3& IntVector3::operator--()
	{
		--x;
		--y;
		--z;
		return *this;
	}
	IntVector3& IntVector3::operator++()
	{
		++x;
		++y;
		++z;
		return *this;
	}
	IntVector3 IntVector3::operator--(int)
	{
		auto result = IntVector3(*this);
		--x;
		--y;
		--z;
		return result;
	}
	IntVector3 IntVector3::operator++(int)
	{
		auto result = IntVector3(*this);
		++x;
		++y;
		++z;
		return result;
	}

	IntVector3 IntVector3::operator-(const IntVector3& other)
	{
		return IntVector3(x - other.x, y - other.y, z - other.z);
	}
	IntVector3 IntVector3::operator+(const IntVector3& other)
	{
		return IntVector3(x + other.x, y + other.y, z + other.z);
	}
	IntVector3 IntVector3::operator/(const IntVector3& other)
	{
		return IntVector3(x / other.x, y / other.y, z / other.z);
	}
	IntVector3 IntVector3::operator*(const IntVector3& other)
	{
		return IntVector3(x * other.x, y * other.y, z * other.z);
	}
	IntVector3 IntVector3::operator%(const IntVector3& other)
	{
		return IntVector3(x % other.x, y % other.y, z % other.z);
	}
	IntVector3 IntVector3::operator|(const IntVector3& other)
	{
		return IntVector3(x | other.x, y | other.y, z | other.z);
	}
	IntVector3 IntVector3::operator&(const IntVector3& other)
	{
		return IntVector3(x & other.x, y & other.y, z & other.z);
	}
	IntVector3 IntVector3::operator^(const IntVector3& other)
	{
		return IntVector3(x ^ other.x, y ^ other.y, z ^ other.z);
	}
	IntVector3 IntVector3::operator<<(const IntVector3& other)
	{
		return IntVector3(x << other.x, y << other.y, z << other.z);
	}
	IntVector3 IntVector3::operator>>(const IntVector3& other)
	{
		return IntVector3(x >> other.x, y >> other.y, z >> other.z);
	}
	IntVector3& IntVector3::operator-=(const IntVector3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}
	IntVector3& IntVector3::operator+=(const IntVector3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}
	IntVector3& IntVector3::operator/=(const IntVector3& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}
	IntVector3& IntVector3::operator*=(const IntVector3& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}
	IntVector3& IntVector3::operator%=(const IntVector3& other)
	{
		x %= other.x;
		y %= other.y;
		z %= other.z;
		return *this;
	}
	IntVector3& IntVector3::operator|=(const IntVector3& other)
	{
		x |= other.x;
		y |= other.y;
		z |= other.z;
		return *this;
	}
	IntVector3& IntVector3::operator&=(const IntVector3& other)
	{
		x &= other.x;
		y &= other.y;
		z &= other.z;
		return *this;
	}
	IntVector3& IntVector3::operator^=(const IntVector3& other)
	{
		x ^= other.x;
		y ^= other.y;
		z ^= other.z;
		return *this;
	}
	IntVector3& IntVector3::operator<<=(const IntVector3& other)
	{
		x <<= other.x;
		y <<= other.y;
		z <<= other.z;
		return *this;
	}
	IntVector3& IntVector3::operator>>=(const IntVector3& other)
	{
		x >>= other.x;
		y >>= other.y;
		z >>= other.z;
		return *this;
	}

	IntVector3 IntVector3::operator-(int value)
	{
		return IntVector3(x - value, y - value, z - value);
	}
	IntVector3 IntVector3::operator+(int value)
	{
		return IntVector3(x + value, y + value, z + value);
	}
	IntVector3 IntVector3::operator/(int value)
	{
		return IntVector3(x / value, y / value, z / value);
	}
	IntVector3 IntVector3::operator*(int value)
	{
		return IntVector3(x * value, y * value, z * value);
	}
	IntVector3 IntVector3::operator%(int value)
	{
		return IntVector3(x % value, y % value, z % value);
	}
	IntVector3 IntVector3::operator|(int value)
	{
		return IntVector3(x | value, y | value, z | value);
	}
	IntVector3 IntVector3::operator&(int value)
	{
		return IntVector3(x & value, y & value, z & value);
	}
	IntVector3 IntVector3::operator^(int value)
	{
		return IntVector3(x ^ value, y ^ value, z ^ value);
	}
	IntVector3 IntVector3::operator<<(int value)
	{
		return IntVector3(x << value, y << value, z << value);
	}
	IntVector3 IntVector3::operator>>(int value)
	{
		return IntVector3(x >> value, y >> value, z >> value);
	}
	IntVector3& IntVector3::operator-=(int value)
	{
		x -= value;
		y -= value;
		z -= value;
		return *this;
	}
	IntVector3& IntVector3::operator+=(int value)
	{
		x += value;
		y += value;
		z += value;
		return *this;
	}
	IntVector3& IntVector3::operator/=(int value)
	{
		x /= value;
		y /= value;
		z /= value;
		return *this;
	}
	IntVector3& IntVector3::operator*=(int value)
	{
		x *= value;
		y *= value;
		z *= value;
		return *this;
	}
	IntVector3& IntVector3::operator%=(int value)
	{
		x %= value;
		y %= value;
		z %= value;
		return *this;
	}
	IntVector3& IntVector3::operator|=(int value)
	{
		x |= value;
		y |= value;
		z |= value;
		return *this;
	}
	IntVector3& IntVector3::operator&=(int value)
	{
		x &= value;
		y &= value;
		z &= value;
		return *this;
	}
	IntVector3& IntVector3::operator^=(int value)
	{
		x ^= value;
		y ^= value;
		z ^= value;
		return *this;
	}
	IntVector3& IntVector3::operator<<=(int value)
	{
		x <<= value;
		y <<= value;
		z <<= value;
		return *this;
	}
	IntVector3& IntVector3::operator>>=(int value)
	{
		x >>= value;
		y >>= value;
		z >>= value;
		return *this;
	}
}
