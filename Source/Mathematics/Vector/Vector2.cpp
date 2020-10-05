#include "Injector/Mathematics/Vector/Vector2.hpp"

#include <cmath>
#include <sstream>

namespace Injector
{
	Vector2::Vector2() noexcept :
		x(0.0f),
		y(0.0f)
	{
	}
	Vector2::Vector2(
		float xy) noexcept :
		x(xy),
		y(xy)
	{
	}
	Vector2::Vector2(
		float _x,
		float _y) noexcept :
		x(_x),
		y(_y)
	{
	}
	Vector2::Vector2(
		const IntVector2& vector) noexcept :
		x(static_cast<float>(vector.x)),
		y(static_cast<float>(vector.y))
	{
	}

	std::string Vector2::getString() const noexcept
	{
		auto ss = std::stringstream();
		ss << x << " " << y;
		return ss.str();
	}
	float Vector2::getDotProduct(const Vector2& vector) const noexcept
	{
		auto result = *this * vector;
		return result.x + result.y;
	}
	float Vector2::getDotProduct(const IntVector2& vector) const noexcept
	{
		auto result = *this * vector;
		return result.x + result.y;
	}
	float Vector2::getLength() const noexcept
	{
		return sqrt(getDotProduct(*this));
	}
	float Vector2::getDistance(const Vector2& vector) const noexcept
	{
		return sqrt(getDotProduct(*this - vector));
	}
	float Vector2::getDistance(const IntVector2& vector) const noexcept
	{
		return sqrt(getDotProduct(*this - vector));
	}
	Vector2 Vector2::getNormalized() const noexcept
	{
		return *this * (1.0f / sqrt(getDotProduct(*this)));
	}
	Vector2 Vector2::getReflected(const Vector2& normal) const noexcept
	{
		return *this - normal * getDotProduct(normal) * 2.0f;
	}
	Vector2 Vector2::getRefracted(const Vector2& normal, float eta) const noexcept
	{
		auto dot = getDotProduct(normal);
		auto k = (1.0f - eta * eta * (1.0f - dot * dot));

		return Vector2(k >= 0.0f ?
			(*this * eta - normal * (eta * dot + sqrt(k))) :
			Vector2(0.0f));
	}
	Vector2 Vector2::getSine() const noexcept
	{
		return Vector2(
			sin(x),
			sin(y));
	}
	Vector2 Vector2::getCosine() const noexcept
	{
		return Vector2(
			cos(x),
			cos(y));
	}
	Vector2 Vector2::getTangent() const noexcept
	{
		return Vector2(
			tan(x),
			tan(y));
	}
	Vector2 Vector2::getCotangent() const noexcept
	{
		return Vector2(
			1.0f / tan(x),
			1.0f / tan(y));
	}

	bool Vector2::operator==(const Vector2& vector) const noexcept
	{
		return
			x == vector.x &&
			y == vector.y;
	}
	bool Vector2::operator!=(const Vector2& vector) const noexcept
	{
		return
			x != vector.x ||
			y != vector.y;
	}

	Vector2& Vector2::operator--() noexcept
	{
		--x;
		--y;
		return *this;
	}
	Vector2& Vector2::operator++() noexcept
	{
		++x;
		++y;
		return *this;
	}
	Vector2 Vector2::operator--(int) noexcept
	{
		auto result = Vector2(*this);
		--x;
		--y;
		return result;
	}
	Vector2 Vector2::operator++(int) noexcept
	{
		auto result = Vector2(*this);
		++x;
		++y;
		return result;
	}
	Vector2 Vector2::operator-() const noexcept
	{
		return Vector2(-x, -y);
	}

	Vector2 Vector2::operator-(const Vector2& vector) const noexcept
	{
		return Vector2(
			x - vector.x,
			y - vector.y);
	}
	Vector2 Vector2::operator+(const Vector2& vector) const noexcept
	{
		return Vector2(
			x + vector.x,
			y + vector.y);
	}
	Vector2 Vector2::operator/(const Vector2& vector) const noexcept
	{
		return Vector2(
			x / vector.x,
			y / vector.y);
	}
	Vector2 Vector2::operator*(const Vector2& vector) const noexcept
	{
		return Vector2(
			x * vector.x,
			y * vector.y);
	}
	Vector2& Vector2::operator-=(const Vector2& vector) noexcept
	{
		x -= vector.x;
		y -= vector.y;
		return *this;
	}
	Vector2& Vector2::operator+=(const Vector2& vector) noexcept
	{
		x += vector.x;
		y += vector.y;
		return *this;
	}
	Vector2& Vector2::operator/=(const Vector2& vector) noexcept
	{
		x /= vector.x;
		y /= vector.y;
		return *this;
	}
	Vector2& Vector2::operator*=(const Vector2& vector) noexcept
	{
		x *= vector.x;
		y *= vector.y;
		return *this;
	}

	Vector2 Vector2::operator-(const IntVector2& vector) const noexcept
	{
		return Vector2(
			x - vector.x,
			y - vector.y);
	}
	Vector2 Vector2::operator+(const IntVector2& vector) const noexcept
	{
		return Vector2(
			x + vector.x,
			y + vector.y);
	}
	Vector2 Vector2::operator/(const IntVector2& vector) const noexcept
	{
		return Vector2(
			x / vector.x,
			y / vector.y);
	}
	Vector2 Vector2::operator*(const IntVector2& vector) const noexcept
	{
		return Vector2(
			x * vector.x,
			y * vector.y);
	}
	Vector2& Vector2::operator-=(const IntVector2& vector) noexcept
	{
		x -= static_cast<float>(vector.x);
		y -= static_cast<float>(vector.y);
		return *this;
	}
	Vector2& Vector2::operator+=(const IntVector2& vector) noexcept
	{
		x += static_cast<float>(vector.x);
		y += static_cast<float>(vector.y);
		return *this;
	}
	Vector2& Vector2::operator/=(const IntVector2& vector) noexcept
	{
		x /= static_cast<float>(vector.x);
		y /= static_cast<float>(vector.y);
		return *this;
	}
	Vector2& Vector2::operator*=(const IntVector2& vector) noexcept
	{
		x *= static_cast<float>(vector.x);
		y *= static_cast<float>(vector.y);
		return *this;
	}

	Vector2 Vector2::operator-(float value) const noexcept
	{
		return Vector2(
			x - value,
			y - value);
	}
	Vector2 Vector2::operator+(float value) const noexcept
	{
		return Vector2(
			x + value,
			y + value);
	}
	Vector2 Vector2::operator/(float value) const noexcept
	{
		return Vector2(
			x / value,
			y / value);
	}
	Vector2 Vector2::operator*(float value) const noexcept
	{
		return Vector2(
			x * value,
			y * value);
	}
	Vector2& Vector2::operator-=(float value) noexcept
	{
		x -= value;
		y -= value;
		return *this;
	}
	Vector2& Vector2::operator+=(float value) noexcept
	{
		x += value;
		y += value;
		return *this;
	}
	Vector2& Vector2::operator/=(float value) noexcept
	{
		x /= value;
		y /= value;
		return *this;
	}
	Vector2& Vector2::operator*=(float value) noexcept
	{
		x *= value;
		y *= value;
		return *this;
	}

	const Vector2 Vector2::zero = Vector2(0.0f);
	const Vector2 Vector2::minusOne = Vector2(-1.0f);
	const Vector2 Vector2::one = Vector2(1.0f);

	bool Vector2::less(
		const Vector2& a,
		const Vector2& b) noexcept
	{
		return std::tie(a.x, a.y) <
			std::tie(b.x, b.y);
	}
}
