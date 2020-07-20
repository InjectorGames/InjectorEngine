#pragma once
#include <injector/vector2.hpp>
#include <injector/int_vector3.hpp>

namespace INJECTOR_NAMESPACE
{
	struct Vector3
	{
		float x, y, z;

		Vector3();
		Vector3(float x, float y, float z);
		Vector3(const Vector2& other, float z);
		Vector3(float x, const Vector2& other);
		Vector3(const IntVector3& other);
		Vector3(const IntVector2& other, float z);
		Vector3(float x, const IntVector2& other);

		float getMagnitude() const noexcept;
		float getDot(const Vector3& other) const noexcept;
		float getDistance(const Vector3& other) const noexcept;
		Vector3 getNegative() const noexcept;
		Vector3 getNormalized() const noexcept;
		Vector3 getSine() const noexcept;
		Vector3 getCosine() const noexcept;
		Vector3 getTangent() const noexcept;
		Vector3 getCotangent() const noexcept;
		Vector3 getCross(const Vector3& other) const noexcept;

		bool operator==(const Vector3& other) const noexcept;
		bool operator!=(const Vector3& other) const noexcept;

		Vector3& operator--() noexcept;
		Vector3& operator++() noexcept;
		Vector3 operator--(int) noexcept;
		Vector3 operator++(int) noexcept;

		Vector3 operator-(const Vector3& other) const noexcept;
		Vector3 operator+(const Vector3& other) const noexcept;
		Vector3 operator/(const Vector3& other) const noexcept;
		Vector3 operator*(const Vector3& other) const noexcept;
		Vector3& operator=(const Vector3& other) noexcept;
		Vector3& operator-=(const Vector3& other) noexcept;
		Vector3& operator+=(const Vector3& other) noexcept;
		Vector3& operator/=(const Vector3& other) noexcept;
		Vector3& operator*=(const Vector3& other) noexcept;

		Vector3 operator-(const IntVector3& other) const noexcept;
		Vector3 operator+(const IntVector3& other) const noexcept;
		Vector3 operator/(const IntVector3& other) const noexcept;
		Vector3 operator*(const IntVector3& other) const noexcept;
		Vector3& operator=(const IntVector3& other) noexcept;
		Vector3& operator-=(const IntVector3& other) noexcept;
		Vector3& operator+=(const IntVector3& other) noexcept;
		Vector3& operator/=(const IntVector3& other) noexcept;
		Vector3& operator*=(const IntVector3& other) noexcept;

		Vector3 operator-(float value) const noexcept;
		Vector3 operator+(float value) const noexcept;
		Vector3 operator/(float value) const noexcept;
		Vector3 operator*(float value) const noexcept;
		Vector3& operator=(float value) noexcept;
		Vector3& operator-=(float value) noexcept;
		Vector3& operator+=(float value) noexcept;
		Vector3& operator/=(float value) noexcept;
		Vector3& operator*=(float value) noexcept;

		static const Vector3 zero;
		static const Vector3 minusOne;
		static const Vector3 one;
	};
}
