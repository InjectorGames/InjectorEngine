#include <injector/matrix2.hpp>

namespace INJECTOR_NAMESPACE
{
	Matrix2::Matrix2() :
		m00(0.0f), m01(0.0f),
		m10(0.0f), m11(0.0f)
	{}
	Matrix2::Matrix2(
		float _m00, float _m01,
		float _m10, float _m11) :
		m00(_m00), m01(_m01),
		m10(_m10), m11(_m11)
	{}

	Matrix2 Matrix2::getDot(const Matrix2& other) const noexcept
	{
		return Matrix2(
			m00 * other.m00 + m01 * other.m10,
			m00 * other.m01 + m01 * other.m11,

			m10 * other.m00 + m11 * other.m10,
			m10 * other.m01 + m11 * other.m11);
	}
	Matrix2 Matrix2::getTransposed() const noexcept
	{
		return Matrix2(
			m00, m10,
			m01, m11);
	}
	float Matrix2::getDeterminant() const noexcept
	{
		return
			m00 * m11 -
			m10 * m01;
	}
	Matrix2 Matrix2::getInversed() const noexcept
	{
		auto determinant = 1.0f / getDeterminant();

		return Matrix2(
			m11 * determinant, -m01 * determinant,
			-m10 * determinant, m00 * determinant);
	}

	const Matrix2 Matrix2::zero = Matrix2(
		0.0f, 0.0f,
		0.0f, 0.0f);
	const Matrix2 Matrix2::minusOne = Matrix2(
		-1.0f, -1.0f,
		-1.0f, -1.0f);
	const Matrix2 Matrix2::one = Matrix2(
		1.0f, 1.0f,
		1.0f, 1.0f);
	const Matrix2 Matrix2::identity = Matrix2(
		1.0f, 0.0f,
		0.0f, 1.0f);
}
