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

		float getMagnitude();
		float getDot(const Vector4& other);
		float getDistance(const Vector4& other);

		bool operator==(const Vector4& other);
		bool operator!=(const Vector4& other);

		Vector4& operator--();
		Vector4& operator++();
		Vector4 operator--(int);
		Vector4 operator++(int);

		Vector4 operator-(const Vector4& other);
		Vector4 operator+(const Vector4& other);
		Vector4 operator/(const Vector4& other);
		Vector4 operator*(const Vector4& other);
		Vector4& operator-=(const Vector4& other);
		Vector4& operator+=(const Vector4& other);
		Vector4& operator/=(const Vector4& other);
		Vector4& operator*=(const Vector4& other);

		Vector4 operator-(const IntVector4& other);
		Vector4 operator+(const IntVector4& other);
		Vector4 operator/(const IntVector4& other);
		Vector4 operator*(const IntVector4& other);
		Vector4& operator-=(const IntVector4& other);
		Vector4& operator+=(const IntVector4& other);
		Vector4& operator/=(const IntVector4& other);
		Vector4& operator*=(const IntVector4& other);

		Vector4 operator-(float value);
		Vector4 operator+(float value);
		Vector4 operator/(float value);
		Vector4 operator*(float value);
		Vector4& operator-=(float value);
		Vector4& operator+=(float value);
		Vector4& operator/=(float value);
		Vector4& operator*=(float value);
	};
}
