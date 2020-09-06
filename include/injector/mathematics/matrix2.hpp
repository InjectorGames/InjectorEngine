#pragma once
#include "Injector/Mathematics/Vector2.hpp"

namespace Injector::Mathematics
{
	struct Matrix2
	{
		float m00, m01;
		float m10, m11;

		Matrix2();
		Matrix2(float value);
		Matrix2(
			float m00, float m01,
			float m10, float m11);
		Matrix2(
			const Vector2& column0,
			const Vector2& column1);

		float getDeterminant() const noexcept;
		Matrix2 getTransposed() const noexcept;
		Matrix2 getInversed() const noexcept;

		Vector2 getRow0() const noexcept;
		Vector2 getRow1() const noexcept;
		void setRow0(const Vector2& vector) noexcept;
		void setRow1(const Vector2& vector) noexcept;

		Vector2 getColumn0() const noexcept;
		Vector2 getColumn1() const noexcept;
		void setColumn0(const Vector2& vector) noexcept;
		void setColumn1(const Vector2& vector) noexcept;

		bool operator==(const Matrix2& matrix) const noexcept;
		bool operator!=(const Matrix2& matrix) const noexcept;

		Matrix2& operator--() noexcept;
		Matrix2& operator++() noexcept;
		Matrix2 operator--(int) noexcept;
		Matrix2 operator++(int) noexcept;
		Matrix2 operator-() const noexcept;

		Matrix2 operator-(const Matrix2& matrix) const noexcept;
		Matrix2 operator+(const Matrix2& matrix) const noexcept;
		Matrix2 operator/(const Matrix2& matrix) const noexcept;
		Vector2 operator/(const Vector2& vector) const noexcept;
		Matrix2 operator*(const Matrix2& matrix) const noexcept;
		Vector2 operator*(const Vector2& vector) const noexcept;
		Matrix2& operator-=(const Matrix2& matrix) noexcept;
		Matrix2& operator+=(const Matrix2& matrix) noexcept;
		Matrix2& operator/=(const Matrix2& matrix) noexcept;
		Matrix2& operator*=(const Matrix2& matrix) noexcept;

		Matrix2 operator-(float value) const noexcept;
		Matrix2 operator+(float value) const noexcept;
		Matrix2 operator/(float value) const noexcept;
		Matrix2 operator*(float value) const noexcept;
		Matrix2& operator-=(float value) noexcept;
		Matrix2& operator+=(float value) noexcept;
		Matrix2& operator/=(float value) noexcept;
		Matrix2& operator*=(float value) noexcept;
		
		static const Matrix2 zero;
		static const Matrix2 minusOne;
		static const Matrix2 one;
		static const Matrix2 identity;
	};
}
