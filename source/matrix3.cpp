#include <injector/matrix3.hpp>

namespace INJECTOR_NAMESPACE
{
	Matrix3::Matrix3() :
		m00(0.0f), m01(0.0f), m02(0.0f),
		m10(0.0f), m11(0.0f), m12(0.0f),
		m20(0.0f), m21(0.0f), m22(0.0f)
	{}
	Matrix3::Matrix3(
		float _m00, float _m01, float _m02,
		float _m10, float _m11, float _m12,
		float _m20, float _m21, float _m22) :
		m00(_m00), m01(_m01), m02(_m02),
		m10(_m10), m11(_m11), m12(_m12),
		m20(_m20), m21(_m21), m22(_m22)
	{}

	Matrix3 Matrix3::getDot(const Matrix3& other) const noexcept
	{
		return Matrix3(
			m00 * other.m00 + m01 * other.m10 + m02 * other.m20,
			m00 * other.m01 + m01 * other.m11 + m02 * other.m21,
			m00 * other.m02 + m01 * other.m12 + m02 * other.m22,

			m10 * other.m00 + m11 * other.m10 + m12 * other.m20,
			m10 * other.m01 + m11 * other.m11 + m12 * other.m21,
			m10 * other.m02 + m11 * other.m12 + m12 * other.m22,

			m20 * other.m00 + m21 * other.m10 + m22 * other.m20,
			m20 * other.m01 + m21 * other.m11 + m22 * other.m21,
			m20 * other.m02 + m21 * other.m12 + m22 * other.m22);
	}
	Matrix3 Matrix3::getTransposed() const noexcept
	{
		return Matrix3(
			m00, m10, m20,
			m01, m11, m21,
			m02, m12, m22);
	}
	float Matrix3::getDeterminant() const noexcept
	{
		return
			m00 * (m11 * m22 - m21 * m12) -
			m10 * (m01 * m22 - m21 * m02) +
			m20 * (m01 * m12 - m11 * m02);
	}
	Matrix3 Matrix3::getInversed() const noexcept
	{
		auto determinant = 1.0f / getDeterminant();

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

	const Matrix3 Matrix3::zero = Matrix3(
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f);
	const Matrix3 Matrix3::minusOne = Matrix3(
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f);
	const Matrix3 Matrix3::one = Matrix3(
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f);
	const Matrix3 Matrix3::identity = Matrix3(
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f);
}
