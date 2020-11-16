#pragma once
#include "Injector/Mathematics/Vector2.hpp"

namespace Injector
{
	template<class T = float>
	struct Matrix2 final
	{
		T m00, m01;
		T m10, m11;

		Matrix2() noexcept :
			m00(static_cast<T>(1)),
			m01(static_cast<T>(0)),

			m10(static_cast<T>(0)),
			m11(static_cast<T>(1))
		{
		}
		Matrix2(T value) noexcept :
			m00(value), m01(value),
			m10(value), m11(value)
		{
		}
		Matrix2(
			T _m00, T _m01,
			T _m10, T _m11) noexcept :
			m00(_m00), m01(_m01),
			m10(_m10), m11(_m11)
		{
		}
		Matrix2(
			const Vector2<T>& column0,
			const Vector2<T>& column1) noexcept :
			m00(column0.x), m01(column0.y),
			m10(column1.x), m11(column1.y)
		{
		}

		std::string getString() const noexcept
		{
			auto ss = std::stringstream();
			ss <<
			   m00 << " " << m01 << "; " <<
			   m10 << " " << m11;
			return ss.str();
		}
		T getDeterminant() const noexcept
		{
			return
				m00 * m11 -
				m10 * m01;
		}
		Matrix2<T> getTransposed() const noexcept
		{
			return Matrix2<T>(
				m00, m10,
				m01, m11);
		}
		Matrix2<T>getInverted() const noexcept
		{
			auto determinant = static_cast<T>(1) / getDeterminant();

			return Matrix2<T>(
				m11 * determinant, -m01 * determinant,
				-m10 * determinant, m00 * determinant);
		}

		Vector2<T> getRow0() const noexcept
		{
			return Vector2<T>(m00, m10);
		}
		Vector2<T> getRow1() const noexcept
		{
			return Vector2<T>(m01, m11);
		}
		void setRow0(const Vector2<T>& vector) noexcept
		{
			m00 = vector.x;
			m10 = vector.y;
		}
		void setRow1(const Vector2<T>& vector) noexcept
		{
			m01 = vector.x;
			m11 = vector.y;
		}

		Vector2<T> getColumn0() const noexcept
		{
			return Vector2<T>(m00, m01);
		}
		Vector2<T> getColumn1() const noexcept
		{
			return Vector2<T>(m10, m11);
		}
		void setColumn0(const Vector2<T>& vector) noexcept
		{
			m00 = vector.x;
			m01 = vector.y;
		}
		void setColumn1(const Vector2<T>& vector) noexcept
		{
			m10 = vector.x;
			m11 = vector.y;
		}

		bool operator==(const Matrix2<T>& matrix) const noexcept
		{
			return
				getColumn0() == matrix.getColumn0() &&
				getColumn1() == matrix.getColumn1();
		}
		bool operator!=(const Matrix2<T>& matrix) const noexcept
		{
			return
				getColumn0() != matrix.getColumn0() ||
				getColumn1() != matrix.getColumn1();
		}

		Matrix2<T>& operator--() noexcept
		{
			setColumn0(--getColumn0());
			setColumn1(--getColumn1());
			return *this;
		}
		Matrix2<T>& operator++() noexcept
		{
			setColumn0(++getColumn0());
			setColumn1(++getColumn1());
			return *this;
		}
		Matrix2<T> operator--(int) noexcept
		{
			auto result = Matrix2<T>(*this);
			setColumn0(--getColumn0());
			setColumn1(--getColumn1());
			return result;
		}
		Matrix2<T> operator++(int) noexcept
		{
			auto result = Matrix2<T>(*this);
			setColumn0(++getColumn0());
			setColumn1(++getColumn1());
			return result;
		}
		Matrix2<T> operator-() const noexcept
		{
			return Matrix2<T>(
				-getColumn0(),
				-getColumn1());
		}

		Matrix2<T> operator-(
			const Matrix2<T>& matrix) const noexcept
		{
			return Matrix2<T>(
				getColumn0() - matrix.getColumn0(),
				getColumn1() - matrix.getColumn1());
		}
		Matrix2<T> operator+(
			const Matrix2<T>& matrix) const noexcept
		{
			return Matrix2<T>(
				getColumn0() + matrix.getColumn0(),
				getColumn1() + matrix.getColumn1());
		}
		Matrix2<T> operator/(
			const Matrix2<T>& matrix) const noexcept
		{
			return *this * matrix.getInverted();
		}
		Vector2<T> operator/(
			const Vector2<T>& vector) const noexcept
		{
			return getInverted() * vector;
		}
		Matrix2<T> operator*(
			const Matrix2<T>& matrix) const noexcept
		{
			auto a0 = getColumn0();
			auto a1 = getColumn1();

			auto b0 = matrix.getColumn0();
			auto b1 = matrix.getColumn1();

			return Matrix2(
				a0 * b0.x + a1 * b0.y,
				a0 * b1.x + a1 * b1.y);
		}
		Vector2<T> operator*(
			const Vector2<T>& vector) const noexcept
		{
			return
				getColumn0() * Vector2<T>(vector.x) +
				getColumn1() * Vector2<T>(vector.y);
		}

		Matrix2<T>& operator-=(
			const Matrix2<T>& matrix) noexcept
		{
			setColumn0(getColumn0() - matrix.getColumn0());
			setColumn1(getColumn1() - matrix.getColumn1());
			return *this;
		}
		Matrix2<T>& operator+=(
			const Matrix2<T>& matrix) noexcept
		{
			setColumn0(getColumn0() + matrix.getColumn0());
			setColumn1(getColumn1() + matrix.getColumn1());
			return *this;
		}
		Matrix2<T>& operator/=(
			const Matrix2<T>& matrix) noexcept
		{
			return *this *= matrix.getInverted();
		}
		Matrix2<T>& operator*=(
			const Matrix2<T>& matrix) noexcept
		{
			auto a0 = getColumn0();
			auto a1 = getColumn1();

			auto b0 = matrix.getColumn0();
			auto b1 = matrix.getColumn1();

			setColumn0(a0 * b0.x + a1 * b0.y);
			setColumn1(a0 * b1.x + a1 * b1.y);
			return *this;
		}

		Matrix2<T> operator-(
			T value) const noexcept
		{
			auto vector = Vector2<T>(value);

			return Matrix2<T>(
				getColumn0() - vector,
				getColumn1() - vector);
		}
		Matrix2<T>operator+(
			T value) const noexcept
		{
			auto vector = Vector2<T>(value);

			return Matrix2<T>(
				getColumn0() + vector,
				getColumn1() + vector);
		}
		Matrix2<T>operator/(
			T value) const noexcept
		{
			auto vector = Vector2<T>(value);

			return Matrix2<T>(
				getColumn0() / vector,
				getColumn1() / vector);
		}
		Matrix2<T> operator*(
			T value) const noexcept
		{
			auto vector = Vector2<T>(value);

			return Matrix2<T>(
				getColumn0() * vector,
				getColumn1() * vector);
		}
		Matrix2<T>& operator-=(
			T value) noexcept
		{
			auto vector = Vector2<T>(value);
			setColumn0(getColumn0() - vector);
			setColumn1(getColumn1() - vector);
			return *this;
		}
		Matrix2<T>& operator+=(
			T value) noexcept
		{
			auto vector = Vector2<T>(value);
			setColumn0(getColumn0() + vector);
			setColumn1(getColumn1() + vector);
			return *this;
		}
		Matrix2<T>& operator/=(
			T value) noexcept
		{
			auto vector = Vector2<T>(value);
			setColumn0(getColumn0() / vector);
			setColumn1(getColumn1() / vector);
			return *this;
		}
		Matrix2<T>& operator*=(
			T value) noexcept
		{
			auto vector = Vector2<T>(value);
			setColumn0(getColumn0() * vector);
			setColumn1(getColumn1() * vector);
			return *this;
		}

		struct Less
		{
			bool operator()(
				const Matrix2<T>& a,
				const Matrix2<T>& b) const noexcept
			{
				return
					std::tie(
						a.m00, a.m01,
						a.m10, a.m11) <
					std::tie(
						b.m00, b.m01,
						b.m10, b.m11);
			}
		};
	};

	using FloatMatrix2 = Matrix2<float>;
	using DoubleMatrix2 = Matrix2<double>;
	using CharMatrix2 = Matrix2<char>;
	using ByteMatrix2 = Matrix2<uint8_t>;
	using SbyteMatrix2 = Matrix2<int8_t>;
	using ShortMatrix2 = Matrix2<int16_t>;
	using UshortMatrix2 = Matrix2<uint16_t>;
	using IntMatrix2 = Matrix2<int32_t>;
	using UintMatrix2 = Matrix2<uint32_t>;
	using LongMatrix2 = Matrix2<int64_t>;
	using UlongMatrix2 = Matrix2<uint64_t>;
}
