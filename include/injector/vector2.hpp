#pragma once
#include <injector/int_vector2.hpp>

namespace INJECTOR_NAMESPACE
{
	struct Vector2
	{
		float x, y;

		Vector2(float x = 0.0f, float y = 0.0f);
		Vector2(const IntVector2& other);

		float getMagnitude();
		float getDot(const Vector2& other);
		float getDistance(const Vector2& other);

		bool operator==(const Vector2& other);
		bool operator!=(const Vector2& other);

		Vector2& operator--();
		Vector2& operator++();
		Vector2 operator--(int);
		Vector2 operator++(int);

		Vector2 operator-(const Vector2& other);
		Vector2 operator+(const Vector2& other);
		Vector2 operator/(const Vector2& other);
		Vector2 operator*(const Vector2& other);
		Vector2& operator-=(const Vector2& other);
		Vector2& operator+=(const Vector2& other);
		Vector2& operator/=(const Vector2& other);
		Vector2& operator*=(const Vector2& other);

		Vector2 operator-(const IntVector2& other);
		Vector2 operator+(const IntVector2& other);
		Vector2 operator/(const IntVector2& other);
		Vector2 operator*(const IntVector2& other);
		Vector2& operator-=(const IntVector2& other);
		Vector2& operator+=(const IntVector2& other);
		Vector2& operator/=(const IntVector2& other);
		Vector2& operator*=(const IntVector2& other);

		Vector2 operator-(float value);
		Vector2 operator+(float value);
		Vector2 operator/(float value);
		Vector2 operator*(float value);
		Vector2& operator-=(float value);
		Vector2& operator+=(float value);
		Vector2& operator/=(float value);
		Vector2& operator*=(float value);
	};
}
