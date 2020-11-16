#pragma once
#include "Injector/Mathematics/Matrix3.hpp"
#include "Injector/Mathematics/Vector4.hpp"

namespace Injector
{
	template<class T = float>
	struct Matrix4 final
	{
		T m00, m01, m02, m03;
		T m10, m11, m12, m13;
		T m20, m21, m22, m23;
		T m30, m31, m32, m33;

		Matrix4() noexcept :
			m00(static_cast<T>(1)),
			m01(static_cast<T>(0)),
			m02(static_cast<T>(0)),
			m03(static_cast<T>(0)),

			m10(static_cast<T>(0)),
			m11(static_cast<T>(1)),
			m12(static_cast<T>(0)),
			m13(static_cast<T>(0)),

			m20(static_cast<T>(0)),
			m21(static_cast<T>(0)),
			m22(static_cast<T>(1)),
			m23(static_cast<T>(0)),

			m30(static_cast<T>(0)),
			m31(static_cast<T>(0)),
			m32(static_cast<T>(0)),
			m33(static_cast<T>(1))
		{
		}
		explicit Matrix4(
			T value) noexcept :
			m00(value), m01(value), m02(value), m03(value),
			m10(value), m11(value), m12(value), m13(value),
			m20(value), m21(value), m22(value), m23(value),
			m30(value), m31(value), m32(value), m33(value)
		{
		}
		Matrix4(
			T _m00, T _m01, T _m02, T _m03,
			T _m10, T _m11, T _m12, T _m13,
			T _m20, T _m21, T _m22, T _m23,
			T _m30, T _m31, T _m32, T _m33) noexcept :
			m00(_m00), m01(_m01), m02(_m02), m03(_m03),
			m10(_m10), m11(_m11), m12(_m12), m13(_m13),
			m20(_m20), m21(_m21), m22(_m22), m23(_m23),
			m30(_m30), m31(_m31), m32(_m32), m33(_m33)
		{
		}
		Matrix4(
			const Vector4<T>& column0,
			const Vector4<T>& column1,
			const Vector4<T>& column2,
			const Vector4<T>& column3) noexcept :
			m00(column0.x), m01(column0.y), m02(column0.z), m03(column0.w),
			m10(column1.x), m11(column1.y), m12(column1.z), m13(column1.w),
			m20(column2.x), m21(column2.y), m22(column2.z), m23(column2.w),
			m30(column3.x), m31(column3.y), m32(column3.z), m33(column3.w)
		{
		}

		std::string getString() const noexcept
		{
			auto ss = std::stringstream();
			ss <<
			   m00 << " " << m01 << " " << m02 << " " << m03 << "; " <<
			   m10 << " " << m11 << " " << m12 << " " << m13 << "; " <<
			   m20 << " " << m21 << " " << m22 << " " << m23 << "; " <<
			   m30 << " " << m31 << " " << m32 << " " << m33;
			return ss.str();
		}
		T getDeterminant() const noexcept
		{
			auto f0 = m22 * m33 - m32 * m23;
			auto f1 = m21 * m33 - m31 * m23;
			auto f2 = m21 * m32 - m31 * m22;
			auto f3 = m20 * m33 - m30 * m23;
			auto f4 = m20 * m32 - m30 * m22;
			auto f5 = m20 * m31 - m30 * m21;

			auto c0 = m11 * f0 - m12 * f1 + m13 * f2;
			auto c1 = -(m10 * f0 - m12 * f3 + m13 * f4);
			auto c2 = m10 * f1 - m11 * f3 + m13 * f5;
			auto c3 = -(m10 * f2 - m11 * f4 + m12 * f5);

			return
				m00 * c0 + m01 * c1 +
				m02 * c2 + m03 * c3;
		}
		Matrix4<T> getTransposed() const noexcept
		{
			return Matrix4(
				m00, m10, m20, m30,
				m01, m11, m21, m31,
				m02, m12, m22, m32,
				m03, m13, m23, m33);
		}
		Matrix4<T> getInverted() const noexcept
		{
			auto c00 = m22 * m33 - m32 * m23;
			auto c02 = m12 * m33 - m32 * m13;
			auto c03 = m12 * m23 - m22 * m13;

			auto c04 = m21 * m33 - m31 * m23;
			auto c06 = m11 * m33 - m31 * m13;
			auto c07 = m11 * m23 - m21 * m13;

			auto c08 = m21 * m32 - m31 * m22;
			auto c10 = m11 * m32 - m31 * m12;
			auto c11 = m11 * m22 - m21 * m12;

			auto c12 = m20 * m33 - m30 * m23;
			auto c14 = m10 * m33 - m30 * m13;
			auto c15 = m10 * m23 - m20 * m13;

			auto c16 = m20 * m32 - m30 * m22;
			auto c18 = m10 * m32 - m30 * m12;
			auto c19 = m10 * m22 - m20 * m12;

			auto c20 = m20 * m31 - m30 * m21;
			auto c22 = m10 * m31 - m30 * m11;
			auto c23 = m10 * m21 - m20 * m11;

			auto f0 = Vector4<T>(c00, c00, c02, c03);
			auto f1 = Vector4<T>(c04, c04, c06, c07);
			auto f2 = Vector4<T>(c08, c08, c10, c11);
			auto f3 = Vector4<T>(c12, c12, c14, c15);
			auto f4 = Vector4<T>(c16, c16, c18, c19);
			auto f5 = Vector4<T>(c20, c20, c22, c23);

			auto v0 = Vector4<T>(m10, m00, m00, m00);
			auto v1 = Vector4<T>(m11, m01, m01, m01);
			auto v2 = Vector4<T>(m12, m02, m02, m02);
			auto v3 = Vector4<T>(m13, m03, m03, m03);

			auto i0 = Vector4<T>(v1 * f0 - v2 * f1 + v3 * f2);
			auto i1 = Vector4<T>(v0 * f0 - v2 * f3 + v3 * f4);
			auto i2 = Vector4<T>(v0 * f1 - v1 * f3 + v3 * f5);
			auto i3 = Vector4<T>(v0 * f2 - v1 * f4 + v2 * f5);

			auto a = Vector4<T>(
				static_cast<T>(1),
				static_cast<T>(-1),
				static_cast<T>(1),
				static_cast<T>(-1));
			auto b = Vector4<T>(
				static_cast<T>(-1),
				static_cast<T>(1),
				static_cast<T>(-1),
				static_cast<T>(1));
			auto inverse = Matrix4<T>(
				i0 * a,
				i1 * b,
				i2 * a,
				i3 * b);

			auto dot0 = getColumn0() * inverse.getRow0();
			auto dot1 = (dot0.x + dot0.y) + (dot0.z + dot0.w);

			auto determinant = static_cast<T>(1) / dot1;

			return inverse * determinant;
		}
		Matrix4<T> getScaled(const Vector3<T>& vector) const noexcept
		{
			auto matrix = Matrix4<T>();
			matrix.setColumn0(getColumn0() * vector.x);
			matrix.setColumn1(getColumn1() * vector.y);
			matrix.setColumn2(getColumn2() * vector.z);
			matrix.setColumn3(getColumn3());
			return matrix;
		}
		Matrix4<T> getTranslated(const Vector3<T>& vector) const noexcept
		{
			auto result = Matrix4<T>(*this);
			result.setColumn3(
				getColumn0() * vector.x +
				getColumn1() * vector.y +
				getColumn2() * vector.z +
				getColumn3());
			return result;
		}
		Matrix4<T> getRotated(
			const Vector3<T>& vector,
			T angle) const noexcept
		{
			auto c = static_cast<T>(cos(angle));
			auto s = static_cast<T>(sin(angle));

			auto axis = vector.getNormalized();
			auto temp = axis * (static_cast<T>(1) - c);

			auto r00 = c + temp.x * axis.x;
			auto r01 = temp.x * axis.y + s * axis.z;
			auto r02 = temp.x * axis.z - s * axis.y;

			auto r10 = temp.y * axis.x - s * axis.z;
			auto r11 = c + temp.y * axis.y;
			auto r12 = temp.y * axis.z + s * axis.x;

			auto r20 = temp.z * axis.x + s * axis.y;
			auto r21 = temp.z * axis.y - s * axis.x;
			auto r22 = c + temp.z * axis.z;

			auto c0 = getColumn0();
			auto c1 = getColumn1();
			auto c2 = getColumn2();

			return Matrix4<T>(
				c0 * r00 + c1 * r01 + c2 * r02,
				c0 * r10 + c1 * r11 + c2 * r12,
				c0 * r20 + c1 * r21 + c2 * r22,
				getColumn3());
		}
		Matrix4<T> getLookedAt(
			const Vector3<T>& eye,
			const Vector3<T>& center,
			const Vector3<T>& up) const noexcept
		{
			auto f = (center - eye).getNormalized();
			auto s = up.getCrossProduct(f).getNormalized();
			auto u = f.getCrossProduct(s);

			return Matrix4<T>(
				s.x, s.y, s.z, static_cast<T>(0),
				u.x, u.y, u.z, static_cast<T>(0),
				f.x, f.y, f.z, static_cast<T>(0),
				-s.getDotProduct(eye),
				-u.getDotProduct(eye),
				-f.getDotProduct(eye),
				static_cast<T>(1));
		}

		Vector4<T> getRow0() const noexcept
		{
			return Vector4<T>(m00, m10, m20, m30);
		}
		Vector4<T> getRow1() const noexcept
		{
			return Vector4<T>(m01, m11, m21, m31);
		}
		Vector4<T> getRow2() const noexcept
		{
			return Vector4<T>(m02, m12, m22, m31);
		}
		Vector4<T> getRow3() const noexcept
		{
			return Vector4<T>(m03, m13, m23, m33);
		}
		void setRow0(const Vector4<T>& vector) noexcept
		{
			m00 = vector.x;
			m10 = vector.y;
			m20 = vector.z;
			m30 = vector.w;
		}
		void setRow1(const Vector4<T>& vector) noexcept
		{
			m01 = vector.x;
			m11 = vector.y;
			m21 = vector.z;
			m31 = vector.w;
		}
		void setRow2(const Vector4<T>& vector) noexcept
		{
			m02 = vector.x;
			m12 = vector.y;
			m22 = vector.z;
			m32 = vector.w;
		}
		void setRow3(const Vector4<T>& vector) noexcept
		{
			m03 = vector.x;
			m13 = vector.y;
			m23 = vector.z;
			m33 = vector.w;
		}

		Vector4<T> getColumn0() const noexcept
		{
			return Vector4(m00, m01, m02, m03);
		}
		Vector4<T> getColumn1() const noexcept
		{
			return Vector4(m10, m11, m12, m13);
		}
		Vector4<T> getColumn2() const noexcept
		{
			return Vector4(m20, m21, m22, m23);
		}
		Vector4<T> getColumn3() const noexcept
		{
			return Vector4(m30, m31, m32, m33);
		}
		void setColumn0(
			const Vector4<T>& vector) noexcept
		{
			m00 = vector.x;
			m01 = vector.y;
			m02 = vector.z;
			m03 = vector.w;
		}
		void setColumn1(
			const Vector4<T>& vector) noexcept
		{
			m10 = vector.x;
			m11 = vector.y;
			m12 = vector.z;
			m13 = vector.w;
		}
		void setColumn2(
			const Vector4<T>& vector) noexcept
		{
			m20 = vector.x;
			m21 = vector.y;
			m22 = vector.z;
			m23 = vector.w;
		}
		void setColumn3(
			const Vector4<T>& vector) noexcept
		{
			m30 = vector.x;
			m31 = vector.y;
			m32 = vector.z;
			m33 = vector.w;
		}

		bool operator==(
			const Matrix4<T>& matrix) const noexcept
		{
			return
				getColumn0() == matrix.getColumn0() &&
				getColumn1() == matrix.getColumn1() &&
				getColumn2() == matrix.getColumn2() &&
				getColumn3() == matrix.getColumn3();
		}
		bool operator!=(
			const Matrix4<T>& matrix) const noexcept
		{
			return
				getColumn0() != matrix.getColumn0() ||
				getColumn1() != matrix.getColumn1() ||
				getColumn2() != matrix.getColumn2() ||
				getColumn3() != matrix.getColumn3();
		}

		Matrix4<T>& operator--() noexcept
		{
			setColumn0(--getColumn0());
			setColumn1(--getColumn1());
			setColumn2(--getColumn2());
			setColumn3(--getColumn3());
			return *this;
		}
		Matrix4<T>& operator++() noexcept
		{
			setColumn0(++getColumn0());
			setColumn1(++getColumn1());
			setColumn2(++getColumn2());
			setColumn3(++getColumn3());
			return *this;
		}
		Matrix4<T> operator--(int) noexcept
		{
			auto result = Matrix4<T>(*this);
			setColumn0(--getColumn0());
			setColumn1(--getColumn1());
			setColumn2(--getColumn2());
			setColumn3(--getColumn3());
			return result;
		}
		Matrix4<T> operator++(int) noexcept
		{
			auto result = Matrix4<T>(*this);
			setColumn0(++getColumn0());
			setColumn1(++getColumn1());
			setColumn2(++getColumn2());
			setColumn3(++getColumn3());
			return result;
		}
		Matrix4<T> operator-() const noexcept
		{
			return Matrix4<T>(
				-getColumn0(),
				-getColumn1(),
				-getColumn2(),
				-getColumn3());
		}

		Matrix4<T> operator-(
			const Matrix4<T>& matrix) const noexcept
		{
			return Matrix4<T>(
				getColumn0() - matrix.getColumn0(),
				getColumn1() - matrix.getColumn1(),
				getColumn2() - matrix.getColumn2(),
				getColumn3() - matrix.getColumn3());
		}
		Matrix4<T> operator+(
			const Matrix4<T>& matrix) const noexcept
		{
			return Matrix4<T>(
				getColumn0() + matrix.getColumn0(),
				getColumn1() + matrix.getColumn1(),
				getColumn2() + matrix.getColumn2(),
				getColumn3() + matrix.getColumn3());
		}
		Matrix4<T> operator/(
			const Matrix4<T>& matrix) const noexcept
		{
			return *this * matrix.getInverted();
		}
		Vector4<T> operator/(
			const Vector4<T>& vector) const noexcept
		{
			return getInverted() * vector;
		}
		Matrix4<T> operator*(
			const Matrix4<T>& matrix) const noexcept
		{
			auto a0 = getColumn0();
			auto a1 = getColumn1();
			auto a2 = getColumn2();
			auto a3 = getColumn3();

			auto b0 = matrix.getColumn0();
			auto b1 = matrix.getColumn1();
			auto b2 = matrix.getColumn2();
			auto b3 = matrix.getColumn3();

			return Matrix4<T>(
				a0 * b0.x + a1 * b0.y + a2 * b0.z + a3 * b0.w,
				a0 * b1.x + a1 * b1.y + a2 * b1.z + a3 * b1.w,
				a0 * b2.x + a1 * b2.y + a2 * b2.z + a3 * b2.w,
				a0 * b3.x + a1 * b3.y + a2 * b3.z + a3 * b3.w);
		}
		Vector4<T> operator*(
			const Vector4<T>& vector) const noexcept
		{
			return
				getColumn0() * Vector4<T>(vector.x) +
				getColumn1() * Vector4<T>(vector.y) +
				getColumn2() * Vector4<T>(vector.z) +
				getColumn3() * Vector4<T>(vector.w);
		}

		Matrix4<T>& operator-=(
			const Matrix4<T>& matrix) noexcept
		{
			setColumn0(getColumn0() - matrix.getColumn0());
			setColumn1(getColumn1() - matrix.getColumn1());
			setColumn2(getColumn2() - matrix.getColumn2());
			setColumn3(getColumn3() - matrix.getColumn3());
			return *this;
		}
		Matrix4<T>& operator+=(
			const Matrix4<T>& matrix) noexcept
		{
			setColumn0(getColumn0() + matrix.getColumn0());
			setColumn1(getColumn1() + matrix.getColumn1());
			setColumn2(getColumn2() + matrix.getColumn2());
			setColumn3(getColumn3() + matrix.getColumn3());
			return *this;
		}
		Matrix4<T>& operator/=(
			const Matrix4<T>& matrix) noexcept
		{
			return *this *= matrix.getInverted();
		}
		Matrix4<T>& operator*=(
			const Matrix4<T>& matrix) noexcept
		{
			auto a0 = getColumn0();
			auto a1 = getColumn1();
			auto a2 = getColumn2();
			auto a3 = getColumn3();

			auto b0 = matrix.getColumn0();
			auto b1 = matrix.getColumn1();
			auto b2 = matrix.getColumn2();
			auto b3 = matrix.getColumn3();

			setColumn0(a0 * b0.x + a1 * b0.y + a2 * b0.z + a3 * b0.w);
			setColumn1(a0 * b1.x + a1 * b1.y + a2 * b1.z + a3 * b1.w);
			setColumn2(a0 * b2.x + a1 * b2.y + a2 * b2.z + a3 * b2.w);
			setColumn3(a0 * b3.x + a1 * b3.y + a2 * b3.z + a3 * b3.w);
			return *this;
		}

		Matrix4<T> operator-(
			T value) const noexcept
		{
			auto vector = Vector4<T>(value);

			return Matrix4<T>(
				getColumn0() - vector,
				getColumn1() - vector,
				getColumn2() - vector,
				getColumn3() - vector);
		}
		Matrix4<T> operator+(
			T value) const noexcept
		{
			auto vector = Vector4<T>(value);

			return Matrix4<T>(
				getColumn0() + vector,
				getColumn1() + vector,
				getColumn2() + vector,
				getColumn3() + vector);
		}
		Matrix4<T> operator/(
			T value) const noexcept
		{
			auto vector = Vector4<T>(value);

			return Matrix4<T>(
				getColumn0() / vector,
				getColumn1() / vector,
				getColumn2() / vector,
				getColumn3() / vector);
		}
		Matrix4<T> operator*(
			T value) const noexcept
		{
			auto vector = Vector4<T>(value);

			return Matrix4<T>(
				getColumn0() * vector,
				getColumn1() * vector,
				getColumn2() * vector,
				getColumn3() * vector);
		}
		Matrix4<T>& operator-=(
			T value) noexcept
		{
			auto vector = Vector4<T>(value);
			setColumn0(getColumn0() - vector);
			setColumn1(getColumn1() - vector);
			setColumn2(getColumn2() - vector);
			setColumn3(getColumn3() - vector);
			return *this;
		}
		Matrix4<T>& operator+=(
			T value) noexcept
		{
			auto vector = Vector4<T>(value);
			setColumn0(getColumn0() + vector);
			setColumn1(getColumn1() + vector);
			setColumn2(getColumn2() + vector);
			setColumn3(getColumn3() + vector);
			return *this;
		}
		Matrix4<T>& operator/=(
			T value) noexcept
		{
			auto vector = Vector4<T>(value);
			setColumn0(getColumn0() / vector);
			setColumn1(getColumn1() / vector);
			setColumn2(getColumn2() / vector);
			setColumn3(getColumn3() / vector);
			return *this;
		}
		Matrix4<T>& operator*=(
			T value) noexcept
		{
			auto vector = Vector4<T>(value);
			setColumn0(getColumn0() * vector);
			setColumn1(getColumn1() * vector);
			setColumn2(getColumn2() * vector);
			setColumn3(getColumn3() * vector);
			return *this;
		}

		struct Less
		{
			bool operator()(
				const Matrix4<T>& a,
				const Matrix4<T>& b) const noexcept
			{
				return
					std::tie(
						a.m00, a.m01, a.m02, a.m03,
						a.m10, a.m11, a.m12, a.m13,
						a.m20, a.m21, a.m22, a.m23,
						a.m30, a.m31, a.m32, a.m33) <
					std::tie(
						b.m00, b.m01, b.m02, b.m03,
						b.m10, b.m11, b.m12, b.m13,
						b.m20, b.m21, b.m22, b.m23,
						b.m30, b.m31, b.m32, b.m33);
			}
		};
	};

	template<class T = float>
	static Matrix4<T> vkCreatePerspectiveMatrix(
		float fieldOfView,
		float aspectRatio,
		float nearClipPlane,
		float farClipPlane) noexcept
	{
		auto tanHalfFov =
			tan(fieldOfView / static_cast<T>(2));

		return Matrix4<T>(
			static_cast<T>(1) / (aspectRatio * tanHalfFov),
			static_cast<T>(0),
			static_cast<T>(0),
			static_cast<T>(0),

			static_cast<T>(0),
			static_cast<T>(-1) / tanHalfFov,
			static_cast<T>(0),
			static_cast<T>(0),

			static_cast<T>(0),
			static_cast<T>(0),
			farClipPlane / (farClipPlane - nearClipPlane),
			static_cast<T>(1),

			static_cast<T>(0),
			static_cast<T>(0),
			-(farClipPlane * nearClipPlane) / (farClipPlane - nearClipPlane),
			static_cast<T>(0));
	}
	template<class T = float>
	static Matrix4<T> glCreatePerspectiveMatrix(
		float fieldOfView,
		float aspectRatio,
		float nearClipPlane,
		float farClipPlane) noexcept
	{
		auto tanHalfFov =
			tan(fieldOfView / static_cast<T>(2));

		return Matrix4<T>(
			static_cast<T>(1) / (aspectRatio * tanHalfFov),
			static_cast<T>(0),
			static_cast<T>(0),
			static_cast<T>(0),

			static_cast<T>(0),
			static_cast<T>(1) / tanHalfFov,
			static_cast<T>(0),
			static_cast<T>(0),

			static_cast<T>(0),
			static_cast<T>(0),
			(farClipPlane + nearClipPlane) / (farClipPlane - nearClipPlane),
			static_cast<T>(1),

			static_cast<T>(0),
			static_cast<T>(0),
			-(static_cast<T>(2) * farClipPlane * nearClipPlane) / (farClipPlane - nearClipPlane),
			static_cast<T>(0));
	}
	template<class T = float>
	static Matrix4<T> vkCreateOrthographicMatrix(
		float left,
		float right,
		float bottom,
		float top,
		float nearClipPlane,
		float farClipPlane) noexcept
	{
		return Matrix4<T>(
			static_cast<T>(2) / (right - left),
			static_cast<T>(0),
			static_cast<T>(0),
			static_cast<T>(0),

			static_cast<T>(0),
			static_cast<T>(-2) / (top - bottom),
			static_cast<T>(0),
			static_cast<T>(0),

			static_cast<T>(0),
			static_cast<T>(0),
			static_cast<T>(1) / (farClipPlane - nearClipPlane),
			static_cast<T>(0),

			-(right + left) / (right - left),
			-(top + bottom) / (top - bottom),
			-nearClipPlane / (farClipPlane - nearClipPlane),
			static_cast<T>(1));
	}
	template<class T = float>
	static Matrix4<T> glCreateOrthographicMatrix(
		float left,
		float right,
		float bottom,
		float top,
		float nearClipPlane,
		float farClipPlane) noexcept
	{
		return Matrix4<T>(
			static_cast<T>(2) / (right - left),
			static_cast<T>(0),
			static_cast<T>(0),
			static_cast<T>(0),

			static_cast<T>(0),
			static_cast<T>(2) / (top - bottom),
			static_cast<T>(0),
			static_cast<T>(0),

			static_cast<T>(0),
			static_cast<T>(0),
			static_cast<T>(2) / (farClipPlane - nearClipPlane),
			static_cast<T>(0),

			-(right + left) / (right - left),
			-(top + bottom) / (top - bottom),
			-(farClipPlane + nearClipPlane) / (farClipPlane - nearClipPlane),
			static_cast<T>(1));
	}

	using FloatMatrix4 = Matrix4<float>;
	using DoubleMatrix4 = Matrix4<double>;
	using CharMatrix4 = Matrix4<char>;
	using ByteMatrix4 = Matrix4<uint8_t>;
	using SbyteMatrix4 = Matrix4<int8_t>;
	using ShortMatrix4 = Matrix4<int16_t>;
	using UshortMatrix4 = Matrix4<uint16_t>;
	using IntMatrix4 = Matrix4<int32_t>;
	using UintMatrix4 = Matrix4<uint32_t>;
	using LongMatrix4 = Matrix4<int64_t>;
	using UlongMatrix4 = Matrix4<uint64_t>;
}
