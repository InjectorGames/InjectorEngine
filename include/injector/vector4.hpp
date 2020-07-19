#pragma once
#include <injector/vector3.hpp>
#include <injector/int_vector4.hpp>

namespace INJECTOR_NAMESPACE
{
	struct Vector4
	{
		float x, y, z, w;

		Vector4(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f);
		Vector4(const IntVector4& other);
		Vector4(const Vector2& other, float z = 0.0f, float w = 0.0f);
		Vector4(const IntVector2& other, float z = 0.0f, float w = 0.0f);
		Vector4(const Vector3& other, float w = 0.0f);
		Vector4(const IntVector3& other, float w = 0.0f);

		float getMagnitude() const noexcept;
		float getDot(const Vector4& other) const noexcept;
		float getDistance(const Vector4& other) const noexcept;
		Vector4 getNegative() const noexcept;
		Vector4 getNormalized() const noexcept;
		Vector4 getSine() const noexcept;
		Vector4 getCosine() const noexcept;
		Vector4 getTangent() const noexcept;
		Vector4 getCotangent() const noexcept;

		bool operator==(const Vector4& other) const noexcept;
		bool operator!=(const Vector4& other) const noexcept;

		Vector4& operator--() noexcept;
		Vector4& operator++() noexcept;
		Vector4 operator--(int) noexcept;
		Vector4 operator++(int) noexcept;

		Vector4 operator-(const Vector4& other) const noexcept;
		Vector4 operator+(const Vector4& other) const noexcept;
		Vector4 operator/(const Vector4& other) const noexcept;
		Vector4 operator*(const Vector4& other) const noexcept;
		Vector4& operator=(const Vector4& other) noexcept;
		Vector4& operator-=(const Vector4& other) noexcept;
		Vector4& operator+=(const Vector4& other) noexcept;
		Vector4& operator/=(const Vector4& other) noexcept;
		Vector4& operator*=(const Vector4& other) noexcept;

		Vector4 operator-(const IntVector4& other) const noexcept;
		Vector4 operator+(const IntVector4& other) const noexcept;
		Vector4 operator/(const IntVector4& other) const noexcept;
		Vector4 operator*(const IntVector4& other) const noexcept;
		Vector4& operator=(const IntVector4& other) noexcept;
		Vector4& operator-=(const IntVector4& other) noexcept;
		Vector4& operator+=(const IntVector4& other) noexcept;
		Vector4& operator/=(const IntVector4& other) noexcept;
		Vector4& operator*=(const IntVector4& other) noexcept;

		Vector4 operator-(float value) const noexcept;
		Vector4 operator+(float value) const noexcept;
		Vector4 operator/(float value) const noexcept;
		Vector4 operator*(float value) const noexcept;
		Vector4& operator=(float value) noexcept;
		Vector4& operator-=(float value) noexcept;
		Vector4& operator+=(float value) noexcept;
		Vector4& operator/=(float value) noexcept;
		Vector4& operator*=(float value) noexcept;

		static const Vector4 zero;
		static const Vector4 minusOne;
		static const Vector4 one;
	};
}
