#include <injector/vector3.hpp>

#include <cmath>

namespace INJECTOR_NAMESPACE
{
	Vector3::Vector3(float _x, float _y, float _z) :
		x(_x),
		y(_y),
		z(_z)
	{}
	Vector3::Vector3(const Vector2& other, float _z) :
		x(other.x),
		y(other.y),
		z(_z)
	{}

	float Vector3::getMagnitude()
	{
		return std::sqrtf(x * x + y * y + z * z);
	}
	float Vector3::getDot(const Vector3& other)
	{
		return x * other.x + y * other.y + z * other.z;
	}
	float Vector3::getDistance(const Vector3& other)
	{
		return  std::sqrtf(x - other.x * x - other.x +
			y - other.y * y - other.y +
			z - other.z * z - other.z);
	}
	Vector3 Vector3::getCross(const Vector3& other)
	{
		return Vector3(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x);
	}

	bool Vector3::operator==(const Vector3& other)
	{
		return x == other.x && y == other.y && z == other.z;
	}
	bool Vector3::operator!=(const Vector3& other)
	{
		return x != other.x && y != other.y && z != other.z;
	}

	Vector3& Vector3::operator--()
	{
		--x;
		--y;
		--z;
		return *this;
	}
	Vector3& Vector3::operator++()
	{
		++x;
		++y;
		++z;
		return *this;
	}
	Vector3 Vector3::operator--(int)
	{
		auto result = Vector3(*this);
		--x;
		--y;
		--z;
		return result;
	}
	Vector3 Vector3::operator++(int)
	{
		auto result = Vector3(*this);
		++x;
		++y;
		++z;
		return result;
	}

	Vector3 Vector3::operator-(const Vector3& other)
	{
		return Vector3(x - other.x, y - other.y, z - other.z);
	}
	Vector3 Vector3::operator+(const Vector3& other)
	{
		return Vector3(x + other.x, y + other.y, z + other.z);
	}
	Vector3 Vector3::operator/(const Vector3& other)
	{
		return Vector3(x / other.x, y / other.y, z / other.z);
	}
	Vector3 Vector3::operator*(const Vector3& other)
	{
		return Vector3(x * other.x, y * other.y, z * other.z);
	}
	Vector3& Vector3::operator-=(const Vector3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}
	Vector3& Vector3::operator+=(const Vector3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}
	Vector3& Vector3::operator/=(const Vector3& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}
	Vector3& Vector3::operator*=(const Vector3& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	Vector3 Vector3::operator-(float value)
	{
		return Vector3(x - value, y - value, z - value);
	}
	Vector3 Vector3::operator+(float value)
	{
		return Vector3(x + value, y + value, z + value);
	}
	Vector3 Vector3::operator/(float value)
	{
		return Vector3(x / value, y / value, z / value);
	}
	Vector3 Vector3::operator*(float value)
	{
		return Vector3(x * value, y * value, z * value);
	}
	Vector3& Vector3::operator-=(float value)
	{
		x -= value;
		y -= value;
		z -= value;
		return *this;
	}
	Vector3& Vector3::operator+=(float value)
	{
		x += value;
		y += value;
		z += value;
		return *this;
	}
	Vector3& Vector3::operator/=(float value)
	{
		x /= value;
		y /= value;
		z /= value;
		return *this;
	}
	Vector3& Vector3::operator*=(float value)
	{
		x *= value;
		y *= value;
		z *= value;
		return *this;
	}
}