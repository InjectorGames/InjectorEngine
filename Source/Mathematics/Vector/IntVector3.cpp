#include "Injector/Mathematics/Vector/IntVector3.hpp"

#include <tuple>
#include <cmath>
#include <cstdint>
#include <sstream>

namespace Injector
{
	IntVector3::IntVector3() noexcept :
		x(0),
		y(0),
		z(0)
	{
	}
	IntVector3::IntVector3(
		int xyz) noexcept :
		x(xyz),
		y(xyz),
		z(xyz)
	{
	}
	IntVector3::IntVector3(
		int _x,
		int _y,
		int _z) noexcept :
		x(_x),
		y(_y),
		z(_z)
	{
	}
	IntVector3::IntVector3(
		const IntVector2& vector,
		int _z) noexcept :
		x(vector.x),
		y(vector.y),
		z(_z)
	{
	}
	IntVector3::IntVector3(
		int _x,
		const IntVector2& vector) noexcept :
		x(_x),
		y(vector.x),
		z(vector.y)
	{
	}

	std::string IntVector3::getString() const noexcept
	{
		auto ss = std::stringstream();
		ss << x << " " << y << " " << z;
		return ss.str();
	}
	int IntVector3::getDotProduct(const IntVector3& vector) const noexcept
	{
		auto result = *this * vector;
		return result.x + result.y + result.z;
	}
	IntVector3 IntVector3::getCrossProduct(const IntVector3& vector) const noexcept
	{
		return IntVector3(
			y * vector.z - z * vector.y,
			z * vector.x - x * vector.z,
			x * vector.y - y * vector.x);
	}
	float IntVector3::getLength() const noexcept
	{
		return sqrtf(static_cast<float>(
			getDotProduct(*this)));
	}
	float IntVector3::getDistance(const IntVector3& vector) const noexcept
	{
		return sqrtf(static_cast<float>(
			getDotProduct(*this - vector)));
	}
	IntVector3 IntVector3::getReflected(const IntVector3& normal) const noexcept
	{
		return *this - normal * getDotProduct(normal) * 2;
	}

	IntVector2 IntVector3::getIntVector2() const noexcept
	{
		return IntVector2(x, y);
	}

	bool IntVector3::operator==(const IntVector3& vector) const noexcept
	{
		return
			x == vector.x &&
			y == vector.y &&
			z == vector.z;
	}
	bool IntVector3::operator!=(const IntVector3& vector) const noexcept
	{
		return
			x != vector.x ||
			y != vector.y ||
			z != vector.z;
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
	IntVector3 IntVector3::operator-() const noexcept
	{
		return IntVector3(
			-x,
			-y,
			-z);
	}

	IntVector3 IntVector3::operator-(const IntVector3& vector) const noexcept
	{
		return IntVector3(
			x - vector.x,
			y - vector.y,
			z - vector.z);
	}
	IntVector3 IntVector3::operator+(const IntVector3& vector) const noexcept
	{
		return IntVector3(
			x + vector.x,
			y + vector.y,
			z + vector.z);
	}
	IntVector3 IntVector3::operator/(const IntVector3& vector) const noexcept
	{
		return IntVector3(
			x / vector.x,
			y / vector.y,
			z / vector.z);
	}
	IntVector3 IntVector3::operator*(const IntVector3& vector) const noexcept
	{
		return IntVector3(
			x * vector.x,
			y * vector.y,
			z * vector.z);
	}
	IntVector3 IntVector3::operator%(const IntVector3& vector) const noexcept
	{
		return IntVector3(
			x % vector.x,
			y % vector.y,
			z % vector.z);
	}
	IntVector3 IntVector3::operator|(const IntVector3& vector) const noexcept
	{
		return IntVector3(
			x | vector.x,
			y | vector.y,
			z | vector.z);
	}
	IntVector3 IntVector3::operator&(const IntVector3& vector) const noexcept
	{
		return IntVector3(
			x & vector.x,
			y & vector.y,
			z & vector.z);
	}
	IntVector3 IntVector3::operator^(const IntVector3& vector) const noexcept
	{
		return IntVector3(
			x ^ vector.x,
			y ^ vector.y,
			z ^ vector.z);
	}
	IntVector3 IntVector3::operator<<(const IntVector3& vector) const noexcept
	{
		return IntVector3(
			x << vector.x,
			y << vector.y,
			z << vector.z);
	}
	IntVector3 IntVector3::operator>>(const IntVector3& vector) const noexcept
	{
		return IntVector3(
			x >> vector.x,
			y >> vector.y,
			z >> vector.z);
	}
	IntVector3& IntVector3::operator-=(const IntVector3& vector) noexcept
	{
		x -= vector.x;
		y -= vector.y;
		z -= vector.z;
		return *this;
	}
	IntVector3& IntVector3::operator+=(const IntVector3& vector) noexcept
	{
		x += vector.x;
		y += vector.y;
		z += vector.z;
		return *this;
	}
	IntVector3& IntVector3::operator/=(const IntVector3& vector) noexcept
	{
		x /= vector.x;
		y /= vector.y;
		z /= vector.z;
		return *this;
	}
	IntVector3& IntVector3::operator*=(const IntVector3& vector) noexcept
	{
		x *= vector.x;
		y *= vector.y;
		z *= vector.z;
		return *this;
	}
	IntVector3& IntVector3::operator%=(const IntVector3& vector) noexcept
	{
		x %= vector.x;
		y %= vector.y;
		z %= vector.z;
		return *this;
	}
	IntVector3& IntVector3::operator|=(const IntVector3& vector) noexcept
	{
		x |= vector.x;
		y |= vector.y;
		z |= vector.z;
		return *this;
	}
	IntVector3& IntVector3::operator&=(const IntVector3& vector) noexcept
	{
		x &= vector.x;
		y &= vector.y;
		z &= vector.z;
		return *this;
	}
	IntVector3& IntVector3::operator^=(const IntVector3& vector) noexcept
	{
		x ^= vector.x;
		y ^= vector.y;
		z ^= vector.z;
		return *this;
	}
	IntVector3& IntVector3::operator<<=(const IntVector3& vector) noexcept
	{
		x <<= vector.x;
		y <<= vector.y;
		z <<= vector.z;
		return *this;
	}
	IntVector3& IntVector3::operator>>=(const IntVector3& vector) noexcept
	{
		x >>= vector.x;
		y >>= vector.y;
		z >>= vector.z;
		return *this;
	}

	IntVector3 IntVector3::operator-(int value) const noexcept
	{
		return IntVector3(
			x - value,
			y - value,
			z - value);
	}
	IntVector3 IntVector3::operator+(int value) const noexcept
	{
		return IntVector3(
			x + value,
			y + value,
			z + value);
	}
	IntVector3 IntVector3::operator/(int value) const noexcept
	{
		return IntVector3(
			x / value,
			y / value,
			z / value);
	}
	IntVector3 IntVector3::operator*(int value) const noexcept
	{
		return IntVector3(
			x * value,
			y * value,
			z * value);
	}
	IntVector3 IntVector3::operator%(int value) const noexcept
	{
		return IntVector3(
			x % value,
			y % value,
			z % value);
	}
	IntVector3 IntVector3::operator|(int value) const noexcept
	{
		return IntVector3(
			x | value,
			y | value,
			z | value);
	}
	IntVector3 IntVector3::operator&(int value) const noexcept
	{
		return IntVector3(
			x & value,
			y & value,
			z & value);
	}
	IntVector3 IntVector3::operator^(int value) const noexcept
	{
		return IntVector3(
			x ^ value,
			y ^ value,
			z ^ value);
	}
	IntVector3 IntVector3::operator<<(int value) const noexcept
	{
		return IntVector3(
			x << value,
			y << value,
			z << value);
	}
	IntVector3 IntVector3::operator>>(int value) const noexcept
	{
		return IntVector3(
			x >> value,
			y >> value,
			z >> value);
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

	const IntVector3 IntVector3::zero = IntVector3(0);
	const IntVector3 IntVector3::minusOne = IntVector3(-1);
	const IntVector3 IntVector3::one = IntVector3(1);
	const IntVector3 IntVector3::left = IntVector3(-1, 0, 0);
	const IntVector3 IntVector3::right = IntVector3(1, 0, 0);
	const IntVector3 IntVector3::down = IntVector3(0, -1, 0);
	const IntVector3 IntVector3::up = IntVector3(0, 1, 0);
	const IntVector3 IntVector3::back = IntVector3(0, 0, -1);
	const IntVector3 IntVector3::forward = IntVector3(0, 0, 1);
	const IntVector3 IntVector3::minimum = IntVector3(INT32_MIN);
	const IntVector3 IntVector3::maximum = IntVector3(INT32_MAX);

	bool IntVector3::less(
		const IntVector3& a,
		const IntVector3& b) noexcept
	{
		return std::tie(a.x, a.y, a.z) <
			std::tie(b.x, b.y, b.z);
	}
}
