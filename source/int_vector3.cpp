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

	float IntVector3::getMagnitude() const noexcept
	{
		return std::sqrtf(static_cast<float>(x * x + y * y + z * z));
	}
	int IntVector3::getDot(const IntVector3& other) const noexcept
	{
		return x * other.x + y * other.y + z * other.z;
	}
	float IntVector3::getDistance(const IntVector3& other) const noexcept
	{
		return std::sqrtf(static_cast<float>(
			x - other.x * x - other.x +
			y - other.y * y - other.y +
			z - other.z * z - other.z));
	}
	IntVector3 IntVector3::getNegative() const noexcept
	{
		return IntVector3(-x, -y, -z);
	}
	IntVector3 IntVector3::getCross(const IntVector3& other) const noexcept
	{
		return IntVector3(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x);
	}

	bool IntVector3::operator==(const IntVector3& other) const noexcept
	{
		return x == other.x && y == other.y && z == other.z;
	}
	bool IntVector3::operator!=(const IntVector3& other) const noexcept
	{
		return x != other.x || y != other.y || z != other.z;
	}

	IntVector3& IntVector3::operator--() noexcept
	{
		--x;
		--y;
		--z;
		return *this;
	}
	IntVector3& IntVector3::operator++() noexcept
	{
		++x;
		++y;
		++z;
		return *this;
	}
	IntVector3 IntVector3::operator--(int) noexcept
	{
		auto result = IntVector3(*this);
		--x;
		--y;
		--z;
		return result;
	}
	IntVector3 IntVector3::operator++(int) noexcept
	{
		auto result = IntVector3(*this);
		++x;
		++y;
		++z;
		return result;
	}

	IntVector3 IntVector3::operator-(const IntVector3& other) const noexcept
	{
		return IntVector3(x - other.x, y - other.y, z - other.z);
	}
	IntVector3 IntVector3::operator+(const IntVector3& other) const noexcept
	{
		return IntVector3(x + other.x, y + other.y, z + other.z);
	}
	IntVector3 IntVector3::operator/(const IntVector3& other) const noexcept
	{
		return IntVector3(x / other.x, y / other.y, z / other.z);
	}
	IntVector3 IntVector3::operator*(const IntVector3& other) const noexcept
	{
		return IntVector3(x * other.x, y * other.y, z * other.z);
	}
	IntVector3 IntVector3::operator%(const IntVector3& other) const noexcept
	{
		return IntVector3(x % other.x, y % other.y, z % other.z);
	}
	IntVector3 IntVector3::operator|(const IntVector3& other) const noexcept
	{
		return IntVector3(x | other.x, y | other.y, z | other.z);
	}
	IntVector3 IntVector3::operator&(const IntVector3& other) const noexcept
	{
		return IntVector3(x & other.x, y & other.y, z & other.z);
	}
	IntVector3 IntVector3::operator^(const IntVector3& other) const noexcept
	{
		return IntVector3(x ^ other.x, y ^ other.y, z ^ other.z);
	}
	IntVector3 IntVector3::operator<<(const IntVector3& other) const noexcept
	{
		return IntVector3(x << other.x, y << other.y, z << other.z);
	}
	IntVector3 IntVector3::operator>>(const IntVector3& other) const noexcept
	{
		return IntVector3(x >> other.x, y >> other.y, z >> other.z);
	}
	IntVector3& IntVector3::operator=(const IntVector3& other) noexcept
	{
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}
	IntVector3& IntVector3::operator-=(const IntVector3& other) noexcept
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}
	IntVector3& IntVector3::operator+=(const IntVector3& other) noexcept
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}
	IntVector3& IntVector3::operator/=(const IntVector3& other) noexcept
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}
	IntVector3& IntVector3::operator*=(const IntVector3& other) noexcept
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}
	IntVector3& IntVector3::operator%=(const IntVector3& other) noexcept
	{
		x %= other.x;
		y %= other.y;
		z %= other.z;
		return *this;
	}
	IntVector3& IntVector3::operator|=(const IntVector3& other) noexcept
	{
		x |= other.x;
		y |= other.y;
		z |= other.z;
		return *this;
	}
	IntVector3& IntVector3::operator&=(const IntVector3& other) noexcept
	{
		x &= other.x;
		y &= other.y;
		z &= other.z;
		return *this;
	}
	IntVector3& IntVector3::operator^=(const IntVector3& other) noexcept
	{
		x ^= other.x;
		y ^= other.y;
		z ^= other.z;
		return *this;
	}
	IntVector3& IntVector3::operator<<=(const IntVector3& other) noexcept
	{
		x <<= other.x;
		y <<= other.y;
		z <<= other.z;
		return *this;
	}
	IntVector3& IntVector3::operator>>=(const IntVector3& other) noexcept
	{
		x >>= other.x;
		y >>= other.y;
		z >>= other.z;
		return *this;
	}

	IntVector3 IntVector3::operator-(int value) const noexcept
	{
		return IntVector3(x - value, y - value, z - value);
	}
	IntVector3 IntVector3::operator+(int value) const noexcept
	{
		return IntVector3(x + value, y + value, z + value);
	}
	IntVector3 IntVector3::operator/(int value) const noexcept
	{
		return IntVector3(x / value, y / value, z / value);
	}
	IntVector3 IntVector3::operator*(int value) const noexcept
	{
		return IntVector3(x * value, y * value, z * value);
	}
	IntVector3 IntVector3::operator%(int value) const noexcept
	{
		return IntVector3(x % value, y % value, z % value);
	}
	IntVector3 IntVector3::operator|(int value) const noexcept
	{
		return IntVector3(x | value, y | value, z | value);
	}
	IntVector3 IntVector3::operator&(int value) const noexcept
	{
		return IntVector3(x & value, y & value, z & value);
	}
	IntVector3 IntVector3::operator^(int value) const noexcept
	{
		return IntVector3(x ^ value, y ^ value, z ^ value);
	}
	IntVector3 IntVector3::operator<<(int value) const noexcept
	{
		return IntVector3(x << value, y << value, z << value);
	}
	IntVector3 IntVector3::operator>>(int value) const noexcept
	{
		return IntVector3(x >> value, y >> value, z >> value);
	}
	IntVector3& IntVector3::operator=(int value) noexcept
	{
		x = value;
		y = value;
		z = value;
		return *this;
	}
	IntVector3& IntVector3::operator-=(int value) noexcept
	{
		x -= value;
		y -= value;
		z -= value;
		return *this;
	}
	IntVector3& IntVector3::operator+=(int value) noexcept
	{
		x += value;
		y += value;
		z += value;
		return *this;
	}
	IntVector3& IntVector3::operator/=(int value) noexcept
	{
		x /= value;
		y /= value;
		z /= value;
		return *this;
	}
	IntVector3& IntVector3::operator*=(int value) noexcept
	{
		x *= value;
		y *= value;
		z *= value;
		return *this;
	}
	IntVector3& IntVector3::operator%=(int value) noexcept
	{
		x %= value;
		y %= value;
		z %= value;
		return *this;
	}
	IntVector3& IntVector3::operator|=(int value) noexcept
	{
		x |= value;
		y |= value;
		z |= value;
		return *this;
	}
	IntVector3& IntVector3::operator&=(int value) noexcept
	{
		x &= value;
		y &= value;
		z &= value;
		return *this;
	}
	IntVector3& IntVector3::operator^=(int value) noexcept
	{
		x ^= value;
		y ^= value;
		z ^= value;
		return *this;
	}
	IntVector3& IntVector3::operator<<=(int value) noexcept
	{
		x <<= value;
		y <<= value;
		z <<= value;
		return *this;
	}
	IntVector3& IntVector3::operator>>=(int value) noexcept
	{
		x >>= value;
		y >>= value;
		z >>= value;
		return *this;
	}

	const IntVector3 IntVector3::zero = IntVector3(0, 0, 0);
	const IntVector3 IntVector3::minusOne = IntVector3(-1, -1, -1);
	const IntVector3 IntVector3::one = IntVector3(1, 1, 1);
}
