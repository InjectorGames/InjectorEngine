#include <injector/vector4.hpp>
#include <cmath>

namespace INJECTOR_NAMESPACE
{
	Vector4::Vector4() :
		x(0.0f), y(0.0f), z(0.0f), w(0.0f)
	{}
	Vector4::Vector4(float _x, float _y, float _z, float _w) :
		x(_x), y(_y), z(_z), w(_w)
	{}
	Vector4::Vector4(const Vector2& other, float _z, float _w) :
		x(other.x), y(other.y), z(_z), w(_w)
	{}
	Vector4::Vector4(float _x, const Vector2& other, float _w) :
		x(_x), y(other.x), z(other.y), w(_w)
	{}
	Vector4::Vector4(float _x, float _y, const Vector2& other) :
		x(_x), y(_y), z(other.x), w(other.y)
	{}
	Vector4::Vector4(const Vector3& other, float _w) :
		x(other.x), y(other.y), z(other.z), w(_w)
	{}
	Vector4::Vector4(float _x, const Vector3& other) :
		x(_x), y(other.x), z(other.y), w(other.z)
	{}
	Vector4::Vector4(const IntVector4& other) :
		x(static_cast<float>(other.x)),
		y(static_cast<float>(other.y)),
		z(static_cast<float>(other.z)),
		w(static_cast<float>(other.w))
	{}
	Vector4::Vector4(const IntVector2& other, float _z, float _w) :
		x(static_cast<float>(other.x)),
		y(static_cast<float>(other.y)),
		z(_z),
		w(_w)
	{}
	Vector4::Vector4(float _x, const IntVector2& other, float _w) :
		x(_x),
		y(static_cast<float>(other.x)),
		z(static_cast<float>(other.y)),
		w(_w)
	{}
	Vector4::Vector4(float _x, float _y, const IntVector2& other) :
		x(_x),
		y(_y),
		z(static_cast<float>(other.x)),
		w(static_cast<float>(other.y))
	{}
	Vector4::Vector4(const IntVector3& other, float _w) :
		x(static_cast<float>(other.x)),
		y(static_cast<float>(other.y)),
		z(static_cast<float>(other.z)),
		w(_w)
	{}
	Vector4::Vector4(float _x, const IntVector3& other) :
		x(_x),
		y(static_cast<float>(other.x)),
		z(static_cast<float>(other.y)),
		w(static_cast<float>(other.z))
	{}

	float Vector4::getMagnitude() const noexcept
	{
		return std::sqrtf(x * x + y * y + z * z + w * w);
	}
	float Vector4::getDot(const Vector4& other) const noexcept
	{
		return x * other.x + y * other.y + z * other.z + w * other.w;
	}
	float Vector4::getDistance(const Vector4& other) const noexcept
	{
		return  std::sqrtf(
			x - other.x * x - other.x +
			y - other.y * y - other.y +
			z - other.z * z - other.z +
			w - other.w * w - other.w);
	}
	Vector4 Vector4::getNegative() const noexcept
	{
		return Vector4(-x, -y, -z, -w);
	}
	Vector4 Vector4::getNormalized() const noexcept
	{
		auto magnitude = 1.0f / getMagnitude();
		return Vector4(x * magnitude, y * magnitude, z * magnitude, w * magnitude);
	}
	Vector4 Vector4::getSine() const noexcept
	{
		return Vector4(std::sinf(x), std::sinf(y), std::sinf(z), std::sinf(w));
	}
	Vector4 Vector4::getCosine() const noexcept
	{
		return Vector4(std::cosf(x), std::cosf(y), std::cosf(z), std::cosf(w));
	}
	Vector4 Vector4::getTangent() const noexcept
	{
		return Vector4(std::tanf(x), std::tanf(y), std::tanf(z), std::tanf(w));
	}
	Vector4 Vector4::getCotangent() const noexcept
	{
		return Vector4(1.0f / std::tanf(x), 1.0f / std::tanf(y),
			1.0f / std::tanf(z), 1.0f / std::tanf(w));
	}

	bool Vector4::operator==(const Vector4& other) const noexcept
	{
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}
	bool Vector4::operator!=(const Vector4& other) const noexcept
	{
		return x != other.x || y != other.y || z != other.z || w != other.w;
	}

	Vector4& Vector4::operator--() noexcept
	{
		--x;
		--y;
		--z;
		--w;
		return *this;
	}
	Vector4& Vector4::operator++() noexcept
	{
		++x;
		++y;
		++z;
		++w;
		return *this;
	}
	Vector4 Vector4::operator--(int) noexcept
	{
		auto result = Vector4(*this);
		--x;
		--y;
		--z;
		--w;
		return result;
	}
	Vector4 Vector4::operator++(int) noexcept
	{
		auto result = Vector4(*this);
		++x;
		++y;
		++z;
		++w;
		return result;
	}

	Vector4 Vector4::operator-(const Vector4& other) const noexcept
	{
		return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
	}
	Vector4 Vector4::operator+(const Vector4& other) const noexcept
	{
		return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
	}
	Vector4 Vector4::operator/(const Vector4& other) const noexcept
	{
		return Vector4(x / other.x, y / other.y, z / other.z, w / other.w);
	}
	Vector4 Vector4::operator*(const Vector4& other) const noexcept
	{
		return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
	}
	Vector4& Vector4::operator=(const Vector4& other) noexcept
	{
		x = other.x;
		y = other.y;
		z = other.z;
		w = other.w;
		return *this;
	}
	Vector4& Vector4::operator-=(const Vector4& other) noexcept
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}
	Vector4& Vector4::operator+=(const Vector4& other) noexcept
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}
	Vector4& Vector4::operator/=(const Vector4& other) noexcept
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;
		return *this;
	}
	Vector4& Vector4::operator*=(const Vector4& other) noexcept
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;
		return *this;
	}

	Vector4 Vector4::operator-(const IntVector4& other) const noexcept
	{
		return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
	}
	Vector4 Vector4::operator+(const IntVector4& other) const noexcept
	{
		return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
	}
	Vector4 Vector4::operator/(const IntVector4& other) const noexcept
	{
		return Vector4(x / other.x, y / other.y, z / other.z, w / other.w);
	}
	Vector4 Vector4::operator*(const IntVector4& other) const noexcept
	{
		return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
	}
	Vector4& Vector4::operator=(const IntVector4& other) noexcept
	{
		x = static_cast<float>(other.x);
		y = static_cast<float>(other.y);
		z = static_cast<float>(other.z);
		w = static_cast<float>(other.w);
		return *this;
	}
	Vector4& Vector4::operator-=(const IntVector4& other) noexcept
	{
		x -= static_cast<float>(other.x);
		y -= static_cast<float>(other.y);
		z -= static_cast<float>(other.z);
		w -= static_cast<float>(other.w);
		return *this;
	}
	Vector4& Vector4::operator+=(const IntVector4& other) noexcept
	{
		x += static_cast<float>(other.x);
		y += static_cast<float>(other.y);
		z += static_cast<float>(other.z);
		w += static_cast<float>(other.w);
		return *this;
	}
	Vector4& Vector4::operator/=(const IntVector4& other) noexcept
	{
		x /= static_cast<float>(other.x);
		y /= static_cast<float>(other.y);
		z /= static_cast<float>(other.z);
		w /= static_cast<float>(other.w);
		return *this;
	}
	Vector4& Vector4::operator*=(const IntVector4& other) noexcept
	{
		x *= static_cast<float>(other.x);
		y *= static_cast<float>(other.y);
		z *= static_cast<float>(other.z);
		w *= static_cast<float>(other.w);
		return *this;
	}

	Vector4 Vector4::operator-(float value) const noexcept
	{
		return Vector4(x - value, y - value, z - value, w - value);
	}
	Vector4 Vector4::operator+(float value) const noexcept
	{
		return Vector4(x + value, y + value, z + value, w + value);
	}
	Vector4 Vector4::operator/(float value) const noexcept
	{
		return Vector4(x / value, y / value, z / value, w / value);
	}
	Vector4 Vector4::operator*(float value) const noexcept
	{
		return Vector4(x * value, y * value, z * value, w * value);
	}
	Vector4& Vector4::operator=(float value) noexcept
	{
		x = value;
		y = value;
		z = value;
		w = value;
		return *this;
	}
	Vector4& Vector4::operator-=(float value) noexcept
	{
		x -= value;
		y -= value;
		z -= value;
		w -= value;
		return *this;
	}
	Vector4& Vector4::operator+=(float value) noexcept
	{
		x += value;
		y += value;
		z += value;
		w += value;
		return *this;
	}
	Vector4& Vector4::operator/=(float value) noexcept
	{
		x /= value;
		y /= value;
		z /= value;
		w /= value;
		return *this;
	}
	Vector4& Vector4::operator*=(float value) noexcept
	{
		x *= value;
		y *= value;
		z *= value;
		w *= value;
		return *this;
	}

	const Vector4 Vector4::zero = Vector4(0.0f, 0.0f, 0.0f, 0.0f);
	const Vector4 Vector4::minusOne = Vector4(-1.0f, -1.0f, -1.0f, -1.0f);
	const Vector4 Vector4::one = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
}
