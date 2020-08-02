#include <injector/mathematics/matrix3.hpp>

namespace INJECTOR_NAMESPACE
{
	Matrix3::Matrix3() :
		m00(0.0f), m10(0.0f), m20(0.0f),
		m01(0.0f), m11(0.0f), m21(0.0f),
		m02(0.0f), m12(0.0f), m22(0.0f)
	{}
	Matrix3::Matrix3(float value) :
		m00(value), m10(value), m20(value),
		m01(value), m11(value), m21(value),
		m02(value), m12(value), m22(value)
	{}
	Matrix3::Matrix3(
		float _m00, float _m10, float _m20,
		float _m01, float _m11, float _m21,
		float _m02, float _m12, float _m22) :
		m00(_m00), m10(_m10), m20(_m20),
		m01(_m01), m11(_m11), m21(_m21),
		m02(_m02), m12(_m12), m22(_m22)
	{}
	Matrix3::Matrix3(
		const Vector3& column0,
		const Vector3& column1,
		const Vector3& column2) :
		m00(column0.x), m10(column0.y), m20(column0.z),
		m01(column1.x), m11(column1.y), m21(column1.z),
		m02(column2.x), m12(column2.y), m22(column2.z)
	{}

	float Matrix3::getDeterminant() const noexcept
	{
		return
			m00 * (m11 * m22 - m21 * m12) -
			m10 * (m01 * m22 - m21 * m02) +
			m20 * (m01 * m12 - m11 * m02);
	}
	Matrix3 Matrix3::getTransposed() const noexcept
	{
		return Matrix3(
			m00, m01, m02,
			m10, m11, m12,
			m20, m21, m22);
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

	Vector3 Matrix3::getRow0() const noexcept
	{
		return Vector3(m00, m01, m02);
	}
	Vector3 Matrix3::getRow1() const noexcept
	{
		return Vector3(m10, m11, m12);
	}
	Vector3 Matrix3::getRow2() const noexcept
	{
		return Vector3(m20, m21, m22);
	}
	void Matrix3::setRow0(const Vector3& vector) noexcept
	{
		m00 = vector.x;
		m01 = vector.y;
		m02 = vector.z;
	}
	void Matrix3::setRow1(const Vector3& vector) noexcept
	{
		m10 = vector.x;
		m11 = vector.y;
		m12 = vector.z;
	}
	void Matrix3::setRow2(const Vector3& vector) noexcept
	{
		m20 = vector.x;
		m21 = vector.y;
		m22 = vector.z;
	}

	Vector3 Matrix3::getColumn0() const noexcept
	{
		return Vector3(m00, m10, m20);
	}
	Vector3 Matrix3::getColumn1() const noexcept
	{
		return Vector3(m01, m11, m21);
	}
	Vector3 Matrix3::getColumn2() const noexcept
	{
		return Vector3(m02, m12, m22);
	}
	void Matrix3::setColumn0(const Vector3& vector) noexcept
	{
		m00 = vector.x;
		m10 = vector.y;
		m20 = vector.z;
	}
	void Matrix3::setColumn1(const Vector3& vector) noexcept
	{
		m01 = vector.x;
		m11 = vector.y;
		m21 = vector.z;
	}
	void Matrix3::setColumn2(const Vector3& vector) noexcept
	{
		m02 = vector.x;
		m12 = vector.y;
		m22 = vector.z;
	}

	Matrix2 Matrix3::getMatrix2() const noexcept
	{
		return Matrix2(
			m00, m10,
			m01, m11);
	}

	bool Matrix3::operator==(const Matrix3& matrix) const noexcept
	{
		return getColumn0() == matrix.getColumn0() &&
			getColumn1() == matrix.getColumn1() &&
			getColumn2() == matrix.getColumn2();
	}
	bool Matrix3::operator!=(const Matrix3& matrix) const noexcept
	{
		return !(*this == matrix);
	}

	Matrix3& Matrix3::operator--() noexcept
	{
		setColumn0(--getColumn0());
		setColumn1(--getColumn1());
		setColumn2(--getColumn2());
		return *this;
	}
	Matrix3& Matrix3::operator++() noexcept
	{
		setColumn0(++getColumn0());
		setColumn1(++getColumn1());
		setColumn2(++getColumn2());
		return *this;
	}
	Matrix3 Matrix3::operator--(int) noexcept
	{
		auto result = Matrix3(*this);
		setColumn0(--getColumn0());
		setColumn1(--getColumn1());
		setColumn2(--getColumn2());
		return result;
	}
	Matrix3 Matrix3::operator++(int) noexcept
	{
		auto result = Matrix3(*this);
		setColumn0(++getColumn0());
		setColumn1(++getColumn1());
		setColumn2(++getColumn2());
		return result;
	}
	Matrix3 Matrix3::operator-() const noexcept
	{
		return Matrix3(
			-getColumn0(),
			-getColumn1(),
			-getColumn2());
	}

	Matrix3 Matrix3::operator-(const Matrix3& matrix) const noexcept
	{
		return Matrix3(getColumn0() - matrix.getColumn0(),
			getColumn1() - matrix.getColumn1(),
			getColumn2() - matrix.getColumn2());
	}
	Matrix3 Matrix3::operator+(const Matrix3& matrix) const noexcept
	{
		return Matrix3(getColumn0() + matrix.getColumn0(),
			getColumn1() + matrix.getColumn1(),
			getColumn2() + matrix.getColumn2());
	}
	Matrix3 Matrix3::operator/(const Matrix3& matrix) const noexcept
	{
		return *this * matrix.getInversed();
	}
	Vector3 Matrix3::operator/(const Vector3& vector) const noexcept
	{
		return getInversed() * vector;
	}
	Matrix3 Matrix3::operator*(const Matrix3& matrix) const noexcept
	{
		auto a0 = getColumn0();
		auto a1 = getColumn1();
		auto a2 = getColumn2();

		auto b0 = matrix.getColumn0();
		auto b1 = matrix.getColumn1();
		auto b2 = matrix.getColumn2();

		return Matrix3(
			a0 * b0.x + a1 * b0.y + a2 * b0.z,
			a0 * b1.x + a1 * b1.y + a2 * b1.z,
			a0 * b2.x + a1 * b2.y + a2 * b2.z);
	}
	Vector3 Matrix3::operator*(const Vector3& vector) const noexcept
	{
		return getColumn0() * Vector3(vector.x) +
			getColumn1() * Vector3(vector.y) +
			getColumn2() * Vector3(vector.z);
	}

	Matrix3& Matrix3::operator-=(const Matrix3& matrix) noexcept
	{
		setColumn0(getColumn0() - matrix.getColumn0());
		setColumn1(getColumn1() - matrix.getColumn1());
		setColumn2(getColumn2() - matrix.getColumn2());
		return *this;
	}
	Matrix3& Matrix3::operator+=(const Matrix3& matrix) noexcept
	{
		setColumn0(getColumn0() + matrix.getColumn0());
		setColumn1(getColumn1() + matrix.getColumn1());
		setColumn2(getColumn2() + matrix.getColumn2());
		return *this;
	}
	Matrix3& Matrix3::operator/=(const Matrix3& matrix) noexcept
	{
		return *this *= matrix.getInversed();
	}
	Matrix3& Matrix3::operator*=(const Matrix3& matrix) noexcept
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

	Matrix3 Matrix3::operator-(float value) const noexcept
	{
		auto vector = Vector3(value);

		return Matrix3(getColumn0() - vector,
			getColumn1() - vector,
			getColumn2() - vector);
	}
	Matrix3 Matrix3::operator+(float value) const noexcept
	{
		auto vector = Vector3(value);

		return Matrix3(getColumn0() + vector,
			getColumn1() + vector,
			getColumn2() + vector);
	}
	Matrix3 Matrix3::operator/(float value) const noexcept
	{
		auto vector = Vector3(value);

		return Matrix3(getColumn0() / vector,
			getColumn1() / vector,
			getColumn2() / vector);
	}
	Matrix3 Matrix3::operator*(float value) const noexcept
	{
		auto vector = Vector3(value);

		return Matrix3(getColumn0() * vector,
			getColumn1() * vector,
			getColumn2() * vector);
	}
	Matrix3& Matrix3::operator-=(float value) noexcept
	{
		auto vector = Vector3(value);
		setColumn0(getColumn0() - vector);
		setColumn1(getColumn1() - vector);
		setColumn2(getColumn2() - vector);
		return *this;
	}
	Matrix3& Matrix3::operator+=(float value) noexcept
	{
		auto vector = Vector3(value);
		setColumn0(getColumn0() + vector);
		setColumn1(getColumn1() + vector);
		setColumn2(getColumn2() + vector);
		return *this;
	}
	Matrix3& Matrix3::operator/=(float value) noexcept
	{
		auto vector = Vector3(value);
		setColumn0(getColumn0() / vector);
		setColumn1(getColumn1() / vector);
		setColumn2(getColumn2() / vector);
		return *this;
	}
	Matrix3& Matrix3::operator*=(float value) noexcept
	{
		auto vector = Vector3(value);
		setColumn0(getColumn0() * vector);
		setColumn1(getColumn1() * vector);
		setColumn2(getColumn2() * vector);
		return *this;
	}

	const Matrix3 Matrix3::zero = Matrix3(0.0f);
	const Matrix3 Matrix3::minusOne = Matrix3(-1.0f);
	const Matrix3 Matrix3::one = Matrix3(1.0f);
	const Matrix3 Matrix3::identity = Matrix3(
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f);
}
