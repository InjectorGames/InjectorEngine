#include <injector/vector2.hpp>

#include <cmath>

namespace INJECTOR_NAMESPACE
{
	Vector2::Vector2(float _x, float _y) :
		x(_x), y(_y)
	{}
	Vector2::Vector2(const IntVector2& other) :
		x(static_cast<float>(other.x)),
		y(static_cast<float>(other.y))
	{}

	float Vector2::getMagnitude() const noexcept
	{
		return std::sqrtf(x * x + y * y);
	}
	float Vector2::getDot(const Vector2& other) const noexcept
	{
		return x * other.x + y * other.y;
	}
	float Vector2::getDistance(const Vector2& other) const noexcept
	{
		return std::sqrtf(
			x - other.x * x - other.x + 
			y - other.y * y - other.y);
	}
	Vector2 Vector2::getNegative() const noexcept
	{
		return Vector2(-x, -y);
	}
	Vector2 Vector2::getNormalized() const noexcept
	{
		auto magnitude = 1.0f / getMagnitude();
		return Vector2(x * magnitude, y * magnitude);
	}
	Vector2 Vector2::getSine() const noexcept
	{
		return Vector2(std::sinf(x), std::sinf(y));
	}
	Vector2 Vector2::getCosine() const noexcept
	{
		return Vector2(std::cosf(x), std::cosf(y));
	}
	Vector2 Vector2::getTangent() const noexcept
	{
		return Vector2(std::tanf(x), std::tanf(y));
	}
	Vector2 Vector2::getCotangent() const noexcept
	{
		return Vector2(1.0f / std::tanf(x), 1.0f / std::tanf(y));
	}

	bool Vector2::operator==(const Vector2& other) const noexcept
	{
		return x == other.x && y == other.y;
	}
	bool Vector2::operator!=(const Vector2& other) const noexcept
	{
		return x != other.x || y != other.y;
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

	Vector2 Vector2::operator-(const Vector2& other) const noexcept
	{
		return Vector2(x - other.x, y - other.y);
	}
	Vector2 Vector2::operator+(const Vector2& other) const noexcept
	{
		return Vector2(x + other.x, y + other.y);
	}
	Vector2 Vector2::operator/(const Vector2& other) const noexcept
	{
		return Vector2(x / other.x, y / other.y);
	}
	Vector2 Vector2::operator*(const Vector2& other) const noexcept
	{
		return Vector2(x * other.x, y * other.y);
	}
	Vector2& Vector2::operator=(const Vector2& other) noexcept
	{
		x = other.x;
		y = other.y;
		return *this;
	}
	Vector2& Vector2::operator-=(const Vector2& other) noexcept
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}
	Vector2& Vector2::operator+=(const Vector2& other) noexcept
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	Vector2& Vector2::operator/=(const Vector2& other) noexcept
	{
		x /= other.x;
		y /= other.y;
		return *this;
	}
	Vector2& Vector2::operator*=(const Vector2& other) noexcept
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}

	Vector2 Vector2::operator-(const IntVector2& other) const noexcept
	{
		return Vector2(x - other.x, y - other.y);
	}
	Vector2 Vector2::operator+(const IntVector2& other) const noexcept
	{
		return Vector2(x + other.x, y + other.y);
	}
	Vector2 Vector2::operator/(const IntVector2& other) const noexcept
	{
		return Vector2(x / other.x, y / other.y);
	}
	Vector2 Vector2::operator*(const IntVector2& other) const noexcept
	{
		return Vector2(x * other.x, y * other.y);
	}
	Vector2& Vector2::operator=(const IntVector2& other) noexcept
	{
		x = other.x;
		y = other.y;
		return *this;
	}
	Vector2& Vector2::operator-=(const IntVector2& other) noexcept
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}
	Vector2& Vector2::operator+=(const IntVector2& other) noexcept
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	Vector2& Vector2::operator/=(const IntVector2& other) noexcept
	{
		x /= other.x;
		y /= other.y;
		return *this;
	}
	Vector2& Vector2::operator*=(const IntVector2& other) noexcept
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}

	Vector2 Vector2::operator-(float value) const noexcept
	{
		return Vector2(x - value, y - value);
	}
	Vector2 Vector2::operator+(float value) const noexcept
	{
		return Vector2(x + value, y + value);
	}
	Vector2 Vector2::operator/(float value) const noexcept
	{
		return Vector2(x / value, y / value);
	}
	Vector2 Vector2::operator*(float value) const noexcept
	{
		return Vector2(x * value, y * value);
	}
	Vector2& Vector2::operator=(float value) noexcept
	{
		x = value;
		y = value;
		return *this;
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

	const Vector2 Vector2::zero = Vector2(0.0f, 0.0f);
	const Vector2 Vector2::minusOne = Vector2(-1.0f, -1.0f);
	const Vector2 Vector2::one = Vector2(1.0f, 1.0f);
}
