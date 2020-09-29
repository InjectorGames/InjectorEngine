#include "Injector/Mathematics/Matrix4.hpp"

#include <cmath>
#include <sstream>

namespace Injector
{
	Matrix4::Matrix4() :
		m00(0.0f), m01(0.0f), m02(0.0f), m03(0.0f),
		m10(0.0f), m11(0.0f), m12(0.0f), m13(0.0f),
		m20(0.0f), m21(0.0f), m22(0.0f), m23(0.0f),
		m30(0.0f), m31(0.0f), m32(0.0f), m33(0.0f)
	{
	}
	Matrix4::Matrix4(float value) :
		m00(value), m01(value), m02(value), m03(value),
		m10(value), m11(value), m12(value), m13(value),
		m20(value), m21(value), m22(value), m23(value),
		m30(value), m31(value), m32(value), m33(value)
	{
	}
	Matrix4::Matrix4(
		float _m00, float _m01, float _m02, float _m03,
		float _m10, float _m11, float _m12, float _m13,
		float _m20, float _m21, float _m22, float _m23,
		float _m30, float _m31, float _m32, float _m33) :
		m00(_m00), m01(_m01), m02(_m02), m03(_m03),
		m10(_m10), m11(_m11), m12(_m12), m13(_m13),
		m20(_m20), m21(_m21), m22(_m22), m23(_m23),
		m30(_m30), m31(_m31), m32(_m32), m33(_m33)
	{
	}
	Matrix4::Matrix4(
		const Vector4& column0,
		const Vector4& column1,
		const Vector4& column2,
		const Vector4& column3) :
		m00(column0.x), m01(column0.y), m02(column0.z), m03(column0.w),
		m10(column1.x), m11(column1.y), m12(column1.z), m13(column1.w),
		m20(column2.x), m21(column2.y), m22(column2.z), m23(column2.w),
		m30(column3.x), m31(column3.y), m32(column3.z), m33(column3.w)
	{
	}

	std::string Matrix4::getString() const noexcept
	{
		auto stream = std::stringstream();

		stream <<
			m00 << " " << m01 << " " << m02 << " " << m03 << "; " <<
			m10 << " " << m11 << " " << m12 << " " << m13 << "; " <<
			m20 << " " << m21 << " " << m22 << " " << m23 << "; " <<
			m30 << " " << m31 << " " << m32 << " " << m33;

		return stream.str();
	}
	float Matrix4::getDeterminant() const noexcept
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
	Matrix4 Matrix4::getTransposed() const noexcept
	{
		return Matrix4(
			m00, m10, m20, m30,
			m01, m11, m21, m31,
			m02, m12, m22, m32,
			m03, m13, m23, m33);
	}
	Matrix4 Matrix4::getInversed() const noexcept
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

		auto f0 = Vector4(c00, c00, c02, c03);
		auto f1 = Vector4(c04, c04, c06, c07);
		auto f2 = Vector4(c08, c08, c10, c11);
		auto f3 = Vector4(c12, c12, c14, c15);
		auto f4 = Vector4(c16, c16, c18, c19);
		auto f5 = Vector4(c20, c20, c22, c23);

		auto v0 = Vector4(m10, m00, m00, m00);
		auto v1 = Vector4(m11, m01, m01, m01);
		auto v2 = Vector4(m12, m02, m02, m02);
		auto v3 = Vector4(m13, m03, m03, m03);

		auto i0 = Vector4(v1 * f0 - v2 * f1 + v3 * f2);
		auto i1 = Vector4(v0 * f0 - v2 * f3 + v3 * f4);
		auto i2 = Vector4(v0 * f1 - v1 * f3 + v3 * f5);
		auto i3 = Vector4(v0 * f2 - v1 * f4 + v2 * f5);

		auto a = Vector4(1.0f, -1.0f, 1.0f, -1.0f);
		auto b = Vector4(-1.0f, 1.0f, -1.0f, 1.0f);
		auto inverse = Matrix4(i0 * a, i1 * b, i2 * a, i3 * b);

		auto dot0 = getColumn0() * inverse.getRow0();
		auto dot1 = (dot0.x + dot0.y) + (dot0.z + dot0.w);

		auto determinant = 1.0f / dot1;

		return inverse * determinant;
	}
	Matrix4 Matrix4::getScaled(const Vector3& vector) const noexcept
	{
		auto matrix = Matrix4();
		matrix.setColumn0(getColumn0() * vector.x);
		matrix.setColumn1(getColumn1() * vector.y);
		matrix.setColumn2(getColumn2() * vector.z);
		matrix.setColumn3(getColumn3());
		return matrix;
	}
	Matrix4 Matrix4::getTranslated(const Vector3& vector) const noexcept
	{
		auto result = Matrix4(*this);
		result.setColumn3(
			getColumn0() * vector.x +
			getColumn1() * vector.y +
			getColumn2() * vector.z +
			getColumn3());
		return result;
	}
	Matrix4 Matrix4::getRotated(const Vector3& vector, float angle) const noexcept
	{
		float c = cos(angle);
		float s = sin(angle);

		auto axis = vector.getNormalized();
		auto temp = axis * (1.0f - c);

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

		return Matrix4(
			c0 * r00 + c1 * r01 + c2 * r02,
			c0 * r10 + c1 * r11 + c2 * r12,
			c0 * r20 + c1 * r21 + c2 * r22,
			getColumn3());
	}
	Matrix4 Matrix4::getLookedAt(
		const Vector3& eye, const Vector3& center, const Vector3& up) const noexcept
	{
		auto f = (center - eye).getNormalized();
		auto s = up.getCrossProduct(f).getNormalized();
		auto u = f.getCrossProduct(s);

		return Matrix4(
			s.x, s.y, s.z, 0.0f,
			u.x, u.y, u.z, 0.0f,
			f.x, f.y, f.z, 0.0f,
			-s.getDotProduct(eye),
			-u.getDotProduct(eye),
			-f.getDotProduct(eye),
			1.0f);
	}

	Vector4 Matrix4::getRow0() const noexcept
	{
		return Vector4(m00, m10, m20, m30);
	}
	Vector4 Matrix4::getRow1() const noexcept
	{
		return Vector4(m01, m11, m21, m31);
	}
	Vector4 Matrix4::getRow2() const noexcept
	{
		return Vector4(m02, m12, m22, m31);
	}
	Vector4 Matrix4::getRow3() const noexcept
	{
		return Vector4(m03, m13, m23, m33);
	}
	void Matrix4::setRow0(const Vector4& vector) noexcept
	{
		m00 = vector.x;
		m10 = vector.y;
		m20 = vector.z;
		m30 = vector.w;
	}
	void Matrix4::setRow1(const Vector4& vector) noexcept
	{
		m01 = vector.x;
		m11 = vector.y;
		m21 = vector.z;
		m31 = vector.w;
	}
	void Matrix4::setRow2(const Vector4& vector) noexcept
	{
		m02 = vector.x;
		m12 = vector.y;
		m22 = vector.z;
		m32 = vector.w;
	}
	void Matrix4::setRow3(const Vector4& vector) noexcept
	{
		m03 = vector.x;
		m13 = vector.y;
		m23 = vector.z;
		m33 = vector.w;
	}

	Vector4 Matrix4::getColumn0() const noexcept
	{
		return Vector4(m00, m01, m02, m03);
	}
	Vector4 Matrix4::getColumn1() const noexcept
	{
		return Vector4(m10, m11, m12, m13);
	}
	Vector4 Matrix4::getColumn2() const noexcept
	{
		return Vector4(m20, m21, m22, m23);
	}
	Vector4 Matrix4::getColumn3() const noexcept
	{
		return Vector4(m30, m31, m32, m33);
	}
	void Matrix4::setColumn0(const Vector4& vector) noexcept
	{
		m00 = vector.x;
		m01 = vector.y;
		m02 = vector.z;
		m03 = vector.w;
	}
	void Matrix4::setColumn1(const Vector4& vector) noexcept
	{
		m10 = vector.x;
		m11 = vector.y;
		m12 = vector.z;
		m13 = vector.w;
	}
	void Matrix4::setColumn2(const Vector4& vector) noexcept
	{
		m20 = vector.x;
		m21 = vector.y;
		m22 = vector.z;
		m23 = vector.w;
	}
	void Matrix4::setColumn3(const Vector4& vector) noexcept
	{
		m30 = vector.x;
		m31 = vector.y;
		m32 = vector.z;
		m33 = vector.w;
	}

	Matrix2 Matrix4::getMatrix2() const noexcept
	{
		return Matrix2(
			m00, m01,
			m10, m11);
	}
	Matrix3 Matrix4::getMatrix3() const noexcept
	{
		return Matrix3(
			m00, m01, m02,
			m10, m11, m12,
			m20, m21, m22);
	}

	bool Matrix4::operator==(const Matrix4& matrix) const noexcept
	{
		return
			getColumn0() == matrix.getColumn0() &&
			getColumn1() == matrix.getColumn1() &&
			getColumn2() == matrix.getColumn2() &&
			getColumn3() == matrix.getColumn3();
	}
	bool Matrix4::operator!=(const Matrix4& matrix) const noexcept
	{
		return !(*this == matrix);
	}

	Matrix4& Matrix4::operator--() noexcept
	{
		setColumn0(--getColumn0());
		setColumn1(--getColumn1());
		setColumn2(--getColumn2());
		setColumn3(--getColumn3());
		return *this;
	}
	Matrix4& Matrix4::operator++() noexcept
	{
		setColumn0(++getColumn0());
		setColumn1(++getColumn1());
		setColumn2(++getColumn2());
		setColumn3(++getColumn3());
		return *this;
	}
	Matrix4 Matrix4::operator--(int) noexcept
	{
		auto result = Matrix4(*this);
		setColumn0(--getColumn0());
		setColumn1(--getColumn1());
		setColumn2(--getColumn2());
		setColumn3(--getColumn3());
		return result;
	}
	Matrix4 Matrix4::operator++(int) noexcept
	{
		auto result = Matrix4(*this);
		setColumn0(++getColumn0());
		setColumn1(++getColumn1());
		setColumn2(++getColumn2());
		setColumn3(++getColumn3());
		return result;
	}
	Matrix4 Matrix4::operator-() const noexcept
	{
		return Matrix4(
			-getColumn0(),
			-getColumn1(),
			-getColumn2(),
			-getColumn3());
	}

	Matrix4 Matrix4::operator-(const Matrix4& matrix) const noexcept
	{
		return Matrix4(
			getColumn0() - matrix.getColumn0(),
			getColumn1() - matrix.getColumn1(),
			getColumn2() - matrix.getColumn2(),
			getColumn3() - matrix.getColumn3());
	}
	Matrix4 Matrix4::operator+(const Matrix4& matrix) const noexcept
	{
		return Matrix4(
			getColumn0() + matrix.getColumn0(),
			getColumn1() + matrix.getColumn1(),
			getColumn2() + matrix.getColumn2(),
			getColumn3() + matrix.getColumn3());
	}
	Matrix4 Matrix4::operator/(const Matrix4& matrix) const noexcept
	{
		return *this * matrix.getInversed();
	}
	Vector4 Matrix4::operator/(const Vector4& vector) const noexcept
	{
		return getInversed() * vector;
	}
	Matrix4 Matrix4::operator*(const Matrix4& matrix) const noexcept
	{
		auto a0 = getColumn0();
		auto a1 = getColumn1();
		auto a2 = getColumn2();
		auto a3 = getColumn3();

		auto b0 = matrix.getColumn0();
		auto b1 = matrix.getColumn1();
		auto b2 = matrix.getColumn2();
		auto b3 = matrix.getColumn3();

		return Matrix4(
			a0 * b0.x + a1 * b0.y + a2 * b0.z + a3 * b0.w,
			a0 * b1.x + a1 * b1.y + a2 * b1.z + a3 * b1.w,
			a0 * b2.x + a1 * b2.y + a2 * b2.z + a3 * b2.w,
			a0 * b3.x + a1 * b3.y + a2 * b3.z + a3 * b3.w);
	}
	Vector4 Matrix4::operator*(const Vector4& vector) const noexcept
	{
		return
			getColumn0() * Vector4(vector.x) +
			getColumn1() * Vector4(vector.y) +
			getColumn2() * Vector4(vector.z) +
			getColumn3() * Vector4(vector.w);
	}

	Matrix4& Matrix4::operator-=(const Matrix4& matrix) noexcept
	{
		setColumn0(getColumn0() - matrix.getColumn0());
		setColumn1(getColumn1() - matrix.getColumn1());
		setColumn2(getColumn2() - matrix.getColumn2());
		setColumn3(getColumn3() - matrix.getColumn3());
		return *this;
	}
	Matrix4& Matrix4::operator+=(const Matrix4& matrix) noexcept
	{
		setColumn0(getColumn0() + matrix.getColumn0());
		setColumn1(getColumn1() + matrix.getColumn1());
		setColumn2(getColumn2() + matrix.getColumn2());
		setColumn3(getColumn3() + matrix.getColumn3());
		return *this;
	}
	Matrix4& Matrix4::operator/=(const Matrix4& matrix) noexcept
	{
		return *this *= matrix.getInversed();
	}
	Matrix4& Matrix4::operator*=(const Matrix4& matrix) noexcept
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

	Matrix4 Matrix4::operator-(float value) const noexcept
	{
		auto vector = Vector4(value);

		return Matrix4(
			getColumn0() - vector,
			getColumn1() - vector,
			getColumn2() - vector,
			getColumn3() - vector);
	}
	Matrix4 Matrix4::operator+(float value) const noexcept
	{
		auto vector = Vector4(value);

		return Matrix4(
			getColumn0() + vector,
			getColumn1() + vector,
			getColumn2() + vector,
			getColumn3() + vector);
	}
	Matrix4 Matrix4::operator/(float value) const noexcept
	{
		auto vector = Vector4(value);

		return Matrix4(
			getColumn0() / vector,
			getColumn1() / vector,
			getColumn2() / vector,
			getColumn3() / vector);
	}
	Matrix4 Matrix4::operator*(float value) const noexcept
	{
		auto vector = Vector4(value);

		return Matrix4(
			getColumn0() * vector,
			getColumn1() * vector,
			getColumn2() * vector,
			getColumn3() * vector);
	}
	Matrix4& Matrix4::operator-=(float value) noexcept
	{
		auto vector = Vector4(value);
		setColumn0(getColumn0() - vector);
		setColumn1(getColumn1() - vector);
		setColumn2(getColumn2() - vector);
		setColumn3(getColumn3() - vector);
		return *this;
	}
	Matrix4& Matrix4::operator+=(float value) noexcept
	{
		auto vector = Vector4(value);
		setColumn0(getColumn0() + vector);
		setColumn1(getColumn1() + vector);
		setColumn2(getColumn2() + vector);
		setColumn3(getColumn3() + vector);
		return *this;
	}
	Matrix4& Matrix4::operator/=(float value) noexcept
	{
		auto vector = Vector4(value);
		setColumn0(getColumn0() / vector);
		setColumn1(getColumn1() / vector);
		setColumn2(getColumn2() / vector);
		setColumn3(getColumn3() / vector);
		return *this;
	}
	Matrix4& Matrix4::operator*=(float value) noexcept
	{
		auto vector = Vector4(value);
		setColumn0(getColumn0() * vector);
		setColumn1(getColumn1() * vector);
		setColumn2(getColumn2() * vector);
		setColumn3(getColumn3() * vector);
		return *this;
	}

	Matrix4 Matrix4::createPerspectiveVk(
		float fieldOfView,
		float aspectRatio,
		float nearClipPlane,
		float farClipPlane)
	{
		auto tanHalfFov = tan(fieldOfView / 2.0f);

		return Matrix4(
			1.0f / (aspectRatio * tanHalfFov),
			0.0f, 0.0f, 0.0f, 0.0f,
			-1.0f / tanHalfFov,
			0.0f, 0.0f, 0.0f, 0.0f,
			farClipPlane / (farClipPlane - nearClipPlane),
			1.0f, 0.0f, 0.0f,
			-(farClipPlane * nearClipPlane) / (farClipPlane - nearClipPlane),
			0.0f);
	}
	Matrix4 Matrix4::createPerspectiveGl(
		float fieldOfView,
		float aspectRatio,
		float nearClipPlane,
		float farClipPlane)
	{
		auto tanHalfFov = tan(fieldOfView / 2.0f);

		return Matrix4(
			1.0f / (aspectRatio * tanHalfFov),
			0.0f, 0.0f, 0.0f, 0.0f,
			1.0f / tanHalfFov,
			0.0f, 0.0f, 0.0f, 0.0f,
			(farClipPlane + nearClipPlane) / (farClipPlane - nearClipPlane),
			1.0f, 0.0f, 0.0f,
			-(2.0f * farClipPlane * nearClipPlane) / (farClipPlane - nearClipPlane),
			0.0f);
	}
	Matrix4 Matrix4::createOrthographicVk(
		float left,
		float right,
		float bottom,
		float top,
		float nearClipPlane,
		float farClipPlane)
	{
		return Matrix4(
			2.0f / (right - left),
			0.0f, 0.0f, 0.0f, 0.0f,
			2.0f / (top - bottom),
			0.0f, 0.0f, 0.0f, 0.0f,
			1.0f / (farClipPlane - nearClipPlane),
			0.0f,
			-(right + left) / (right - left),
			-(top + bottom) / (top - bottom),
			-nearClipPlane / (farClipPlane - nearClipPlane),
			1.0f);
	}
	Matrix4 Matrix4::createOrthographicGl(
		float left,
		float right,
		float bottom,
		float top,
		float nearClipPlane,
		float farClipPlane)
	{
		return Matrix4(
			2.0f / (right - left),
			0.0f, 0.0f, 0.0f, 0.0f,
			2.0f / (top - bottom),
			0.0f, 0.0f, 0.0f, 0.0f,
			2.0f / (farClipPlane - nearClipPlane),
			0.0f,
			-(right + left) / (right - left),
			-(top + bottom) / (top - bottom),
			-(farClipPlane + nearClipPlane) / (farClipPlane - nearClipPlane),
			1.0f);
	}

	const Matrix4 Matrix4::zero = Matrix4(0.0f);
	const Matrix4 Matrix4::minusOne = Matrix4(-1.0f);
	const Matrix4 Matrix4::one = Matrix4(1.0f);
	const Matrix4 Matrix4::identity = Matrix4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}
