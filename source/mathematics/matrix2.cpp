#include <injector/mathematics/matrix2.hpp>

namespace INJECTOR_NAMESPACE
{
	Matrix2::Matrix2() :
		m00(0.0f), m01(0.0f),
		m10(0.0f), m11(0.0f)
	{}
	Matrix2::Matrix2(float value) :
		m00(value), m01(value),
		m10(value), m11(value)
	{}
	Matrix2::Matrix2(
		float _m00, float _m01,
		float _m10, float _m11) :
		m00(_m00), m01(_m01),
		m10(_m10), m11(_m11)
	{}
	Matrix2::Matrix2(
		const Vector2& column0,
		const Vector2& column1) :
		m00(column0.x), m01(column0.y),
		m10(column1.x), m11(column1.y)
	{}

	float Matrix2::getDeterminant() const noexcept
	{
		return
			m00 * m11 -
			m10 * m01;
	}
	Matrix2 Matrix2::getTransposed() const noexcept
	{
		return Matrix2(
			m00, m10,
			m01, m11);
	}
	Matrix2 Matrix2::getInversed() const noexcept
	{
		auto determinant = 1.0f / getDeterminant();

		return Matrix2(
			m11 * determinant, -m01 * determinant,
			-m10 * determinant, m00 * determinant);
	}

	Vector2 Matrix2::getRow0() const noexcept
	{
		return Vector2(m00, m10);
	}
	Vector2 Matrix2::getRow1() const noexcept
	{
		return Vector2(m01, m11);
	}
	void Matrix2::setRow0(const Vector2& vector) noexcept
	{
		m00 = vector.x;
		m10 = vector.y;
	}
	void Matrix2::setRow1(const Vector2& vector) noexcept
	{
		m01 = vector.x;
		m11 = vector.y;
	}

	Vector2 Matrix2::getColumn0() const noexcept
	{
		return Vector2(m00, m01);
	}
	Vector2 Matrix2::getColumn1() const noexcept
	{
		return Vector2(m10, m11);
	}
	void Matrix2::setColumn0(const Vector2& vector) noexcept
	{
		m00 = vector.x;
		m01 = vector.y;
	}
	void Matrix2::setColumn1(const Vector2& vector) noexcept
	{
		m10 = vector.x;
		m11 = vector.y;
	}

	bool Matrix2::operator==(const Matrix2& matrix) const noexcept
	{
		return 
			getColumn0() == matrix.getColumn0() &&
			getColumn1() == matrix.getColumn1();
	}
	bool Matrix2::operator!=(const Matrix2& matrix) const noexcept
	{
		return !(*this == matrix);
	}

	Matrix2& Matrix2::operator--() noexcept
	{
		setColumn0(--getColumn0());
		setColumn1(--getColumn1());
		return *this;
	}
	Matrix2& Matrix2::operator++() noexcept
	{
		setColumn0(++getColumn0());
		setColumn1(++getColumn1());
		return *this;
	}
	Matrix2 Matrix2::operator--(int) noexcept
	{
		auto result = Matrix2(*this);
		setColumn0(--getColumn0());
		setColumn1(--getColumn1());
		return result;
	}
	Matrix2 Matrix2::operator++(int) noexcept
	{
		auto result = Matrix2(*this);
		setColumn0(++getColumn0());
		setColumn1(++getColumn1());
		return result;
	}
	Matrix2 Matrix2::operator-() const noexcept
	{
		return Matrix2(
			-getColumn0(),
			-getColumn1());
	}

	Matrix2 Matrix2::operator-(const Matrix2& matrix) const noexcept
	{
		return Matrix2(
			getColumn0() - matrix.getColumn0(),
			getColumn1() - matrix.getColumn1());
	}
	Matrix2 Matrix2::operator+(const Matrix2& matrix) const noexcept
	{
		return Matrix2(
			getColumn0() + matrix.getColumn0(),
			getColumn1() + matrix.getColumn1());
	}
	Matrix2 Matrix2::operator/(const Matrix2& matrix) const noexcept
	{
		return *this * matrix.getInversed();
	}
	Vector2 Matrix2::operator/(const Vector2& vector) const noexcept
	{
		return getInversed() * vector;
	}
	Matrix2 Matrix2::operator*(const Matrix2& matrix) const noexcept
	{
		auto a0 = getColumn0();
		auto a1 = getColumn1();

		auto b0 = matrix.getColumn0();
		auto b1 = matrix.getColumn1();

		return Matrix2(
			a0 * b0.x + a1 * b0.y,
			a0 * b1.x + a1 * b1.y);
	}
	Vector2 Matrix2::operator*(const Vector2& vector) const noexcept
	{
		return 
			getColumn0() * Vector2(vector.x) +
			getColumn1() * Vector2(vector.y);
	}

	Matrix2& Matrix2::operator-=(const Matrix2& matrix) noexcept
	{
		setColumn0(getColumn0() - matrix.getColumn0());
		setColumn1(getColumn1() - matrix.getColumn1());
		return *this;
	}
	Matrix2& Matrix2::operator+=(const Matrix2& matrix) noexcept
	{
		setColumn0(getColumn0() + matrix.getColumn0());
		setColumn1(getColumn1() + matrix.getColumn1());
		return *this;
	}
	Matrix2& Matrix2::operator/=(const Matrix2& matrix) noexcept
	{
		return *this *= matrix.getInversed();
	}
	Matrix2& Matrix2::operator*=(const Matrix2& matrix) noexcept
	{
		auto a0 = getColumn0();
		auto a1 = getColumn1();

		auto b0 = matrix.getColumn0();
		auto b1 = matrix.getColumn1();

		setColumn0(a0 * b0.x + a1 * b0.y);
		setColumn1(a0 * b1.x + a1 * b1.y);
		return *this;
	}

	Matrix2 Matrix2::operator-(float value) const noexcept
	{
		auto vector = Vector2(value);

		return Matrix2(
			getColumn0() - vector,
			getColumn1() - vector);
	}
	Matrix2 Matrix2::operator+(float value) const noexcept
	{
		auto vector = Vector2(value);

		return Matrix2(
			getColumn0() + vector,
			getColumn1() + vector);
	}
	Matrix2 Matrix2::operator/(float value) const noexcept
	{
		auto vector = Vector2(value);

		return Matrix2(
			getColumn0() / vector,
			getColumn1() / vector);
	}
	Matrix2 Matrix2::operator*(float value) const noexcept
	{
		auto vector = Vector2(value);

		return Matrix2(
			getColumn0() * vector,
			getColumn1() * vector);
	}
	Matrix2& Matrix2::operator-=(float value) noexcept
	{
		auto vector = Vector2(value);
		setColumn0(getColumn0() - vector);
		setColumn1(getColumn1() - vector);
		return *this;
	}
	Matrix2& Matrix2::operator+=(float value) noexcept
	{
		auto vector = Vector2(value);
		setColumn0(getColumn0() + vector);
		setColumn1(getColumn1() + vector);
		return *this;
	}
	Matrix2& Matrix2::operator/=(float value) noexcept
	{
		auto vector = Vector2(value);
		setColumn0(getColumn0() / vector);
		setColumn1(getColumn1() / vector);
		return *this;
	}
	Matrix2& Matrix2::operator*=(float value) noexcept
	{
		auto vector = Vector2(value);
		setColumn0(getColumn0() * vector);
		setColumn1(getColumn1() * vector);
		return *this;
	}

	const Matrix2 Matrix2::zero = Matrix2(0.0f);
	const Matrix2 Matrix2::minusOne = Matrix2(-1.0f);
	const Matrix2 Matrix2::one = Matrix2(1.0f);
	const Matrix2 Matrix2::identity = Matrix2(
		1.0f, 0.0f,
		0.0f, 1.0f);
}
