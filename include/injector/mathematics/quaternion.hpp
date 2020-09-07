#pragma once
#include "Injector/Mathematics/Vector3.hpp"
#include "Injector/Mathematics/Matrix3.hpp"
#include "Injector/Mathematics/Matrix4.hpp"

namespace Injector
{
	struct Quaternion
	{
		float x, y, z, w;

		Quaternion();
		Quaternion(float x, float y, float z, float w);
		Quaternion(float angle, const Vector3& axis);
		Quaternion(const Vector3& eulerAngles);
		Quaternion(const Vector3& a, const Vector3& b);
		Quaternion(const Matrix3& matrix);
		Quaternion(const Matrix4& matrix);

		float getDotProduct(const Quaternion& quaternion) const noexcept;
		Quaternion getCrossProduct(const Quaternion& quaternion) const noexcept;
		float getLength() const noexcept;
		Quaternion getNormalized() const noexcept;
		Quaternion getConjugated() const noexcept;
		Quaternion getInversed() const noexcept;
		Quaternion getLookedAt(const Vector3& direction, const Vector3& up) const noexcept;

		float getAngle() const noexcept;
		float getRoll() const noexcept;
		float getPitch() const noexcept;
		float getYaw() const noexcept;
		Vector3 getAxis() const noexcept;
		Vector3 getEulerAngles() const noexcept;

		Matrix3 getMatrix3() const noexcept;
		Matrix4 getMatrix4() const noexcept;

		bool operator==(const Quaternion& quaternion) const noexcept;
		bool operator!=(const Quaternion& quaternion) const noexcept;

		Quaternion& operator--() noexcept;
		Quaternion& operator++() noexcept;
		Quaternion operator--(int) noexcept;
		Quaternion operator++(int) noexcept;

		Quaternion operator-() const noexcept;
		Quaternion operator+() const noexcept;

		Quaternion operator-(const Quaternion& quaternion) const noexcept;
		Quaternion operator+(const Quaternion& quaternion) const noexcept;
		Quaternion operator*(const Quaternion& quaternion) const noexcept;
		Vector3 operator*(const Vector3& vector) const noexcept;
		Vector4 operator*(const Vector4& vector) const noexcept;
		Quaternion& operator-=(const Quaternion& quaternion) noexcept;
		Quaternion& operator+=(const Quaternion& quaternion) noexcept;
		Quaternion& operator*=(const Quaternion& quaternion) noexcept;

		Quaternion operator-(float value) const noexcept;
		Quaternion operator+(float value) const noexcept;
		Quaternion operator/(float value) const noexcept;
		Quaternion operator*(float value) const noexcept;
		Quaternion& operator-=(float value) noexcept;
		Quaternion& operator+=(float value) noexcept;
		Quaternion& operator/=(float value) noexcept;
		Quaternion& operator*=(float value) noexcept;

		static const Quaternion zero;
	};
}