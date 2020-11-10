#pragma once
#include "Injector/Mathematics/Vector/Vector3.hpp"
#include "Injector/Mathematics/Vector/IntVector4.hpp"

namespace Injector
{
	struct Vector4 final
	{
		float x, y, z, w;

		Vector4() noexcept;
		explicit Vector4(float xyzw) noexcept;
		Vector4(float x, float y, float z, float w) noexcept;
		Vector4(const Vector2& vector, float z, float w) noexcept;
		Vector4(float x, const Vector2& vector, float w) noexcept;
		Vector4(float x, float y, const Vector2& vector) noexcept;
		Vector4(const Vector3& vector, float w) noexcept;
		Vector4(float x, const Vector3& vector) noexcept;
		explicit Vector4(const IntVector4& vector) noexcept;
		Vector4(const IntVector2& vector, float z, float w) noexcept;
		Vector4(float x, const IntVector2& vector, float w) noexcept;
		Vector4(float x, float y, const IntVector2& vector) noexcept;
		Vector4(const IntVector3& vector, float w) noexcept;
		Vector4(float x, const IntVector3& vector) noexcept;

		std::string getString() const noexcept;
		float getDotProduct(const Vector4& vector) const noexcept;
		float getDotProduct(const IntVector4& vector) const noexcept;
		float getLength() const noexcept;
		float getDistance(const Vector4& vector) const noexcept;
		float getDistance(const IntVector4& vector) const noexcept;
		Vector4 getNormalized() const noexcept;
		Vector4 getReflected(const Vector4& normal) const noexcept;
		Vector4 getRefracted(const Vector4& normal, float eta) const noexcept;
		Vector4 getSine() const noexcept;
		Vector4 getCosine() const noexcept;
		Vector4 getTangent() const noexcept;
		Vector4 getCotangent() const noexcept;

		Vector2 getVector2() const noexcept;
		Vector3 getVector3() const noexcept;

		bool operator==(const Vector4& vector) const noexcept;
		bool operator!=(const Vector4& vector) const noexcept;

		Vector4& operator--() noexcept;
		Vector4& operator++() noexcept;
		Vector4 operator--(int) noexcept;
		Vector4 operator++(int) noexcept;
		Vector4 operator-() const noexcept;

		Vector4 operator-(const Vector4& vector) const noexcept;
		Vector4 operator+(const Vector4& vector) const noexcept;
		Vector4 operator/(const Vector4& vector) const noexcept;
		Vector4 operator*(const Vector4& vector) const noexcept;
		Vector4& operator-=(const Vector4& vector) noexcept;
		Vector4& operator+=(const Vector4& vector) noexcept;
		Vector4& operator/=(const Vector4& vector) noexcept;
		Vector4& operator*=(const Vector4& vector) noexcept;

		Vector4 operator-(const IntVector4& vector) const noexcept;
		Vector4 operator+(const IntVector4& vector) const noexcept;
		Vector4 operator/(const IntVector4& vector) const noexcept;
		Vector4 operator*(const IntVector4& vector) const noexcept;
		Vector4& operator-=(const IntVector4& vector) noexcept;
		Vector4& operator+=(const IntVector4& vector) noexcept;
		Vector4& operator/=(const IntVector4& vector) noexcept;
		Vector4& operator*=(const IntVector4& vector) noexcept;

		Vector4 operator-(float value) const noexcept;
		Vector4 operator+(float value) const noexcept;
		Vector4 operator/(float value) const noexcept;
		Vector4 operator*(float value) const noexcept;
		Vector4& operator-=(float value) noexcept;
		Vector4& operator+=(float value) noexcept;
		Vector4& operator/=(float value) noexcept;
		Vector4& operator*=(float value) noexcept;

		// (0.0f, 0.0f, 0.0f, 0.0f)
		static const Vector4 zero;
		// (-1.0f, -1.0f, -1.0f, -1.0f)
		static const Vector4 minusOne;
		// (1.0f, 1.0f, 1.0f, 1.0f)
		static const Vector4 one;
		// (-0.5f, -0.5f, -0.5f, -0.5f)
		static const Vector4 minusHalf;
		// (0.5f, 0.5f, 0.5f, 0.5f)
		static const Vector4 half;

		static bool less(
			const Vector4& a,
			const Vector4& b) noexcept;

		struct Less
		{
			bool operator()(
				const Vector4& a,
				const Vector4& b) const noexcept
			{
				return less(a, b);
			}
		};
	};
}
