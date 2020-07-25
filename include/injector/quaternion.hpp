#pragma once
#include <injector/vector3.hpp>
#include <injector/matrix3.hpp>
#include <injector/matrix4.hpp>

namespace INJECTOR_NAMESPACE
{
	struct Quaternion
	{
		float x, y, z, w;

		Quaternion();
		Quaternion(float x, float y, float z, float w);
		Quaternion(const Vector3& vector, float w);
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

		float getRoll() const noexcept;
		float getPitch() const noexcept;
		float getYaw() const noexcept;
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
	};
}