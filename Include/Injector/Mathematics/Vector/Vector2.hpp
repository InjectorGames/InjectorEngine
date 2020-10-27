#pragma once
#include "Injector/Mathematics/Vector/IntVector2.hpp"

namespace Injector
{
	struct Vector2 final
	{
		float x, y;

		Vector2() noexcept;
		explicit Vector2(float xy) noexcept;
		Vector2(float x, float y) noexcept;
		explicit Vector2(const IntVector2& vector) noexcept;

		std::string getString() const noexcept;
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
		Vector2 operator-() const noexcept;

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

		// (0.0f, 0.0f)
		static const Vector2 zero;
		// (-1.0f, -1.0f)
		static const Vector2 minusOne;
		// (1.0f, 1.0f)
		static const Vector2 one;

		static bool less(
			const Vector2& a,
			const Vector2& b) noexcept;

		struct Less
		{
			bool operator()(
				const Vector2& a,
				const Vector2& b) const noexcept
			{
				return less(a, b);
			}
		};
	};
}
