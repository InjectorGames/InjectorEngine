#pragma once
#include <injector/int_vector2.hpp>

namespace INJECTOR_NAMESPACE
{
	struct Vector2
	{
		float x, y;

		Vector2();
		Vector2(float x, float y);
		Vector2(const IntVector2& other);

		float getMagnitude() const noexcept;
		float getDot(const Vector2& other) const noexcept;
		float getDistance(const Vector2& other) const noexcept;
		Vector2 getNegative() const noexcept;
		Vector2 getNormalized() const noexcept;
		Vector2 getSine() const noexcept;
		Vector2 getCosine() const noexcept;
		Vector2 getTangent() const noexcept;
		Vector2 getCotangent() const noexcept;

		bool operator==(const Vector2& other) const noexcept;
		bool operator!=(const Vector2& other) const noexcept;

		Vector2& operator--() noexcept;
		Vector2& operator++() noexcept;
		Vector2 operator--(int) noexcept;
		Vector2 operator++(int) noexcept;

		Vector2 operator-(const Vector2& other) const noexcept;
		Vector2 operator+(const Vector2& other) const noexcept;
		Vector2 operator/(const Vector2& other) const noexcept;
		Vector2 operator*(const Vector2& other) const noexcept;
		Vector2& operator=(const Vector2& other) noexcept;
		Vector2& operator-=(const Vector2& other) noexcept;
		Vector2& operator+=(const Vector2& other) noexcept;
		Vector2& operator/=(const Vector2& other) noexcept;
		Vector2& operator*=(const Vector2& other) noexcept;

		Vector2 operator-(const IntVector2& other) const noexcept;
		Vector2 operator+(const IntVector2& other) const noexcept;
		Vector2 operator/(const IntVector2& other) const noexcept;
		Vector2 operator*(const IntVector2& other) const noexcept;
		Vector2& operator=(const IntVector2& other) noexcept;
		Vector2& operator-=(const IntVector2& other) noexcept;
		Vector2& operator+=(const IntVector2& other) noexcept;
		Vector2& operator/=(const IntVector2& other) noexcept;
		Vector2& operator*=(const IntVector2& other) noexcept;

		Vector2 operator-(float value) const noexcept;
		Vector2 operator+(float value) const noexcept;
		Vector2 operator/(float value) const noexcept;
		Vector2 operator*(float value) const noexcept;
		Vector2& operator=(float value) noexcept;
		Vector2& operator-=(float value) noexcept;
		Vector2& operator+=(float value) noexcept;
		Vector2& operator/=(float value) noexcept;
		Vector2& operator*=(float value) noexcept;

		static const Vector2 zero;
		static const Vector2 minusOne;
		static const Vector2 one;
	};
}
