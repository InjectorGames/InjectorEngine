#pragma once
#include "Injector/Mathematics/Matrix3.hpp"
#include "Injector/Mathematics/Vector4.hpp"

namespace Injector
{
	struct Matrix4 final
	{
		float m00, m01, m02, m03;
		float m10, m11, m12, m13;
		float m20, m21, m22, m23;
		float m30, m31, m32, m33;

		Matrix4();
		explicit Matrix4(
			float value);
		Matrix4(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33);
		Matrix4(
			const Vector4& column0,
			const Vector4& column1,
			const Vector4& column2,
			const Vector4& column3);

		std::string getString() const noexcept;
		float getDeterminant() const noexcept;
		Matrix4 getTransposed() const noexcept;
		Matrix4 getInverted() const noexcept;
		Matrix4 getScaled(const Vector3& vector) const noexcept;
		Matrix4 getTranslated(const Vector3& vector) const noexcept;
		Matrix4 getRotated(const Vector3& vector, float angle) const noexcept;
		Matrix4 getLookedAt(const Vector3& eye, const Vector3& center, const Vector3& up) const noexcept;

		Vector4 getRow0() const noexcept;
		Vector4 getRow1() const noexcept;
		Vector4 getRow2() const noexcept;
		Vector4 getRow3() const noexcept;
		void setRow0(const Vector4& vector) noexcept;
		void setRow1(const Vector4& vector) noexcept;
		void setRow2(const Vector4& vector) noexcept;
		void setRow3(const Vector4& vector) noexcept;

		Vector4 getColumn0() const noexcept;
		Vector4 getColumn1() const noexcept;
		Vector4 getColumn2() const noexcept;
		Vector4 getColumn3() const noexcept;
		void setColumn0(const Vector4& vector) noexcept;
		void setColumn1(const Vector4& vector) noexcept;
		void setColumn2(const Vector4& vector) noexcept;
		void setColumn3(const Vector4& vector) noexcept;

		Matrix2 getMatrix2() const noexcept;
		Matrix3 getMatrix3() const noexcept;

		bool operator==(const Matrix4& matrix) const noexcept;
		bool operator!=(const Matrix4& matrix) const noexcept;

		Matrix4& operator--() noexcept;
		Matrix4& operator++() noexcept;
		Matrix4 operator--(int) noexcept;
		Matrix4 operator++(int) noexcept;
		Matrix4 operator-() const noexcept;

		Matrix4 operator-(const Matrix4& matrix) const noexcept;
		Matrix4 operator+(const Matrix4& matrix) const noexcept;
		Matrix4 operator/(const Matrix4& matrix) const noexcept;
		Vector4 operator/(const Vector4& vector) const noexcept;
		Matrix4 operator*(const Matrix4& matrix) const noexcept;
		Vector4 operator*(const Vector4& vector) const noexcept;
		Matrix4& operator-=(const Matrix4& matrix) noexcept;
		Matrix4& operator+=(const Matrix4& matrix) noexcept;
		Matrix4& operator/=(const Matrix4& matrix) noexcept;
		Matrix4& operator*=(const Matrix4& matrix) noexcept;

		Matrix4 operator-(float value) const noexcept;
		Matrix4 operator+(float value) const noexcept;
		Matrix4 operator/(float value) const noexcept;
		Matrix4 operator*(float value) const noexcept;
		Matrix4& operator-=(float value) noexcept;
		Matrix4& operator+=(float value) noexcept;
		Matrix4& operator/=(float value) noexcept;
		Matrix4& operator*=(float value) noexcept;

		static Matrix4 createPerspectiveVk(
			float fieldOfView,
			float aspectRatio,
			float nearClipPlane,
			float farClipPlane);
		static Matrix4 createPerspectiveGl(
			float fieldOfView,
			float aspectRatio,
			float nearClipPlane,
			float farClipPlane);
		static Matrix4 createOrthographicVk(
			float left,
			float right,
			float bottom,
			float top,
			float nearClipPlane,
			float farClipPlane);
		static Matrix4 createOrthographicGl(
			float left,
			float right,
			float bottom,
			float top,
			float nearClipPlane,
			float farClipPlane);

		static const Matrix4 zero;
		static const Matrix4 minusOne;
		static const Matrix4 one;
		static const Matrix4 identity;
	};
}
