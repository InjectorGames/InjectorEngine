#include <injector/matrix4.hpp>

namespace INJECTOR_NAMESPACE
{
	Matrix4::Matrix4() :
		m00(0.0f), m01(0.0f), m02(0.0f), m03(0.0f),
		m10(0.0f), m11(0.0f), m12(0.0f), m13(0.0f),
		m20(0.0f), m21(0.0f), m22(0.0f), m23(0.0f),
		m30(0.0f), m31(0.0f), m32(0.0f), m33(0.0f)
	{}
	Matrix4::Matrix4(
		float _m00, float _m01, float _m02, float _m03,
		float _m10, float _m11, float _m12, float _m13,
		float _m20, float _m21, float _m22, float _m23,
		float _m30, float _m31, float _m32, float _m33) :
		m00(_m00), m01(_m01), m02(_m02), m03(_m03),
		m10(_m10), m11(_m11), m12(_m12), m13(_m13),
		m20(_m20), m21(_m21), m22(_m22), m23(_m23),
		m30(_m30), m31(_m31), m32(_m32), m33(_m33)
	{}

	Matrix4 Matrix4::getDot(const Matrix4& other) const noexcept
	{
		return Matrix4(
			m00 * other.m00 + m01 * other.m10 + m02 * other.m20 + m03 * other.m30,
			m00 * other.m01 + m01 * other.m11 + m02 * other.m21 + m03 * other.m31,
			m00 * other.m02 + m01 * other.m12 + m02 * other.m22 + m03 * other.m32,
			m00 * other.m03 + m01 * other.m13 + m02 * other.m23 + m03 * other.m33,

			m10 * other.m00 + m11 * other.m10 + m12 * other.m20 + m13 * other.m30,
			m10 * other.m01 + m11 * other.m11 + m12 * other.m21 + m13 * other.m31,
			m10 * other.m02 + m11 * other.m12 + m12 * other.m22 + m13 * other.m32,
			m10 * other.m03 + m11 * other.m13 + m12 * other.m23 + m13 * other.m33,

			m20 * other.m00 + m21 * other.m10 + m22 * other.m20 + m23 * other.m30,
			m20 * other.m01 + m21 * other.m11 + m22 * other.m21 + m23 * other.m31,
			m20 * other.m02 + m21 * other.m12 + m22 * other.m22 + m23 * other.m32,
			m20 * other.m03 + m21 * other.m13 + m22 * other.m23 + m23 * other.m33,

			m30 * other.m00 + m31 * other.m10 + m32 * other.m20 + m33 * other.m30,
			m30 * other.m01 + m31 * other.m11 + m32 * other.m21 + m33 * other.m31,
			m30 * other.m02 + m31 * other.m12 + m32 * other.m22 + m33 * other.m32,
			m30 * other.m03 + m31 * other.m13 + m32 * other.m23 + m33 * other.m33);
	}
	Matrix4 Matrix4::getTransposed() const noexcept
	{
		return Matrix4(
			m00, m10, m20, m30,
			m01, m11, m21, m31,
			m02, m12, m22, m32,
			m03, m13, m23, m33);
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
	Matrix4 Matrix4::getInversed() const noexcept
	{
		// TODO:

		/*T Coef00 = m[2][2] * m[3][3] - m[3][2] * m[2][3];
		T Coef02 = m[1][2] * m[3][3] - m[3][2] * m[1][3];
		T Coef03 = m[1][2] * m[2][3] - m[2][2] * m[1][3];

		T Coef04 = m[2][1] * m[3][3] - m[3][1] * m[2][3];
		T Coef06 = m[1][1] * m[3][3] - m[3][1] * m[1][3];
		T Coef07 = m[1][1] * m[2][3] - m[2][1] * m[1][3];

		T Coef08 = m[2][1] * m[3][2] - m[3][1] * m[2][2];
		T Coef10 = m[1][1] * m[3][2] - m[3][1] * m[1][2];
		T Coef11 = m[1][1] * m[2][2] - m[2][1] * m[1][2];

		T Coef12 = m[2][0] * m[3][3] - m[3][0] * m[2][3];
		T Coef14 = m[1][0] * m[3][3] - m[3][0] * m[1][3];
		T Coef15 = m[1][0] * m[2][3] - m[2][0] * m[1][3];

		T Coef16 = m[2][0] * m[3][2] - m[3][0] * m[2][2];
		T Coef18 = m[1][0] * m[3][2] - m[3][0] * m[1][2];
		T Coef19 = m[1][0] * m[2][2] - m[2][0] * m[1][2];

		T Coef20 = m[2][0] * m[3][1] - m[3][0] * m[2][1];
		T Coef22 = m[1][0] * m[3][1] - m[3][0] * m[1][1];
		T Coef23 = m[1][0] * m[2][1] - m[2][0] * m[1][1];

		vec<4, T, Q> Fac0(Coef00, Coef00, Coef02, Coef03);
		vec<4, T, Q> Fac1(Coef04, Coef04, Coef06, Coef07);
		vec<4, T, Q> Fac2(Coef08, Coef08, Coef10, Coef11);
		vec<4, T, Q> Fac3(Coef12, Coef12, Coef14, Coef15);
		vec<4, T, Q> Fac4(Coef16, Coef16, Coef18, Coef19);
		vec<4, T, Q> Fac5(Coef20, Coef20, Coef22, Coef23);

		vec<4, T, Q> Vec0(m[1][0], m[0][0], m[0][0], m[0][0]);
		vec<4, T, Q> Vec1(m[1][1], m[0][1], m[0][1], m[0][1]);
		vec<4, T, Q> Vec2(m[1][2], m[0][2], m[0][2], m[0][2]);
		vec<4, T, Q> Vec3(m[1][3], m[0][3], m[0][3], m[0][3]);

		vec<4, T, Q> Inv0(Vec1 * Fac0 - Vec2 * Fac1 + Vec3 * Fac2);
		vec<4, T, Q> Inv1(Vec0 * Fac0 - Vec2 * Fac3 + Vec3 * Fac4);
		vec<4, T, Q> Inv2(Vec0 * Fac1 - Vec1 * Fac3 + Vec3 * Fac5);
		vec<4, T, Q> Inv3(Vec0 * Fac2 - Vec1 * Fac4 + Vec2 * Fac5);

		vec<4, T, Q> SignA(+1, -1, +1, -1);
		vec<4, T, Q> SignB(-1, +1, -1, +1);
		mat<4, 4, T, Q> Inverse(Inv0 * SignA, Inv1 * SignB, Inv2 * SignA, Inv3 * SignB);

		vec<4, T, Q> Row0(Inverse[0][0], Inverse[1][0], Inverse[2][0], Inverse[3][0]);

		vec<4, T, Q> Dot0(m[0] * Row0);
		T Dot1 = (Dot0.x + Dot0.y) + (Dot0.z + Dot0.w);

		T OneOverDeterminant = static_cast<T>(1) / Dot1;

		return Inverse * OneOverDeterminant;*/

		return zero;
	}


	const Matrix4 Matrix4::zero = Matrix4(
		0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f, 
		0.0f, 0.0f, 0.0f, 0.0f, 
		0.0f, 0.0f, 0.0f, 0.0f);
	const Matrix4 Matrix4::minusOne = Matrix4(
		-1.0f, -1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f, -1.0f);
	const Matrix4 Matrix4::one = Matrix4(
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f);
	const Matrix4 Matrix4::identity = Matrix4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f);
}
