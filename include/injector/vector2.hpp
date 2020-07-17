#pragma once
#include <injector/defines.hpp>

namespace INJECTOR_NAMESPACE
{
	struct Vector2
	{
		float x, y;

		Vector2(float x = 0.0f, float y = 0.0f);

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
