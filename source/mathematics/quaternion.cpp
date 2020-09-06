#include "Injector/Mathematics/Quaternion.hpp"
#include "Injector/EngineException.hpp"

#include <cmath>
#include <limits>

namespace Injector::Mathematics
{
	using namespace std;

	Quaternion::Quaternion() :
		x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{}
	Quaternion::Quaternion(float _x, float _y, float _z, float _w) :
		x(_x), y(_y), z(_z), w(_w)
	{}
	Quaternion::Quaternion(float angle, const Vector3& axis)
	{
		auto v = axis * sin(angle * 0.5f);
		x = v.x;
		y = v.y;
		z = v.z;
		w = cos(angle * 0.5f);
	}
	Quaternion::Quaternion(const Vector3& eulerAngles)
	{
		auto s = eulerAngles * 0.5f;
		s = s.getSine();

		auto c = eulerAngles * 0.5f;
		c = c.getCosine();

		x = s.x * c.y * c.z - c.x * s.y * s.z;
		y = c.x * s.y * c.z + s.x * c.y * s.z;
		z = c.x * c.y * s.z - s.x * s.y * c.z;
		w = c.x * c.y * c.z + s.x * s.y * s.z;
	}
	Quaternion::Quaternion(const Vector3& a, const Vector3& b)
	{
		auto norm = sqrt(a.getDotProduct(a) * b.getDotProduct(b));
		auto real = norm + a.getDotProduct(b);

		auto t = Vector3();

		if (real < 1.e-6f * norm)
		{
			// If a and b are exactly opposite, rotate 180 degrees
			// around an arbitrary orthogonal axis. Axis normalisation
			// can happen later, when we normalise the quaternion.
			real = 0.0f;

			t = abs(a.x) > abs(a.z) ? Vector3(-a.y, a.x, 0.0f) : Vector3(0.0f, -a.z, a.y);
		}
		else
		{
			// Otherwise, build quaternion the standard way.
			t = a.getCrossProduct(b);
		}

		// TODO: NOT SURE ABOUT ORDER
		*this = Quaternion(t.x, t.y, t.z, real).getNormalized();
	}
	Quaternion::Quaternion(const Matrix3& matrix)
	{
		auto fourXSquaredMinus1 = matrix.m00 - matrix.m11 - matrix.m22;
		auto fourYSquaredMinus1 = matrix.m11 - matrix.m00 - matrix.m22;
		auto fourZSquaredMinus1 = matrix.m22 - matrix.m00 - matrix.m11;
		auto fourWSquaredMinus1 = matrix.m00 + matrix.m11 + matrix.m22;

		auto fourBiggestSquaredMinus1 = fourWSquaredMinus1;
		int biggestIndex = 0;

		if (fourXSquaredMinus1 > fourBiggestSquaredMinus1)
		{
			fourBiggestSquaredMinus1 = fourXSquaredMinus1;
			biggestIndex = 1;
		}
		if (fourYSquaredMinus1 > fourBiggestSquaredMinus1)
		{
			fourBiggestSquaredMinus1 = fourYSquaredMinus1;
			biggestIndex = 2;
		}
		if (fourZSquaredMinus1 > fourBiggestSquaredMinus1)
		{
			fourBiggestSquaredMinus1 = fourZSquaredMinus1;
			biggestIndex = 3;
		}

		auto biggestValue = sqrt(fourBiggestSquaredMinus1 + 1.0f) * 0.5f;
		auto multiplier = 0.25f / biggestValue;

		switch (biggestIndex)
		{
		case 0:
			x = (matrix.m12 - matrix.m21) * multiplier;
			y = (matrix.m20 - matrix.m02) * multiplier;
			z = (matrix.m01 - matrix.m10) * multiplier;
			w = biggestValue;
		case 1:
			x = biggestValue;
			y = (matrix.m01 + matrix.m10) * multiplier;
			z = (matrix.m20 + matrix.m02) * multiplier;
			w = (matrix.m12 - matrix.m21) * multiplier;
		case 2:
			x = (matrix.m01 + matrix.m10) * multiplier;
			y = biggestValue;
			z = (matrix.m12 + matrix.m21) * multiplier;
			w = (matrix.m20 - matrix.m02) * multiplier;
		case 3:
			x = (matrix.m20 + matrix.m02) * multiplier;
			y = (matrix.m12 + matrix.m21) * multiplier;
			z = biggestValue;
			w = (matrix.m01 - matrix.m10) * multiplier;
		default:
			throw EngineException("Something went wrong");
		}
	}
	Quaternion::Quaternion(const Matrix4& matrix)
	{
		auto fourXSquaredMinus1 = matrix.m00 - matrix.m11 - matrix.m22;
		auto fourYSquaredMinus1 = matrix.m11 - matrix.m00 - matrix.m22;
		auto fourZSquaredMinus1 = matrix.m22 - matrix.m00 - matrix.m11;
		auto fourWSquaredMinus1 = matrix.m00 + matrix.m11 + matrix.m22;

		auto fourBiggestSquaredMinus1 = fourWSquaredMinus1;
		int biggestIndex = 0;

		if (fourXSquaredMinus1 > fourBiggestSquaredMinus1)
		{
			fourBiggestSquaredMinus1 = fourXSquaredMinus1;
			biggestIndex = 1;
		}
		if (fourYSquaredMinus1 > fourBiggestSquaredMinus1)
		{
			fourBiggestSquaredMinus1 = fourYSquaredMinus1;
			biggestIndex = 2;
		}
		if (fourZSquaredMinus1 > fourBiggestSquaredMinus1)
		{
			fourBiggestSquaredMinus1 = fourZSquaredMinus1;
			biggestIndex = 3;
		}

		auto biggestValue = sqrt(fourBiggestSquaredMinus1 + 1.0f) * 0.5f;
		auto multiplier = 0.25f / biggestValue;

		switch (biggestIndex)
		{
		case 0:
			x = (matrix.m12 - matrix.m21) * multiplier;
			y = (matrix.m20 - matrix.m02) * multiplier;
			z = (matrix.m01 - matrix.m10) * multiplier;
			w = biggestValue;
		case 1:
			x = biggestValue;
			y = (matrix.m01 + matrix.m10) * multiplier;
			z = (matrix.m20 + matrix.m02) * multiplier;
			w = (matrix.m12 - matrix.m21) * multiplier;
		case 2:
			x = (matrix.m01 + matrix.m10) * multiplier;
			y = biggestValue;
			z = (matrix.m12 + matrix.m21) * multiplier;
			w = (matrix.m20 - matrix.m02) * multiplier;
		case 3:
			x = (matrix.m20 + matrix.m02) * multiplier;
			y = (matrix.m12 + matrix.m21) * multiplier;
			z = biggestValue;
			w = (matrix.m01 - matrix.m10) * multiplier;
		default:
			throw EngineException("Something went wrong");
		}
	}

	float Quaternion::getDotProduct(const Quaternion& quaternion) const noexcept
	{
		auto l = Vector4(x, y, z, w);
		auto r = Vector4(quaternion.x, quaternion.y, quaternion.z, quaternion.w);
		return l.getDotProduct(r);
	}
	Quaternion Quaternion::getCrossProduct(const Quaternion& quaternion) const noexcept
	{
		return *this * quaternion;
	}
	float Quaternion::getLength() const noexcept
	{
		return sqrt(getDotProduct(*this));
	}
	Quaternion Quaternion::getNormalized() const noexcept
	{
		auto length = getLength();

		if (length <= 0.0f)
			return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);

		return *this * (1.0f / length);
	}
	Quaternion Quaternion::getConjugated() const noexcept
	{
		return Quaternion(-x, -y, -z, w);
	}
	Quaternion Quaternion::getInversed() const noexcept
	{
		return getConjugated() / getDotProduct(*this);
	}
	Quaternion Quaternion::getLookedAt(
		const Vector3& direction, const Vector3& up) const noexcept
	{
		auto c0 = up.getCrossProduct(direction) *
			(1.0f / sqrt(fmaxf(0.00001f, direction.getDotProduct(direction))));
		return Quaternion(Matrix3(c0, direction.getCrossProduct(c0), direction));
	}

	float Quaternion::getAngle() const noexcept
	{
		if (abs(w) > static_cast<float>(0.877582561890372716130286068203503191))
			return asin(std::sqrt(x * x + y * y + z * z)) * 2.0f;
		return acos(w) * 2.0f;
	}
	float Quaternion::getRoll() const noexcept
	{
		return atan2(2.0f * (x * y + w * z), w * w + x * x - y * y - z * z);
	}
	float Quaternion::getPitch() const noexcept
	{
		float _y = 2.0f * (y * z + w * x);
		float _x = w * w - x * x - y * y + z * z;

		if (abs(_y) <= std::numeric_limits<float>::epsilon() &&
			abs(_x) <= std::numeric_limits<float>::epsilon())
			return 2.0f * atan2(x, w);

		return atan2(y, x);
	}
	float Quaternion::getYaw() const noexcept
	{
		return asin(fminf(fmaxf(-2.0f * (x * z - w * y), -1.0f), 1.0f));
	}
	Vector3 Quaternion::getAxis() const noexcept
	{
		auto tmp = 1.0f - w * w;

		if (tmp <= 0.0f)
			return Vector3(0.0f, 0.0f, 1.0f);

		tmp = 1.0f / sqrt(tmp);
		return Vector3(x * tmp, y * tmp, z * tmp);
	}
	Vector3 Quaternion::getEulerAngles() const noexcept
	{
		return Vector3(getPitch(), getYaw(), getRoll());
	}

	Matrix3 Quaternion::getMatrix3() const noexcept
	{
		auto xx = x * x;
		auto yy = y * y;
		auto zz = z * z;
		auto xz = x * z;
		auto xy = x * y;
		auto yz = y * z;
		auto wx = w * x;
		auto wy = w * y;
		auto wz = w * z;

		return Matrix3(
			1.0f - 2.0f * (yy + zz), 2.0f * (xy - wz), 2.0f * (xz + wy),
			2.0f * (xy + wz), 1.0f - 2.0f * (xx + zz), 2.0f * (yz - wx),
			2.0f * (xz - wy), 2.0f * (yz + wx), 1.0f - 2.0f * (xx + yy));
	}
	Matrix4 Quaternion::getMatrix4() const noexcept
	{
		auto xx = x * x;
		auto yy = y * y;
		auto zz = z * z;
		auto xz = x * z;
		auto xy = x * y;
		auto yz = y * z;
		auto wx = w * x;
		auto wy = w * y;
		auto wz = w * z;

		return Matrix4(
			1.0f - 2.0f * (yy + zz), 2.0f * (xy - wz), 2.0f * (xz + wy), 0.0f,
			2.0f * (xy + wz), 1.0f - 2.0f * (xx + zz), 2.0f * (yz - wx), 0.0f,
			2.0f * (xz - wy), 2.0f * (yz + wx), 1.0f - 2.0f * (xx + yy), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
	}

	bool Quaternion::operator==(const Quaternion& quaternion) const noexcept
	{
		return x == quaternion.x && y == quaternion.y &&
			z == quaternion.z && w == quaternion.w;
	}
	bool Quaternion::operator!=(const Quaternion& quaternion) const noexcept
	{
		return !(*this == quaternion);
	}

	Quaternion& Quaternion::operator--() noexcept
	{
		--x; --y; --z; --w;
		return *this;
	}
	Quaternion& Quaternion::operator++() noexcept
	{
		++x; ++y; ++z; ++w;
		return *this;
	}
	Quaternion Quaternion::operator--(int) noexcept
	{
		auto result = Quaternion(*this);
		--x; --y; --z; --w;
		return result;
	}
	Quaternion Quaternion::operator++(int) noexcept
	{
		auto result = Quaternion(*this);
		++x; ++y; ++z; ++w;
		return result;
	}

	Quaternion Quaternion::operator-() const noexcept
	{
		return Quaternion(-x, -y, -z, -w);
	}
	Quaternion Quaternion::operator+() const noexcept
	{
		return Quaternion(x, y, z, w);
	}

	Quaternion Quaternion::operator-(const Quaternion& quaternion) const noexcept
	{
		return Quaternion(x - quaternion.x, y - quaternion.y,
			z - quaternion.z, w - quaternion.w);
	}
	Quaternion Quaternion::operator+(const Quaternion& quaternion) const noexcept
	{
		return Quaternion(x + quaternion.x, y + quaternion.y,
			z + quaternion.z, w + quaternion.w);
	}
	Quaternion Quaternion::operator*(const Quaternion& quaternion) const noexcept
	{
		return Quaternion(
			w * quaternion.x + x * quaternion.w + y * quaternion.z - z * quaternion.y,
			w * quaternion.y + y * quaternion.w + z * quaternion.x - x * quaternion.z,
			w * quaternion.z + z * quaternion.w + x * quaternion.y - y * quaternion.x,
			w * quaternion.w - x * quaternion.x - y * quaternion.y - z * quaternion.z);
	}
	Vector3 Quaternion::operator*(const Vector3& vector) const noexcept
	{
		auto qv = Vector3(x, y, z);
		auto uv = qv.getCrossProduct(vector);
		auto uuv = qv.getCrossProduct(uv);
		return vector + ((uv * w) + uuv) * 2.0f;
	}
	Vector4 Quaternion::operator*(const Vector4& vector) const noexcept
	{
		auto v = vector.getVector3();
		return Vector4(*this * v, vector.w);
	}
	Quaternion& Quaternion::operator-=(const Quaternion& quaternion) noexcept
	{
		x -= quaternion.x;
		y -= quaternion.y;
		z -= quaternion.z;
		w -= quaternion.w;
		return *this;
	}
	Quaternion& Quaternion::operator+=(const Quaternion& quaternion) noexcept
	{
		x += quaternion.x;
		y += quaternion.y;
		z += quaternion.z;
		w += quaternion.w;
		return *this;
	}
	Quaternion& Quaternion::operator*=(const Quaternion& quaternion) noexcept
	{
		auto l = Quaternion(*this);
		auto r = Quaternion(quaternion);
		x = l.w * r.x + l.x * r.w + l.y * r.z - l.z * r.y;
		y = l.w * r.y + l.y * r.w + l.z * r.x - l.x * r.z;
		z = l.w * r.z + l.z * r.w + l.x * r.y - l.y * r.x;
		w = l.w * r.w - l.x * r.x - l.y * r.y - l.z * r.z;
		return *this;
	}

	Quaternion Quaternion::operator-(float value) const noexcept
	{
		return Quaternion(x - value, y - value, z - value, w - value);
	}
	Quaternion Quaternion::operator+(float value) const noexcept
	{
		return Quaternion(x + value, y + value, z + value, w + value);
	}
	Quaternion Quaternion::operator/(float value) const noexcept
	{
		return Quaternion(x / value, y / value, z / value, w / value);
	}
	Quaternion Quaternion::operator*(float value) const noexcept
	{
		return Quaternion(x * value, y * value, z * value, w * value);
	}
	Quaternion& Quaternion::operator-=(float value) noexcept
	{
		x -= value;
		y -= value;
		z -= value;
		w -= value;
		return *this;
	}
	Quaternion& Quaternion::operator+=(float value) noexcept
	{
		x += value;
		y += value;
		z += value;
		w += value;
		return *this;
	}
	Quaternion& Quaternion::operator/=(float value) noexcept
	{
		x /= value;
		y /= value;
		z /= value;
		w /= value;
		return *this;
	}
	Quaternion& Quaternion::operator*=(float value) noexcept
	{
		x *= value;
		y *= value;
		z *= value;
		w *= value;
		return *this;
	}

	const Quaternion Quaternion::zero = Quaternion(Vector3::zero);
}
