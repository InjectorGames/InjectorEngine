#include <injector/vector2.hpp>

#include <cmath>

namespace INJECTOR_NAMESPACE
{
	Vector2::Vector2(float _x, float _y) :
		x(_x),
		y(_y)
	{}

	float Vector2::getMagnitude()
	{
		return std::sqrtf(x * x + y * y);
	}
	float Vector2::getDot(const Vector2& other)
	{
		return x * other.x + y * other.y;
	}
	float Vector2::getDistance(const Vector2& other)
	{
		return std::sqrtf(x - other.x * x - other.x + 
			y - other.y * y - other.y);
	}

	bool Vector2::operator==(const Vector2& other)
	{
		return x == other.x && y == other.y;
	}
	bool Vector2::operator!=(const Vector2& other)
	{
		return x != other.x && y != other.y;
	}

	Vector2& Vector2::operator--()
	{
		--x;
		--y;
		return *this;
	}
	Vector2& Vector2::operator++()
	{
		++x;
		++y;
		return *this;
	}
	Vector2 Vector2::operator--(int)
	{
		auto result = Vector2(*this);
		--x;
		--y;
		return result;
	}
	Vector2 Vector2::operator++(int)
	{
		auto result = Vector2(*this);
		++x;
		++y;
		return result;
	}

	Vector2 Vector2::operator-(const Vector2& other)
	{
		return Vector2(x - other.x, y - other.y);
	}
	Vector2 Vector2::operator+(const Vector2& other)
	{
		return Vector2(x + other.x, y + other.y);
	}
	Vector2 Vector2::operator/(const Vector2& other)
	{
		return Vector2(x / other.x, y / other.y);
	}
	Vector2 Vector2::operator*(const Vector2& other)
	{
		return Vector2(x * other.x, y * other.y);
	}
	Vector2& Vector2::operator-=(const Vector2& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}
	Vector2& Vector2::operator+=(const Vector2& other)
	{
		x += other.x;
		y += other.y;
		return *this;
	}
	Vector2& Vector2::operator/=(const Vector2& other)
	{
		x /= other.x;
		y /= other.y;
		return *this;
	}
	Vector2& Vector2::operator*=(const Vector2& other)
	{
		x *= other.x;
		y *= other.y;
		return *this;
	}

	Vector2 Vector2::operator-(float value)
	{
		return Vector2(x - value, y - value);
	}
	Vector2 Vector2::operator+(float value)
	{
		return Vector2(x + value, y + value);
	}
	Vector2 Vector2::operator/(float value)
	{
		return Vector2(x / value, y / value);
	}
	Vector2 Vector2::operator*(float value)
	{
		return Vector2(x * value, y * value);
	}
	Vector2& Vector2::operator-=(float value)
	{
		x -= value;
		y -= value;
		return *this;
	}
	Vector2& Vector2::operator+=(float value)
	{
		x += value;
		y += value;
		return *this;
	}
	Vector2& Vector2::operator/=(float value)
	{
		x /= value;
		y /= value;
		return *this;
	}
	Vector2& Vector2::operator*=(float value)
	{
		x *= value;
		y *= value;
		return *this;
	}
}