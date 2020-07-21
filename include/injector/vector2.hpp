#pragma once
#include <injector/int_vector2.hpp>

namespace INJECTOR_NAMESPACE
{
	struct Vector2
	{
		float x, y;

		Vector2();
		Vector2(float xy);
		Vector2(float x, float y);
		Vector2(const IntVector2& vector);

		float getDotProduct(const Vector2& vector) const noexcept;
		float getDotProduct(const IntVector2& vector) const noexcept;
		float getLength() const noexcept;
		float getDistance(const Vector2& vector) const noexcept;
		float getDistance(const IntVector2& vector) const noexcept;
		Vector2 getNormalized() const noexcept;
		Vector2 getReflected(const Vector2& normal) const noexcept;
		Vector2 getRefracted(const Vector2& normal, float eta) const noexcept;
		Vector2 getSine() const noexcept;
		Vector2 getCosine() const noexcept;
		Vector2 getTangent() const noexcept;
		Vector2 getCotangent() const noexcept;

		bool operator==(const Vector2& vector) const noexcept;
		bool operator!=(const Vector2& vector) const noexcept;

		Vector2& operator--() noexcept;
		Vector2& operator++() noexcept;
		Vector2 operator--(int) noexcept;
		Vector2 operator++(int) noexcept;

		Vector2 operator-(const Vector2& vector) const noexcept;
		Vector2 operator+(const Vector2& vector) const noexcept;
		Vector2 operator/(const Vector2& vector) const noexcept;
		Vector2 operator*(const Vector2& vector) const noexcept;
		Vector2& operator-=(const Vector2& vector) noexcept;
		Vector2& operator+=(const Vector2& vector) noexcept;
		Vector2& operator/=(const Vector2& vector) noexcept;
		Vector2& operator*=(const Vector2& vector) noexcept;

		Vector2 operator-(const IntVector2& vector) const noexcept;
		Vector2 operator+(const IntVector2& vector) const noexcept;
		Vector2 operator/(const IntVector2& vector) const noexcept;
		Vector2 operator*(const IntVector2& vector) const noexcept;
		Vector2& operator-=(const IntVector2& vector) noexcept;
		Vector2& operator+=(const IntVector2& vector) noexcept;
		Vector2& operator/=(const IntVector2& vector) noexcept;
		Vector2& operator*=(const IntVector2& vector) noexcept;

		Vector2 operator-(float value) const noexcept;
		Vector2 operator+(float value) const noexcept;
		Vector2 operator/(float value) const noexcept;
		Vector2 operator*(float value) const noexcept;
		Vector2& operator-=(float value) noexcept;
		Vector2& operator+=(float value) noexcept;
		Vector2& operator/=(float value) noexcept;
		Vector2& operator*=(float value) noexcept;

		static const Vector2 zero;
		static const Vector2 minusOne;
		static const Vector2 one;
	};
}
