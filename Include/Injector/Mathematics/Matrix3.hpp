#pragma once
#include "Injector/Mathematics/Matrix2.hpp"
#include "Injector/Mathematics/Vector3.hpp"

namespace Injector
{
	template<class T = float>
	struct Matrix3 final
	{
		T m00, m01, m02;
		T m10, m11, m12;
		T m20, m21, m22;

		Matrix3() noexcept :
			m00(static_cast<T>(1)), 
			m01(static_cast<T>(0)), 
			m02(static_cast<T>(0)),
			
			m10(static_cast<T>(0)),
			m11(static_cast<T>(1)), 
			m12(static_cast<T>(0)),
			
			m20(static_cast<T>(0)), 
			m21(static_cast<T>(0)), 
			m22(static_cast<T>(1))
		{
		}
		Matrix3(T value) noexcept :
			m00(value), m01(value), m02(value),
			m10(value), m11(value), m12(value),
			m20(value), m21(value), m22(value)
		{
		}
		Matrix3(
			T _m00, T _m01, T _m02,
			T _m10, T _m11, T _m12,
			T _m20, T _m21, T _m22) noexcept :
			m00(_m00), m01(_m01), m02(_m02),
			m10(_m10), m11(_m11), m12(_m12),
			m20(_m20), m21(_m21), m22(_m22)
		{
		}
		Matrix3(
			const Vector3<T>& column0,
			const Vector3<T>& column1,
			const Vector3<T>& column2) noexcept :
			m00(column0.x), m01(column0.y), m02(column0.z),
			m10(column1.x), m11(column1.y), m12(column1.z),
			m20(column2.x), m21(column2.y), m22(column2.z)
		{
		}

		std::string getString() const noexcept
		{
			auto ss = std::stringstream();
			ss <<
			   m00 << " " << m01 << " " << m02 << "; " <<
			   m10 << " " << m11 << " " << m12 << "; " <<
			   m20 << " " << m21 << " " << m22;
			return ss.str();
		}
		T getDeterminant() const noexcept
		{
			return
				m00 * (m11 * m22 - m21 * m12) -
				m10 * (m01 * m22 - m21 * m02) +
				m20 * (m01 * m12 - m11 * m02);
		}
		Matrix3<T> getTransposed() const noexcept
		{
			return Matrix3(
				m00, m10, m20,
				m01, m11, m21,
				m02, m12, m22);
		}
		Matrix3<T> getInverted() const noexcept
		{
			auto determinant = static_cast<T>(1) / getDeterminant();

			return Matrix3(
				(m11 * m22 - m21 * m12) * determinant,
				-(m01 * m22 - m21 * m02) * determinant,
				(m01 * m12 - m11 * m02) * determinant,
				-(m10 * m22 - m20 * m12) * determinant,
				(m00 * m22 - m20 * m02) * determinant,
				-(m00 * m12 - m10 * m02) * determinant,
				(m10 * m21 - m20 * m11) * determinant,
				-(m00 * m21 - m20 * m01) * determinant,
				(m00 * m11 - m10 * m01) * determinant);
		}

		Vector3<T> getRow0() const noexcept
		{
			return Vector3<T>(m00, m10, m20);
		}
		Vector3<T> getRow1() const noexcept
		{
			return Vector3<T>(m01, m11, m21);
		}
		Vector3<T> getRow2() const noexcept
		{
			return Vector3<T>(m02, m12, m22);
		}
		void setRow0(const Vector3<T>& vector) noexcept
		{
			m00 = vector.x;
			m10 = vector.y;
			m20 = vector.z;
		}
		void setRow1(const Vector3<T>& vector) noexcept
		{
			m01 = vector.x;
			m11 = vector.y;
			m21 = vector.z;
		}
		void setRow2(const Vector3<T>& vector) noexcept
		{
			m02 = vector.x;
			m12 = vector.y;
			m22 = vector.z;
		}

		Vector3<T> getColumn0() const noexcept
		{
			return Vector3<T>(m00, m01, m02);
		}
		Vector3<T> getColumn1() const noexcept
		{
			return Vector3<T>(m10, m11, m12);
		}
		Vector3<T> getColumn2() const noexcept
		{
			return Vector3<T>(m20, m21, m22);
		}
		void setColumn0(const Vector3<T>& vector) noexcept
		{
			m00 = vector.x;
			m01 = vector.y;
			m02 = vector.z;
		}
		void setColumn1(const Vector3<T>& vector) noexcept
		{
			m10 = vector.x;
			m11 = vector.y;
			m12 = vector.z;
		}
		void setColumn2(const Vector3<T>& vector) noexcept
		{
			m20 = vector.x;
			m22 = vector.y;
			m22 = vector.z;
		}

		bool operator==(const Matrix3<T>& matrix) const noexcept
		{
			return
				getColumn0() == matrix.getColumn0() &&
				getColumn1() == matrix.getColumn1() &&
				getColumn2() == matrix.getColumn2();
		}
		bool operator!=(const Matrix3<T>& matrix) const noexcept
		{
			return
				getColumn0() != matrix.getColumn0() ||
				getColumn1() != matrix.getColumn1() ||
				getColumn2() != matrix.getColumn2();
		}

		Matrix3<T>& operator--() noexcept
		{
			setColumn0(--getColumn0());
			setColumn1(--getColumn1());
			setColumn2(--getColumn2());
			return *this;
		}
		Matrix3<T>& operator++() noexcept
		{
			setColumn0(++getColumn0());
			setColumn1(++getColumn1());
			setColumn2(++getColumn2());
			return *this;
		}
		Matrix3<T> operator--(int) noexcept
		{
			auto result = Matrix3<T>(*this);
			setColumn0(--getColumn0());
			setColumn1(--getColumn1());
			setColumn2(--getColumn2());
			return result;
		}
		Matrix3<T> operator++(int) noexcept
		{
			auto result = Matrix3<T>(*this);
			setColumn0(++getColumn0());
			setColumn1(++getColumn1());
			setColumn2(++getColumn2());
			return result;
		}
		Matrix3<T> operator-() const noexcept
		{
			return Matrix3<T>(
				-getColumn0(),
				-getColumn1(),
				-getColumn2());
		}

		Matrix3<T> operator-(
			const Matrix3<T>& matrix) const noexcept
		{
			return Matrix3<T>(
				getColumn0() - matrix.getColumn0(),
				getColumn1() - matrix.getColumn1(),
				getColumn2() - matrix.getColumn2());
		}
		Matrix3<T> operator+(
			const Matrix3<T>& matrix) const noexcept
		{
			return Matrix3<T>(
				getColumn0() + matrix.getColumn0(),
				getColumn1() + matrix.getColumn1(),
				getColumn2() + matrix.getColumn2());
		}
		Matrix3<T> operator/(
			const Matrix3<T>& matrix) const noexcept
		{
			return *this * matrix.getInverted();
		}
		Vector3<T> operator/(
			const Vector3<T>& vector) const noexcept
		{
			return getInverted() * vector;
		}
		Matrix3<T> operator*(
			const Matrix3<T>& matrix) const noexcept
		{
			auto a0 = getColumn0();
			auto a1 = getColumn1();
			auto a2 = getColumn2();

			auto b0 = matrix.getColumn0();
			auto b1 = matrix.getColumn1();
			auto b2 = matrix.getColumn2();

			return Matrix3<T>(
				a0 * b0.x + a1 * b0.y + a2 * b0.z,
				a0 * b1.x + a1 * b1.y + a2 * b1.z,
				a0 * b2.x + a1 * b2.y + a2 * b2.z);
		}
		Vector3<T> operator*(
			const Vector3<T>& vector) const noexcept
		{
			return
				getColumn0() * Vector3<T>(vector.x) +
				getColumn1() * Vector3<T>(vector.y) +
				getColumn2() * Vector3<T>(vector.z);
		}

		Matrix3<T>& operator-=(
			const Matrix3<T>& matrix) noexcept
		{
			setColumn0(getColumn0() - matrix.getColumn0());
			setColumn1(getColumn1() - matrix.getColumn1());
			setColumn2(getColumn2() - matrix.getColumn2());
			return *this;
		}
		Matrix3<T>& operator+=(
			const Matrix3<T>& matrix) noexcept
		{
			setColumn0(getColumn0() + matrix.getColumn0());
			setColumn1(getColumn1() + matrix.getColumn1());
			setColumn2(getColumn2() + matrix.getColumn2());
			return *this;
		}
		Matrix3<T>& operator/=(
			const Matrix3<T>& matrix) noexcept
		{
			return *this *= matrix.getInverted();
		}
		Matrix3<T>& operator*=(
			const Matrix3<T>& matrix) noexcept
		{
			auto a0 = getColumn0();
			auto a1 = getColumn1();
			auto a2 = getColumn2();

			auto b0 = matrix.getColumn0();
			auto b1 = matrix.getColumn1();
			auto b2 = matrix.getColumn2();

			setColumn0(a0 * b0.x + a1 * b0.y + a2 * b0.z);
			setColumn1(a0 * b1.x + a1 * b1.y + a2 * b1.z);
			setColumn2(a0 * b2.x + a1 * b2.y + a2 * b2.z);
			return *this;
		}

		Matrix3<T> operator-(
			T value) const noexcept
		{
			auto vector = Vector3<T>(value);

			return Matrix3<T>(
				getColumn0() - vector,
				getColumn1() - vector,
				getColumn2() - vector);
		}
		Matrix3<T> operator+(
			T value) const noexcept
		{
			auto vector = Vector3<T>(value);

			return Matrix3<T>(
				getColumn0() + vector,
				getColumn1() + vector,
				getColumn2() + vector);
		}
		Matrix3<T> operator/(
			T value) const noexcept
		{
			auto vector = Vector3<T>(value);

			return Matrix3<T>(
				getColumn0() / vector,
				getColumn1() / vector,
				getColumn2() / vector);
		}
		Matrix3<T> operator*(
			T value) const noexcept
		{
			auto vector = Vector3<T>(value);

			return Matrix3<T>(
				getColumn0() * vector,
				getColumn1() * vector,
				getColumn2() * vector);
		}
		Matrix3<T>& operator-=(
			T value) noexcept
		{
			auto vector = Vector3<T>(value);
			setColumn0(getColumn0() - vector);
			setColumn1(getColumn1() - vector);
			setColumn2(getColumn2() - vector);
			return *this;
		}
		Matrix3<T>& operator+=(
			T value) noexcept
		{
			auto vector = Vector3<T>(value);
			setColumn0(getColumn0() + vector);
			setColumn1(getColumn1() + vector);
			setColumn2(getColumn2() + vector);
			return *this;
		}
		Matrix3<T>& operator/=(
			T value) noexcept
		{
			auto vector = Vector3<T>(value);
			setColumn0(getColumn0() / vector);
			setColumn1(getColumn1() / vector);
			setColumn2(getColumn2() / vector);
			return *this;
		}
		Matrix3<T>& operator*=(
			T value) noexcept
		{
			auto vector = Vector3<T>(value);
			setColumn0(getColumn0() * vector);
			setColumn1(getColumn1() * vector);
			setColumn2(getColumn2() * vector);
			return *this;
		}

		struct Less
		{
			bool operator()(
				const Matrix3& a,
				const Matrix3& b) const noexcept
			{
				return
					std::tie(
						a.m00, a.m01, a.m02,
						a.m10, a.m11, a.m12,
						a.m20, a.m21, a.m22) <
					std::tie(
						b.m00, b.m01, b.m02,
						b.m10, b.m11, b.m12,
						b.m20, b.m21, b.m22);
			}
		};
	};

	using FloatMatrix3 = Matrix3<float>;
	using DoubleMatrix3 = Matrix3<double>;
	using CharMatrix3 = Matrix3<char>;
	using ByteMatrix3 = Matrix3<uint8_t>;
	using SbyteMatrix3 = Matrix3<int8_t>;
	using ShortMatrix3 = Matrix3<int16_t>;
	using UshortMatrix3 = Matrix3<uint16_t>;
	using IntMatrix3 = Matrix3<int32_t>;
	using UintMatrix3 = Matrix3<uint32_t>;
	using LongMatrix3 = Matrix3<int64_t>;
	using UlongMatrix3 = Matrix3<uint64_t>;
	using SizeMatrix3 = Matrix3<size_t>;
}


