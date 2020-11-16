#pragma once
#include "Injector/Mathematics/Vector3.hpp"
#include "Matrix4.hpp"

namespace Injector
{
	struct Quaternion final
	{
		float x, y, z, w;

		explicit Quaternion(
			const FloatVector3& eulerAngles =
				FloatVector3()) noexcept;
		Quaternion(
			float x,
			float y,
			float z,
			float w) noexcept;
		Quaternion(
			float angle,
			const FloatVector3& axis) noexcept;
		Quaternion(
			const FloatVector3& a,
			const FloatVector3& b) noexcept;
		explicit Quaternion(
			const FloatMatrix3& matrix) noexcept;
		explicit Quaternion(
			const FloatMatrix4& matrix) noexcept;

		float getDotProduct(const Quaternion& quaternion) const noexcept;
		Quaternion getCrossProduct(const Quaternion& quaternion) const noexcept;
		float getLength() const noexcept;
		Quaternion getNormalized() const noexcept;
		Quaternion getConjugated() const noexcept;
		Quaternion getInverted() const noexcept;
		Quaternion getLookedAt(const FloatVector3& direction, const FloatVector3& up) const noexcept;

		float getAngle() const noexcept;
		float getRoll() const noexcept;
		float getPitch() const noexcept;
		float getYaw() const noexcept;
		FloatVector3 getAxis() const noexcept;
		FloatVector3 getEulerAngles() const noexcept;

		FloatMatrix3 getMatrix3() const noexcept;
		FloatMatrix4 getMatrix4() const noexcept;

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
		FloatVector3 operator*(const FloatVector3& vector) const noexcept;
		FloatVector4 operator*(const FloatVector4& vector) const noexcept;
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

		// Euler Angles (0.0f, 0.0f, 0.0f)
		static const Quaternion zero;

		static bool less(
			const Quaternion& a,
			const Quaternion& b) noexcept;

		struct Less
		{
			bool operator()(
				const Quaternion& a,
				const Quaternion& b) const noexcept
			{
				return less(a, b);
			}
		};
	};
}