#include <Injector/Mathematics/Vector3.hpp>

#include <cmath>
#include <sstream>

namespace Injector
{
	Vector3::Vector3() :
		x(0.0f),
		y(0.0f),
		z(0.0f)
	{
	}
	Vector3::Vector3(
		float xyz) :
		x(xyz),
		y(xyz),
		z(xyz)
	{
	}
	Vector3::Vector3(
		float _x,
		float _y,
		float _z) :
		x(_x),
		y(_y),
		z(_z)
	{
	}
	Vector3::Vector3(
		const Vector2& vector,
		float _z) :
		x(vector.x),
		y(vector.y),
		z(_z)
	{
	}
	Vector3::Vector3(
		float _x,
		const Vector2& vector) :
		x(_x),
		y(vector.x),
		z(vector.y)
	{
	}
	Vector3::Vector3(
		const IntVector3& vector) :
		x(static_cast<float>(vector.x)),
		y(static_cast<float>(vector.y)),
		z(static_cast<float>(vector.z))
	{
	}
	Vector3::Vector3(
		const IntVector2& vector,
		float _z) :
		x(static_cast<float>(vector.x)),
		y(static_cast<float>(vector.y)),
		z(_z)
	{
	}
	Vector3::Vector3(
		float _x,
		const IntVector2& vector) :
		x(_x),
		y(static_cast<float>(vector.x)),
		z(static_cast<float>(vector.y))
	{
	}

	std::string Vector3::getString() const noexcept
	{
		auto ss = std::stringstream();
		ss << x << " " << y << " " << z;
		return ss.str();
	}
	float Vector3::getDotProduct(const Vector3& vector) const noexcept
	{
		auto result = *this * vector;
		return result.x + result.y + result.z;
	}
	float Vector3::getDotProduct(const IntVector3& vector) const noexcept
	{
		auto result = *this * vector;
		return result.x + result.y + result.z;
	}
	Vector3 Vector3::getCrossProduct(const Vector3& vector) const noexcept
	{
		return Vector3(
			y * vector.z - z * vector.y,
			z * vector.x - x * vector.z,
			x * vector.y - y * vector.x);
	}
	Vector3 Vector3::getCrossProduct(const IntVector3& vector) const noexcept
	{
		return Vector3(
			y * vector.z - z * vector.y,
			z * vector.x - x * vector.z,
			x * vector.y - y * vector.x);
	}
	float Vector3::getLength() const noexcept
	{
		return sqrt(getDotProduct(*this));
	}
	float Vector3::getDistance(const Vector3& vector) const noexcept
	{
		return sqrt(getDotProduct(*this - vector));
	}
	float Vector3::getDistance(const IntVector3& vector) const noexcept
	{
		return sqrt(getDotProduct(*this - vector));
	}
	Vector3 Vector3::getNormalized() const noexcept
	{
		return *this * (1.0f / sqrt(getDotProduct(*this)));
	}
	Vector3 Vector3::getReflected(const Vector3& normal) const noexcept
	{
		return *this - normal * getDotProduct(normal) * 2.0f;
	}
	Vector3 Vector3::getRefracted(const Vector3& normal, float eta) const noexcept
	{
		auto dot = getDotProduct(normal);
		auto k = (1.0f - eta * eta * (1.0f - dot * dot));

		return Vector3(k >= 0.0f ?
			(*this * eta - normal * (eta * dot + sqrt(k))) :
			Vector3(0.0f));
	}
	Vector3 Vector3::getSine() const noexcept
	{
		return Vector3(
			sin(x),
			sin(y),
			sin(z));
	}
	Vector3 Vector3::getCosine() const noexcept
	{
		return Vector3(
			cos(x),
			cos(y),
			cos(z));
	}
	Vector3 Vector3::getTangent() const noexcept
	{
		return Vector3(
			tan(x),
			tan(y),
			tan(z));
	}
	Vector3 Vector3::getCotangent() const noexcept
	{
		return Vector3(
			1.0f / tan(x),
			1.0f / tan(y),
			1.0f / tan(z));
	}

	Vector2 Vector3::getVector2() const noexcept
	{
		return Vector2(
			x,
			y);
	}

	bool Vector3::operator==(const Vector3& vector) const noexcept
	{
		return
			x == vector.x &&
			y == vector.y &&
			z == vector.z;
	}
	bool Vector3::operator!=(const Vector3& vector) const noexcept
	{
		return
			x != vector.x ||
			y != vector.y ||
			z != vector.z;
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
	Vector3 Vector3::operator-() const noexcept
	{
		return Vector3(
			-x,
			-y,
			-z);
	}

	Vector3 Vector3::operator-(const Vector3& vector) const noexcept
	{
		return Vector3(
			x - vector.x,
			y - vector.y,
			z - vector.z);
	}
	Vector3 Vector3::operator+(const Vector3& vector) const noexcept
	{
		return Vector3(
			x + vector.x,
			y + vector.y,
			z + vector.z);
	}
	Vector3 Vector3::operator/(const Vector3& vector) const noexcept
	{
		return Vector3(
			x / vector.x,
			y / vector.y,
			z / vector.z);
	}
	Vector3 Vector3::operator*(const Vector3& vector) const noexcept
	{
		return Vector3(
			x * vector.x,
			y * vector.y,
			z * vector.z);
	}
	Vector3& Vector3::operator-=(const Vector3& vector) noexcept
	{
		x -= vector.x;
		y -= vector.y;
		z -= vector.z;
		return *this;
	}
	Vector3& Vector3::operator+=(const Vector3& vector) noexcept
	{
		x += vector.x;
		y += vector.y;
		z += vector.z;
		return *this;
	}
	Vector3& Vector3::operator/=(const Vector3& vector) noexcept
	{
		x /= vector.x;
		y /= vector.y;
		z /= vector.z;
		return *this;
	}
	Vector3& Vector3::operator*=(const Vector3& vector) noexcept
	{
		x *= vector.x;
		y *= vector.y;
		z *= vector.z;
		return *this;
	}

	Vector3 Vector3::operator-(const IntVector3& vector) const noexcept
	{
		return Vector3(
			x - vector.x,
			y - vector.y,
			z - vector.z);
	}
	Vector3 Vector3::operator+(const IntVector3& vector) const noexcept
	{
		return Vector3(
			x + vector.x,
			y + vector.y,
			z + vector.z);
	}
	Vector3 Vector3::operator/(const IntVector3& vector) const noexcept
	{
		return Vector3(
			x / vector.x,
			y / vector.y,
			z / vector.z);
	}
	Vector3 Vector3::operator*(const IntVector3& vector) const noexcept
	{
		return Vector3(
			x * vector.x,
			y * vector.y,
			z * vector.z);
	}
	Vector3& Vector3::operator-=(const IntVector3& vector) noexcept
	{
		x -= static_cast<float>(vector.x);
		y -= static_cast<float>(vector.y);
		z -= static_cast<float>(vector.z);
		return *this;
	}
	Vector3& Vector3::operator+=(const IntVector3& vector) noexcept
	{
		x += static_cast<float>(vector.x);
		y += static_cast<float>(vector.y);
		z += static_cast<float>(vector.z);
		return *this;
	}
	Vector3& Vector3::operator/=(const IntVector3& vector) noexcept
	{
		x /= static_cast<float>(vector.x);
		y /= static_cast<float>(vector.y);
		z /= static_cast<float>(vector.z);
		return *this;
	}
	Vector3& Vector3::operator*=(const IntVector3& vector) noexcept
	{
		x *= static_cast<float>(vector.x);
		y *= static_cast<float>(vector.y);
		z *= static_cast<float>(vector.z);
		return *this;
	}

	Vector3 Vector3::operator-(float value) const noexcept
	{
		return Vector3(
			x - value,
			y - value,
			z - value);
	}
	Vector3 Vector3::operator+(float value) const noexcept
	{
		return Vector3(
			x + value,
			y + value,
			z + value);
	}
	Vector3 Vector3::operator/(float value) const noexcept
	{
		return Vector3(
			x / value,
			y / value,
			z / value);
	}
	Vector3 Vector3::operator*(float value) const noexcept
	{
		return Vector3(
			x * value,
			y * value, z * value);
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

	const Vector3 Vector3::zero = Vector3(0.0f);
	const Vector3 Vector3::minusOne = Vector3(-1.0f);
	const Vector3 Vector3::one = Vector3(1.0f);
}
