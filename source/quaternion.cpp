#include <injector/quaternion.hpp>

#include <cmath>
#include <limits>

namespace INJECTOR_NAMESPACE
{
	Quaternion::Quaternion() :
		x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{}
	Quaternion::Quaternion(float _x, float _y, float _z, float _w) :
		x(_x), y(_y), z(_z), w(_w)
	{}
	Quaternion::Quaternion(const Vector3& vector, float _w) :
		x(vector.x), y(vector.y), z(vector.z), w(_w)
	{}
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
		auto norm = std::sqrt(a.getDotProduct(a) * b.getDotProduct(b));
		auto real = norm + a.getDotProduct(b);

		auto t = Vector3();

		if (real < 1.e-6f * norm)
		{
			// If a and b are exactly opposite, rotate 180 degrees
			// around an arbitrary orthogonal axis. Axis normalisation
			// can happen later, when we normalise the quaternion.
			real = 0.0f;

			t = std::abs(a.x) > std::abs(a.z) ?
				Vector3(-a.y, a.x, 0.0f) : Vector3(0.0f, -a.z, a.y);
		}
		else
		{
			// Otherwise, build quaternion the standard way.
			t = a.getCrossProduct(b);
		}

		*this = Quaternion(real, t.x, t.y, t.z).getNormalized();
	}
	Quaternion::Quaternion(const Matrix3 matrix)
	{
		T fourXSquaredMinus1 = m[0][0] - m[1][1] - m[2][2];
		T fourYSquaredMinus1 = m[1][1] - m[0][0] - m[2][2];
		T fourZSquaredMinus1 = m[2][2] - m[0][0] - m[1][1];
		T fourWSquaredMinus1 = m[0][0] + m[1][1] + m[2][2];

		int biggestIndex = 0;
		T fourBiggestSquaredMinus1 = fourWSquaredMinus1;
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

		T biggestVal = sqrt(fourBiggestSquaredMinus1 + static_cast<T>(1)) * static_cast<T>(0.5);
		T mult = static_cast<T>(0.25) / biggestVal;

		switch (biggestIndex)
		{
		case 0:
			return qua<T, Q>(biggestVal, (m[1][2] - m[2][1]) * mult, (m[2][0] - m[0][2]) * mult, (m[0][1] - m[1][0]) * mult);
		case 1:
			return qua<T, Q>((m[1][2] - m[2][1]) * mult, biggestVal, (m[0][1] + m[1][0]) * mult, (m[2][0] + m[0][2]) * mult);
		case 2:
			return qua<T, Q>((m[2][0] - m[0][2]) * mult, (m[0][1] + m[1][0]) * mult, biggestVal, (m[1][2] + m[2][1]) * mult);
		case 3:
			return qua<T, Q>((m[0][1] - m[1][0]) * mult, (m[2][0] + m[0][2]) * mult, (m[1][2] + m[2][1]) * mult, biggestVal);
		default: // Silence a -Wswitch-default warning in GCC. Should never actually get here. Assert is just for sanity.
			assert(false);
			return qua<T, Q>(1, 0, 0, 0);
		}
	}
	Quaternion::Quaternion(const Matrix4 matrix)
	{

	}

	float Quaternion::getDotProduct(const Quaternion& quaternion) const noexcept
	{
		auto result = *this * quaternion;
		return (result.x + result.y) + (result.z + result.w);
	}
	Quaternion Quaternion::getCrossProduct(const Quaternion& quaternion) const noexcept
	{
		return Quaternion(
			w * quaternion.x + x * quaternion.w + y * quaternion.z - z * quaternion.y,
			w * quaternion.y + y * quaternion.w + z * quaternion.x - x * quaternion.z,
			w * quaternion.z + z * quaternion.w + x * quaternion.y - y * quaternion.x,
			w * quaternion.w - x * quaternion.x - y * quaternion.y - z * quaternion.z);
	}
	float Quaternion::getLength() const noexcept
	{
		return std::sqrtf(getDotProduct(*this));
	}
	Quaternion Quaternion::getNormalized() const noexcept
	{
		auto length = getLength();

		if (length <= 0.0f)
			return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);

		return *this * (1.0f / length);
	}
	Quaternion Quaternion::getLookedAt(
		const Vector3& direction, const Vector3& up) const noexcept
	{
		auto c0 = up.getCrossProduct(direction) *
			(1.0f / std::sqrt(std::fmaxf(0.00001f, direction.getDotProduct(direction))));

		auto result = Matrix3(c0, direction.getCrossProduct(c0), direction);

		// TODO:
		return quat_cast(Result);
	}

	float Quaternion::getRoll() const noexcept
	{
		return std::atan2(2.0f * (x * y + w * z), w * w + x * x - y * y - z * z);
	}
	float Quaternion::getPitch() const noexcept
	{
		float _y = 2.0f * (y * z + w * x);
		float _x = w * w - x * x - y * y + z * z;

		if (std::abs(_y) <= std::numeric_limits<float>::epsilon() &&
			std::abs(_x) <= std::numeric_limits<float>::epsilon())
			return 2.0f * std::atan2(x, w);

		return std::atan2(y, x);
	}
	float Quaternion::getYaw() const noexcept
	{
		return std::asin(std::fminf(std::fmaxf(-2.0f * (x * z - w * y), -1.0f), 1.0f));
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
		return x != quaternion.x || y != quaternion.y ||
			z != quaternion.z || w != quaternion.w;
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

	Quaternion Quaternion::operator-(const Quaternion& vector) const noexcept
	{
		return Quaternion(x - vector.x, y - vector.y, z - vector.z, w - vector.w);
	}
	Quaternion Quaternion::operator+(const Quaternion& vector) const noexcept
	{
		return Quaternion(x + vector.x, y + vector.y, z + vector.z, w + vector.w);
	}
	Quaternion Quaternion::operator/(const Quaternion& vector) const noexcept
	{
		return Quaternion(x / vector.x, y / vector.y, z / vector.z, w / vector.w);
	}
	Quaternion Quaternion::operator*(const Quaternion& vector) const noexcept
	{
		return Quaternion(x * vector.x, y * vector.y, z * vector.z, w * vector.w);
	}
	Quaternion& Quaternion::operator-=(const Quaternion& vector) noexcept
	{
		x -= vector.x;
		y -= vector.y;
		z -= vector.z;
		w -= vector.w;
		return *this;
	}
	Quaternion& Quaternion::operator+=(const Quaternion& vector) noexcept
	{
		x += vector.x;
		y += vector.y;
		z += vector.z;
		w += vector.w;
		return *this;
	}
	Quaternion& Quaternion::operator/=(const Quaternion& vector) noexcept
	{
		x /= vector.x;
		y /= vector.y;
		z /= vector.z;
		w /= vector.w;
		return *this;
	}
	Quaternion& Quaternion::operator*=(const Quaternion& vector) noexcept
	{
		x *= vector.x;
		y *= vector.y;
		z *= vector.z;
		w *= vector.w;
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
}
