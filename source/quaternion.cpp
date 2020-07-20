#include <injector/quaternion.hpp>
#include <cmath>

namespace INJECTOR_NAMESPACE
{
	Quaternion::Quaternion() :
		x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{}
	Quaternion::Quaternion(float _x, float _y, float _z, float _w) :
		x(_x), y(_y), z(_z), w(_w)
	{}
	Quaternion::Quaternion(const Vector3& other, float _w) :
		x(other.x), y(other.y), z(other.z), w(_w)
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

	bool Quaternion::operator==(const Quaternion& other) const noexcept
	{
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}
	bool Quaternion::operator!=(const Quaternion& other) const noexcept
	{
		return x != other.x || y != other.y || z != other.z || w != other.w;
	}

	float Quaternion::getMagnitude() const noexcept
	{
		return std::sqrtf(x * x + y * y + z * z + w * w);
	}
	float Quaternion::getDot(const Quaternion& other) const noexcept
	{
		return x * other.x + y * other.y + z * other.z + w * other.w;
	}
	Quaternion Quaternion::getNormalized() const noexcept
	{
		auto magnitude = getMagnitude();

		if (magnitude <= 0.0f)
			return Quaternion(0.0f, 0.0f, 0.0f, 1.0f);

		magnitude = 1.0f / magnitude;
		return Quaternion(x * magnitude, y * magnitude, z * magnitude, w * magnitude);
	}
	Quaternion Quaternion::getCross(const Quaternion& other) const noexcept
	{
		return Quaternion(
			w * other.x + x * other.w + y * other.z - z * other.y,
			w * other.y + y * other.w + z * other.x - x * other.z,
			w * other.z + z * other.w + x * other.y - y * other.x,
			w * other.w - x * other.x - y * other.y - z * other.z);
	}
}
