#pragma once
#include <injector/vector3.hpp>
#include <injector/int_vector4.hpp>

namespace INJECTOR_NAMESPACE
{
	struct Vector4
	{
		float x, y, z, w;

		Vector4();
		Vector4(float xyzw);
		Vector4(float x, float y, float z, float w);
		Vector4(const Vector2& vector, float z, float w);
		Vector4(float x, const Vector2& vector, float w);
		Vector4(float x, float y, const Vector2& vector);
		Vector4(const Vector3& vector, float w);
		Vector4(float x, const Vector3& vector);
		Vector4(const IntVector4& vector);
		Vector4(const IntVector2& vector, float z, float w);
		Vector4(float x, const IntVector2& vector, float w);
		Vector4(float x, float y, const IntVector2& vector);
		Vector4(const IntVector3& vector, float w);
		Vector4(float x, const IntVector3& vector);

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

		static const Vector4 zero;
		static const Vector4 minusOne;
		static const Vector4 one;
	};
}
