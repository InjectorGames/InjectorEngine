#include "Injector/Mathematics/Vector4.hpp"

#include <cmath>
#include <sstream>

namespace Injector
{
	Vector4::Vector4() :
		x(0.0f),
		y(0.0f),
		z(0.0f),
		w(0.0f)
	{
	}
	Vector4::Vector4(
		float xyzw) :
		x(xyzw),
		y(xyzw),
		z(xyzw),
		w(xyzw)
	{
	}
	Vector4::Vector4(
		float _x,
		float _y,
		float _z,
		float _w) :
		x(_x),
		y(_y),
		z(_z),
		w(_w)
	{
	}
	Vector4::Vector4(
		const Vector2& vector,
		float _z,
		float _w) :
		x(vector.x),
		y(vector.y),
		z(_z),
		w(_w)
	{
	}
	Vector4::Vector4(
		float _x,
		const Vector2& vector,
		float _w) :
		x(_x), y(vector.x),
		z(vector.y),
		w(_w)
	{
	}
	Vector4::Vector4(
		float _x,
		float _y,
		const Vector2& vector) :
		x(_x),
		y(_y),
		z(vector.x),
		w(vector.y)
	{
	}
	Vector4::Vector4(
		const Vector3& vector,
		float _w) :
		x(vector.x),
		y(vector.y),
		z(vector.z),
		w(_w)
	{
	}
	Vector4::Vector4(
		float _x,
		const Vector3& vector) :
		x(_x),
		y(vector.x),
		z(vector.y),
		w(vector.z)
	{
	}
	Vector4::Vector4(
		const IntVector4& vector) :
		x(static_cast<float>(vector.x)),
		y(static_cast<float>(vector.y)),
		z(static_cast<float>(vector.z)),
		w(static_cast<float>(vector.w))
	{
	}
	Vector4::Vector4(
		const IntVector2& vector,
		float _z,
		float _w) :
		x(static_cast<float>(vector.x)),
		y(static_cast<float>(vector.y)),
		z(_z),
		w(_w)
	{
	}
	Vector4::Vector4(
		float _x,
		const IntVector2& vector,
		float _w) :
		x(_x),
		y(static_cast<float>(vector.x)),
		z(static_cast<float>(vector.y)),
		w(_w)
	{
	}
	Vector4::Vector4(
		float _x,
		float _y,
		const IntVector2& vector) :
		x(_x),
		y(_y),
		z(static_cast<float>(vector.x)),
		w(static_cast<float>(vector.y))
	{
	}
	Vector4::Vector4(
		const IntVector3& vector,
		float _w) :
		x(static_cast<float>(vector.x)),
		y(static_cast<float>(vector.y)),
		z(static_cast<float>(vector.z)),
		w(_w)
	{
	}
	Vector4::Vector4(
		float _x,
		const IntVector3& vector) :
		x(_x),
		y(static_cast<float>(vector.x)),
		z(static_cast<float>(vector.y)),
		w(static_cast<float>(vector.z))
	{
	}

	std::string Vector4::getString() const noexcept
	{
		auto ss = std::stringstream();
		ss << x << " " << y << " " << z << " " << w;
		return ss.str();
	}
	float Vector4::getDotProduct(const Vector4& vector) const noexcept
	{
		auto result = *this * vector;
		return (result.x + result.y) + (result.z + result.w);
	}
	float Vector4::getDotProduct(const IntVector4& vector) const noexcept
	{
		auto result = *this * vector;
		return (result.x + result.y) + (result.z + result.w);
	}
	float Vector4::getLength() const noexcept
	{
		return sqrt(getDotProduct(*this));
	}
	float Vector4::getDistance(const Vector4& vector) const noexcept
	{
		return sqrt(getDotProduct(*this - vector));
	}
	float Vector4::getDistance(const IntVector4& vector) const noexcept
	{
		return sqrt(getDotProduct(*this - vector));
	}
	Vector4 Vector4::getNormalized() const noexcept
	{
		return *this * (1.0f / sqrt(getDotProduct(*this)));
	}
	Vector4 Vector4::getReflected(const Vector4& normal) const noexcept
	{
		return *this - normal * getDotProduct(normal) * 2.0f;
	}
	Vector4 Vector4::getRefracted(const Vector4& normal, float eta) const noexcept
	{
		auto dot = getDotProduct(normal);
		auto k = (1.0f - eta * eta * (1.0f - dot * dot));

		return Vector4(k >= 0.0f ?
			(*this * eta - normal * (eta * dot + sqrt(k))) :
			Vector4(0.0f));
	}
	Vector4 Vector4::getSine() const noexcept
	{
		return Vector4(
			sin(x),
			sin(y),
			sin(z),
			sin(w));
	}
	Vector4 Vector4::getCosine() const noexcept
	{
		return Vector4(
			cos(x),
			cos(y),
			cos(z),
			cos(w));
	}
	Vector4 Vector4::getTangent() const noexcept
	{
		return Vector4(
			tan(x),
			tan(y),
			tan(z),
			tan(w));
	}
	Vector4 Vector4::getCotangent() const noexcept
	{
		return Vector4(
			1.0f / tan(x),
			1.0f / tan(y),
			1.0f / tan(z),
			1.0f / tan(w));
	}

	Vector2 Vector4::getVector2() const noexcept
	{
		return Vector2(x, y);
	}
	Vector3 Vector4::getVector3() const noexcept
	{
		return Vector3(x, y, z);
	}

	bool Vector4::operator==(const Vector4& vector) const noexcept
	{
		return
			x == vector.x &&
			y == vector.y &&
			z == vector.z &&
			w == vector.w;
	}
	bool Vector4::operator!=(const Vector4& vector) const noexcept
	{
		return
			x != vector.x ||
			y != vector.y ||
			z != vector.z ||
			w != vector.w;
	}

	Vector4& Vector4::operator--() noexcept
	{
		--x;
		--y;
		--z;
		--w;
		return *this;
	}
	Vector4& Vector4::operator++() noexcept
	{
		++x;
		++y;
		++z;
		++w;
		return *this;
	}
	Vector4 Vector4::operator--(int) noexcept
	{
		auto result = Vector4(*this);
		--x;
		--y;
		--z;
		--w;
		return result;
	}
	Vector4 Vector4::operator++(int) noexcept
	{
		auto result = Vector4(*this);
		++x;
		++y;
		++z;
		++w;
		return result;
	}
	Vector4 Vector4::operator-() const noexcept
	{
		return Vector4(
			-x,
			-y,
			-z,
			-w);
	}

	Vector4 Vector4::operator-(const Vector4& vector) const noexcept
	{
		return Vector4(
			x - vector.x,
			y - vector.y,
			z - vector.z,
			w - vector.w);
	}
	Vector4 Vector4::operator+(const Vector4& vector) const noexcept
	{
		return Vector4(
			x + vector.x,
			y + vector.y,
			z + vector.z,
			w + vector.w);
	}
	Vector4 Vector4::operator/(const Vector4& vector) const noexcept
	{
		return Vector4(
			x / vector.x,
			y / vector.y,
			z / vector.z,
			w / vector.w);
	}
	Vector4 Vector4::operator*(const Vector4& vector) const noexcept
	{
		return Vector4(
			x * vector.x,
			y * vector.y,
			z * vector.z,
			w * vector.w);
	}
	Vector4& Vector4::operator-=(const Vector4& vector) noexcept
	{
		x -= vector.x;
		y -= vector.y;
		z -= vector.z;
		w -= vector.w;
		return *this;
	}
	Vector4& Vector4::operator+=(const Vector4& vector) noexcept
	{
		x += vector.x;
		y += vector.y;
		z += vector.z;
		w += vector.w;
		return *this;
	}
	Vector4& Vector4::operator/=(const Vector4& vector) noexcept
	{
		x /= vector.x;
		y /= vector.y;
		z /= vector.z;
		w /= vector.w;
		return *this;
	}
	Vector4& Vector4::operator*=(const Vector4& vector) noexcept
	{
		x *= vector.x;
		y *= vector.y;
		z *= vector.z;
		w *= vector.w;
		return *this;
	}

	Vector4 Vector4::operator-(const IntVector4& vector) const noexcept
	{
		return Vector4(
			x - vector.x,
			y - vector.y,
			z - vector.z,
			w - vector.w);
	}
	Vector4 Vector4::operator+(const IntVector4& vector) const noexcept
	{
		return Vector4(
			x + vector.x,
			y + vector.y,
			z + vector.z,
			w + vector.w);
	}
	Vector4 Vector4::operator/(const IntVector4& vector) const noexcept
	{
		return Vector4(
			x / vector.x,
			y / vector.y,
			z / vector.z,
			w / vector.w);
	}
	Vector4 Vector4::operator*(const IntVector4& vector) const noexcept
	{
		return Vector4(
			x * vector.x,
			y * vector.y,
			z * vector.z,
			w * vector.w);
	}
	Vector4& Vector4::operator-=(const IntVector4& vector) noexcept
	{
		x -= static_cast<float>(vector.x);
		y -= static_cast<float>(vector.y);
		z -= static_cast<float>(vector.z);
		w -= static_cast<float>(vector.w);
		return *this;
	}
	Vector4& Vector4::operator+=(const IntVector4& vector) noexcept
	{
		x += static_cast<float>(vector.x);
		y += static_cast<float>(vector.y);
		z += static_cast<float>(vector.z);
		w += static_cast<float>(vector.w);
		return *this;
	}
	Vector4& Vector4::operator/=(const IntVector4& vector) noexcept
	{
		x /= static_cast<float>(vector.x);
		y /= static_cast<float>(vector.y);
		z /= static_cast<float>(vector.z);
		w /= static_cast<float>(vector.w);
		return *this;
	}
	Vector4& Vector4::operator*=(const IntVector4& vector) noexcept
	{
		x *= static_cast<float>(vector.x);
		y *= static_cast<float>(vector.y);
		z *= static_cast<float>(vector.z);
		w *= static_cast<float>(vector.w);
		return *this;
	}

	Vector4 Vector4::operator-(float value) const noexcept
	{
		return Vector4(
			x - value,
			y - value,
			z - value,
			w - value);
	}
	Vector4 Vector4::operator+(float value) const noexcept
	{
		return Vector4(
			x + value,
			y + value,
			z + value,
			w + value);
	}
	Vector4 Vector4::operator/(float value) const noexcept
	{
		return Vector4(
			x / value,
			y / value,
			z / value,
			w / value);
	}
	Vector4 Vector4::operator*(float value) const noexcept
	{
		return Vector4(
			x * value,
			y * value,
			z * value,
			w * value);
	}
	Vector4& Vector4::operator-=(float value) noexcept
	{
		x -= value;
		y -= value;
		z -= value;
		w -= value;
		return *this;
	}
	Vector4& Vector4::operator+=(float value) noexcept
	{
		x += value;
		y += value;
		z += value;
		w += value;
		return *this;
	}
	Vector4& Vector4::operator/=(float value) noexcept
	{
		x /= value;
		y /= value;
		z /= value;
		w /= value;
		return *this;
	}
	Vector4& Vector4::operator*=(float value) noexcept
	{
		x *= value;
		y *= value;
		z *= value;
		w *= value;
		return *this;
	}

	const Vector4 Vector4::zero = Vector4(0.0f);
	const Vector4 Vector4::minusOne = Vector4(-1.0f);
	const Vector4 Vector4::one = Vector4(1.0f);
}
