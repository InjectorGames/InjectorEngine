#pragma once
#include "Injector/Mathematics/Matrix2.hpp"
#include "Injector/Mathematics/Vector3.hpp"

namespace Injector
{
	struct Matrix3 final
	{
		float m00, m01, m02;
		float m10, m11, m12;
		float m20, m21, m22;

		Matrix3();
		explicit Matrix3(
			float value);
		Matrix3(
			float m00, float m01, float m02,
			float m10, float m11, float m12,
			float m20, float m21, float m22);
		Matrix3(
			const Vector3& column0,
			const Vector3& column1,
			const Vector3& column2);

		std::string getString() const noexcept;
		float getDeterminant() const noexcept;
		Matrix3 getTransposed() const noexcept;
		Matrix3 getInverted() const noexcept;

		Vector3 getRow0() const noexcept;
		Vector3 getRow1() const noexcept;
		Vector3 getRow2() const noexcept;
		void setRow0(const Vector3& vector) noexcept;
		void setRow1(const Vector3& vector) noexcept;
		void setRow2(const Vector3& vector) noexcept;

		Vector3 getColumn0() const noexcept;
		Vector3 getColumn1() const noexcept;
		Vector3 getColumn2() const noexcept;
		void setColumn0(const Vector3& vector) noexcept;
		void setColumn1(const Vector3& vector) noexcept;
		void setColumn2(const Vector3& vector) noexcept;

		Matrix2 getMatrix2() const noexcept;

		bool operator==(const Matrix3& matrix) const noexcept;
		bool operator!=(const Matrix3& matrix) const noexcept;

		Matrix3& operator--() noexcept;
		Matrix3& operator++() noexcept;
		Matrix3 operator--(int) noexcept;
		Matrix3 operator++(int) noexcept;
		Matrix3 operator-() const noexcept;

		Matrix3 operator-(const Matrix3& matrix) const noexcept;
		Matrix3 operator+(const Matrix3& matrix) const noexcept;
		Matrix3 operator/(const Matrix3& matrix) const noexcept;
		Vector3 operator/(const Vector3& vector) const noexcept;
		Matrix3 operator*(const Matrix3& matrix) const noexcept;
		Vector3 operator*(const Vector3& vector) const noexcept;
		Matrix3& operator-=(const Matrix3& matrix) noexcept;
		Matrix3& operator+=(const Matrix3& matrix) noexcept;
		Matrix3& operator/=(const Matrix3& matrix) noexcept;
		Matrix3& operator*=(const Matrix3& matrix) noexcept;

		Matrix3 operator-(float value) const noexcept;
		Matrix3 operator+(float value) const noexcept;
		Matrix3 operator/(float value) const noexcept;
		Matrix3 operator*(float value) const noexcept;
		Matrix3& operator-=(float value) noexcept;
		Matrix3& operator+=(float value) noexcept;
		Matrix3& operator/=(float value) noexcept;
		Matrix3& operator*=(float value) noexcept;

		static const Matrix3 zero;
		static const Matrix3 minusOne;
		static const Matrix3 one;
		static const Matrix3 identity;

		static bool less(
			const Matrix3& a,
			const Matrix3& b) noexcept;
	};
}
