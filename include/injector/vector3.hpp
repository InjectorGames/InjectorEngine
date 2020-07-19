#pragma once
#include <injector/vector2.hpp>
#include <injector/int_vector3.hpp>

namespace INJECTOR_NAMESPACE
{
	struct Vector3
	{
		float x, y, z;

		Vector3(float x = 0.0f, float y = 0.0f, float z = 0.0f);
		Vector3(const IntVector3& other);
		Vector3(const Vector2& other, float z = 0.0f);
		Vector3(const IntVector2& other, float z = 0.0f);

		float getMagnitude();
		float getDot(const Vector3& other);
		float getDistance(const Vector3& other);
		Vector3 getCross(const Vector3& other);

		bool operator==(const Vector3& other);
		bool operator!=(const Vector3& other);

		Vector3& operator--();
		Vector3& operator++();
		Vector3 operator--(int);
		Vector3 operator++(int);

		Vector3 operator-(const Vector3& other);
		Vector3 operator+(const Vector3& other);
		Vector3 operator/(const Vector3& other);
		Vector3 operator*(const Vector3& other);
		Vector3& operator-=(const Vector3& other);
		Vector3& operator+=(const Vector3& other);
		Vector3& operator/=(const Vector3& other);
		Vector3& operator*=(const Vector3& other);

		Vector3 operator-(const IntVector3& other);
		Vector3 operator+(const IntVector3& other);
		Vector3 operator/(const IntVector3& other);
		Vector3 operator*(const IntVector3& other);
		Vector3& operator-=(const IntVector3& other);
		Vector3& operator+=(const IntVector3& other);
		Vector3& operator/=(const IntVector3& other);
		Vector3& operator*=(const IntVector3& other);

		Vector3 operator-(float value);
		Vector3 operator+(float value);
		Vector3 operator/(float value);
		Vector3 operator*(float value);
		Vector3& operator-=(float value);
		Vector3& operator+=(float value);
		Vector3& operator/=(float value);
		Vector3& operator*=(float value);
	};
}
