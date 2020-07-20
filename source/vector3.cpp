#include <injector/vector3.hpp>
#include <cmath>

namespace INJECTOR_NAMESPACE
{
	Vector3::Vector3() :
		x(0.0f), y(0.0f), z(0.0f)
	{}
	Vector3::Vector3(float _x, float _y, float _z) :
		x(_x), y(_y), z(_z)
	{}
	Vector3::Vector3(const Vector2& other, float _z) :
		x(other.x), y(other.y), z(_z)
	{}
	Vector3::Vector3(float _x, const Vector2& other) :
		x(_x), y(other.x), z(other.y)
	{}
	Vector3::Vector3(const IntVector3& other) :
		x(static_cast<float>(other.x)),
		y(static_cast<float>(other.y)),
		z(static_cast<float>(other.z))
	{}
	Vector3::Vector3(const IntVector2& other, float _z) :
		x(static_cast<float>(other.x)),
		y(static_cast<float>(other.y)),
		z(_z)
	{}
	Vector3::Vector3(float _x, const IntVector2& other) :
		x(_x),
		y(static_cast<float>(other.x)),
		z(static_cast<float>(other.y))
	{}

	float Vector3::getMagnitude() const noexcept
	{
		return std::sqrtf(x * x + y * y + z * z);
	}
	float Vector3::getDot(const Vector3& other) const noexcept
	{
		return x * other.x + y * other.y + z * other.z;
	}
	float Vector3::getDistance(const Vector3& other) const noexcept
	{
		return  std::sqrtf(
			x - other.x * x - other.x +
			y - other.y * y - other.y +
			z - other.z * z - other.z);
	}
	Vector3 Vector3::getNegative() const noexcept
	{
		return Vector3(-x, -y, -z);
	}
	Vector3 Vector3::getNormalized() const noexcept
	{
		auto magnitude = 1.0f / getMagnitude();
		return Vector3(x * magnitude, y * magnitude, z * magnitude);
	}
	Vector3 Vector3::getSine() const noexcept
	{
		return Vector3(std::sinf(x), std::sinf(y), std::sinf(z));
	}
	Vector3 Vector3::getCosine() const noexcept
	{
		return Vector3(std::cosf(x), std::cosf(y), std::cosf(z));
	}
	Vector3 Vector3::getTangent() const noexcept
	{
		return Vector3(std::tanf(x), std::tanf(y), std::tanf(z));
	}
	Vector3 Vector3::getCotangent() const noexcept
	{
		return Vector3(1.0f / std::tanf(x), 1.0f / std::tanf(y), 1.0f / std::tanf(z));
	}
	Vector3 Vector3::getCross(const Vector3& other) const noexcept
	{
		return Vector3(
			y * other.z - z * other.y,
			z * other.x - x * other.z,
			x * other.y - y * other.x);
	}

	bool Vector3::operator==(const Vector3& other) const noexcept
	{
		return x == other.x && y == other.y && z == other.z;
	}
	bool Vector3::operator!=(const Vector3& other) const noexcept
	{
		return x != other.x || y != other.y || z != other.z;
	}

	Vector3& Vector3::operator--() noexcept
	{
		--x;
		--y;
		--z;
		return *this;
	}
	Vector3& Vector3::operator++() noexcept
	{
		++x;
		++y;
		++z;
		return *this;
	}
	Vector3 Vector3::operator--(int) noexcept
	{
		auto result = Vector3(*this);
		--x;
		--y;
		--z;
		return result;
	}
	Vector3 Vector3::operator++(int) noexcept
	{
		auto result = Vector3(*this);
		++x;
		++y;
		++z;
		return result;
	}

	Vector3 Vector3::operator-(const Vector3& other) const noexcept
	{
		return Vector3(x - other.x, y - other.y, z - other.z);
	}
	Vector3 Vector3::operator+(const Vector3& other) const noexcept
	{
		return Vector3(x + other.x, y + other.y, z + other.z);
	}
	Vector3 Vector3::operator/(const Vector3& other) const noexcept
	{
		return Vector3(x / other.x, y / other.y, z / other.z);
	}
	Vector3 Vector3::operator*(const Vector3& other) const noexcept
	{
		return Vector3(x * other.x, y * other.y, z * other.z);
	}
	Vector3& Vector3::operator=(const Vector3& other) noexcept
	{
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}
	Vector3& Vector3::operator-=(const Vector3& other) noexcept
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		return *this;
	}
	Vector3& Vector3::operator+=(const Vector3& other) noexcept
	{
		x += other.x;
		y += other.y;
		z += other.z;
		return *this;
	}
	Vector3& Vector3::operator/=(const Vector3& other) noexcept
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		return *this;
	}
	Vector3& Vector3::operator*=(const Vector3& other) noexcept
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		return *this;
	}

	Vector3 Vector3::operator-(const IntVector3& other) const noexcept
	{
		return Vector3(x - other.x, y - other.y, z - other.z);
	}
	Vector3 Vector3::operator+(const IntVector3& other) const noexcept
	{
		return Vector3(x + other.x, y + other.y, z + other.z);
	}
	Vector3 Vector3::operator/(const IntVector3& other) const noexcept
	{
		return Vector3(x / other.x, y / other.y, z / other.z);
	}
	Vector3 Vector3::operator*(const IntVector3& other) const noexcept
	{
		return Vector3(x * other.x, y * other.y, z * other.z);
	}
	Vector3& Vector3::operator=(const IntVector3& other) noexcept
	{
		x = static_cast<float>(other.x);
		y = static_cast<float>(other.y);
		z = static_cast<float>(other.z);
		return *this;
	}
	Vector3& Vector3::operator-=(const IntVector3& other) noexcept
	{
		x -= static_cast<float>(other.x);
		y -= static_cast<float>(other.y);
		z -= static_cast<float>(other.z);
		return *this;
	}
	Vector3& Vector3::operator+=(const IntVector3& other) noexcept
	{
		x += static_cast<float>(other.x);
		y += static_cast<float>(other.y);
		z += static_cast<float>(other.z);
		return *this;
	}
	Vector3& Vector3::operator/=(const IntVector3& other) noexcept
	{
		x /= static_cast<float>(other.x);
		y /= static_cast<float>(other.y);
		z /= static_cast<float>(other.z);
		return *this;
	}
	Vector3& Vector3::operator*=(const IntVector3& other) noexcept
	{
		x *= static_cast<float>(other.x);
		y *= static_cast<float>(other.y);
		z *= static_cast<float>(other.z);
		return *this;
	}

	Vector3 Vector3::operator-(float value) const noexcept
	{
		return Vector3(x - value, y - value, z - value);
	}
	Vector3 Vector3::operator+(float value) const noexcept
	{
		return Vector3(x + value, y + value, z + value);
	}
	Vector3 Vector3::operator/(float value) const noexcept
	{
		return Vector3(x / value, y / value, z / value);
	}
	Vector3 Vector3::operator*(float value) const noexcept
	{
		return Vector3(x * value, y * value, z * value);
	}
	Vector3& Vector3::operator=(float value) noexcept
	{
		x = value;
		y = value;
		z = value;
		return *this;
	}
	Vector3& Vector3::operator-=(float value) noexcept
	{
		x -= value;
		y -= value;
		z -= value;
		return *this;
	}
	Vector3& Vector3::operator+=(float value) noexcept
	{
		x += value;
		y += value;
		z += value;
		return *this;
	}
	Vector3& Vector3::operator/=(float value) noexcept
	{
		x /= value;
		y /= value;
		z /= value;
		return *this;
	}
	Vector3& Vector3::operator*=(float value) noexcept
	{
		x *= value;
		y *= value;
		z *= value;
		return *this;
	}

	const Vector3 Vector3::zero = Vector3(0.0f, 0.0f, 0.0f);
	const Vector3 Vector3::minusOne = Vector3(-1.0f, -1.0f, -1.0f);
	const Vector3 Vector3::one = Vector3(1.0f, 1.0f, 1.0f);
}
