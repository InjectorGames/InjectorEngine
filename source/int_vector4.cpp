#include <injector/int_vector4.hpp>

#include <cmath>

namespace INJECTOR_NAMESPACE
{
	IntVector4::IntVector4(int _x, int _y, int _z, int _w) :
		x(_x), y(_y), z(_z), w(_w)
	{}
	IntVector4::IntVector4(const IntVector2& other, int _z, int _w) :
		x(other.x), y(other.y), z(_z), w(_w)
	{}
	IntVector4::IntVector4(const IntVector3& other, int _w) :
		x(other.x), y(other.y), z(other.z), w(_w)
	{}

	float IntVector4::getMagnitude() const noexcept
	{
		return std::sqrtf(static_cast<float>(x * x + y * y + z * z + w * w));
	}
	int IntVector4::getDot(const IntVector4& other) const noexcept
	{
		return x * other.x + y * other.y + z * other.z + w * other.w;
	}
	float IntVector4::getDistance(const IntVector4& other) const noexcept
	{
		return  std::sqrtf(static_cast<float>(
			x - other.x * x - other.x +
			y - other.y * y - other.y +
			z - other.z * z - other.z +
			w - other.w * w - other.w));
	}
	IntVector4 IntVector4::getNegative() const noexcept
	{
		return IntVector4(-x, -y, -z, -w);
	}

	bool IntVector4::operator==(const IntVector4& other) const noexcept
	{
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}
	bool IntVector4::operator!=(const IntVector4& other) const noexcept
	{
		return x != other.x || y != other.y || z != other.z || w != other.w;
	}

	IntVector4& IntVector4::operator--() noexcept
	{
		--x;
		--y;
		--z;
		--w;
		return *this;
	}
	IntVector4& IntVector4::operator++() noexcept
	{
		++x;
		++y;
		++z;
		++w;
		return *this;
	}
	IntVector4 IntVector4::operator--(int) noexcept
	{
		auto result = IntVector4(*this);
		--x;
		--y;
		--z;
		--w;
		return result;
	}
	IntVector4 IntVector4::operator++(int) noexcept
	{
		auto result = IntVector4(*this);
		++x;
		++y;
		++z;
		++w;
		return result;
	}

	IntVector4 IntVector4::operator-(const IntVector4& other) const noexcept
	{
		return IntVector4(x - other.x, y - other.y, z - other.z, w - other.w);
	}
	IntVector4 IntVector4::operator+(const IntVector4& other) const noexcept
	{
		return IntVector4(x + other.x, y + other.y, z + other.z, w + other.w);
	}
	IntVector4 IntVector4::operator/(const IntVector4& other) const noexcept
	{
		return IntVector4(x / other.x, y / other.y, z / other.z, w / other.w);
	}
	IntVector4 IntVector4::operator*(const IntVector4& other) const noexcept
	{
		return IntVector4(x * other.x, y * other.y, z * other.z, w * other.w);
	}
	IntVector4 IntVector4::operator%(const IntVector4& other) const noexcept
	{
		return IntVector4(x % other.x, y % other.y, z % other.z, w % other.w);
	}
	IntVector4 IntVector4::operator|(const IntVector4& other) const noexcept
	{
		return IntVector4(x | other.x, y | other.y, z | other.z, w | other.w);
	}
	IntVector4 IntVector4::operator&(const IntVector4& other) const noexcept
	{
		return IntVector4(x & other.x, y & other.y, z & other.z, w & other.w);
	}
	IntVector4 IntVector4::operator^(const IntVector4& other) const noexcept
	{
		return IntVector4(x ^ other.x, y ^ other.y, z ^ other.z, w ^ other.w);
	}
	IntVector4 IntVector4::operator<<(const IntVector4& other) const noexcept
	{
		return IntVector4(x << other.x, y << other.y, z << other.z, w << other.w);
	}
	IntVector4 IntVector4::operator>>(const IntVector4& other) const noexcept
	{
		return IntVector4(x >> other.x, y >> other.y, z >> other.z, w >> other.w);
	}
	IntVector4& IntVector4::operator=(const IntVector4& other) noexcept
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
		return *this;
	}
	IntVector4& IntVector4::operator-=(const IntVector4& other) noexcept
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}
	IntVector4& IntVector4::operator+=(const IntVector4& other) noexcept
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}
	IntVector4& IntVector4::operator/=(const IntVector4& other) noexcept
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;
		return *this;
	}
	IntVector4& IntVector4::operator*=(const IntVector4& other) noexcept
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;
		return *this;
	}
	IntVector4& IntVector4::operator%=(const IntVector4& other) noexcept
	{
		x %= other.x;
		y %= other.y;
		z %= other.z;
		w %= other.w;
		return *this;
	}
	IntVector4& IntVector4::operator|=(const IntVector4& other) noexcept
	{
		x |= other.x;
		y |= other.y;
		z |= other.z;
		w |= other.w;
		return *this;
	}
	IntVector4& IntVector4::operator&=(const IntVector4& other) noexcept
	{
		x &= other.x;
		y &= other.y;
		z &= other.z;
		w &= other.w;
		return *this;
	}
	IntVector4& IntVector4::operator^=(const IntVector4& other) noexcept
	{
		x ^= other.x;
		y ^= other.y;
		z ^= other.z;
		w ^= other.w;
		return *this;
	}
	IntVector4& IntVector4::operator<<=(const IntVector4& other) noexcept
	{
		x <<= other.x;
		y <<= other.y;
		z <<= other.z;
		w <<= other.w;
		return *this;
	}
	IntVector4& IntVector4::operator>>=(const IntVector4& other) noexcept
	{
		x >>= other.x;
		y >>= other.y;
		z >>= other.z;
		w >>= other.w;
		return *this;
	}

	IntVector4 IntVector4::operator-(int value) const noexcept
	{
		return IntVector4(x - value, y - value, z - value, w - value);
	}
	IntVector4 IntVector4::operator+(int value) const noexcept
	{
		return IntVector4(x + value, y + value, z + value, w + value);
	}
	IntVector4 IntVector4::operator/(int value) const noexcept
	{
		return IntVector4(x / value, y / value, z / value, w / value);
	}
	IntVector4 IntVector4::operator*(int value) const noexcept
	{
		return IntVector4(x * value, y * value, z * value, w * value);
	}
	IntVector4 IntVector4::operator%(int value) const noexcept
	{
		return IntVector4(x % value, y % value, z % value, w % value);
	}
	IntVector4 IntVector4::operator|(int value) const noexcept
	{
		return IntVector4(x | value, y | value, z | value, w | value);
	}
	IntVector4 IntVector4::operator&(int value) const noexcept
	{
		return IntVector4(x & value, y & value, z & value, w & value);
	}
	IntVector4 IntVector4::operator^(int value) const noexcept
	{
		return IntVector4(x ^ value, y ^ value, z ^ value, w ^ value);
	}
	IntVector4 IntVector4::operator<<(int value) const noexcept
	{
		return IntVector4(x << value, y << value, z << value, w << value);
	}
	IntVector4 IntVector4::operator>>(int value) const noexcept
	{
		return IntVector4(x >> value, y >> value, z >> value, w >> value);
	}
	IntVector4& IntVector4::operator=(int value) noexcept
	{
		x = value;
		y = value;
		z = value;
		w = value;
		return *this;
	}
	IntVector4& IntVector4::operator-=(int value) noexcept
	{
		x -= value;
		y -= value;
		z -= value;
		w -= value;
		return *this;
	}
	IntVector4& IntVector4::operator+=(int value) noexcept
	{
		x += value;
		y += value;
		z += value;
		w += value;
		return *this;
	}
	IntVector4& IntVector4::operator/=(int value) noexcept
	{
		x /= value;
		y /= value;
		z /= value;
		w /= value;
		return *this;
	}
	IntVector4& IntVector4::operator*=(int value) noexcept
	{
		x *= value;
		y *= value;
		z *= value;
		w *= value;
		return *this;
	}
	IntVector4& IntVector4::operator%=(int value) noexcept
	{
		x %= value;
		y %= value;
		z %= value;
		w %= value;
		return *this;
	}
	IntVector4& IntVector4::operator|=(int value) noexcept
	{
		x |= value;
		y |= value;
		z |= value;
		w |= value;
		return *this;
	}
	IntVector4& IntVector4::operator&=(int value) noexcept
	{
		x &= value;
		y &= value;
		z &= value;
		w &= value;
		return *this;
	}
	IntVector4& IntVector4::operator^=(int value) noexcept
	{
		x ^= value;
		y ^= value;
		z ^= value;
		w ^= value;
		return *this;
	}
	IntVector4& IntVector4::operator<<=(int value) noexcept
	{
		x <<= value;
		y <<= value;
		z <<= value;
		w <<= value;
		return *this;
	}
	IntVector4& IntVector4::operator>>=(int value) noexcept
	{
		x >>= value;
		y >>= value;
		z >>= value;
		w >>= value;
		return *this;
	}

	const IntVector4 IntVector4::zero = IntVector4(0, 0, 0, 0);
	const IntVector4 IntVector4::minusOne = IntVector4(-1, -1, -1, -1);
	const IntVector4 IntVector4::one = IntVector4(1, 1, 1, 1);
}
