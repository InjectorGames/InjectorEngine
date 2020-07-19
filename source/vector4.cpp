#include <injector/vector4.hpp>

#include <cmath>

namespace INJECTOR_NAMESPACE
{
	Vector4::Vector4(float _x, float _y, float _z, float _w) :
		x(_x), y(_y), z(_z), w(_w)
	{}
	Vector4::Vector4(const IntVector4& other) :
		x(static_cast<float>(other.x)),
		y(static_cast<float>(other.y)), 
		z(static_cast<float>(other.z)),
		w(static_cast<float>(other.w))
	{}
	Vector4::Vector4(const Vector2& other, float _z, float _w) :
		x(other.x), y(other.y), z(_z), w(_w)
	{}
	Vector4::Vector4(const IntVector2& other, float _z, float _w) :
		x(static_cast<float>(other.x)),
		y(static_cast<float>(other.y)),
		z(_z), w(_w)
	{}
	Vector4::Vector4(const Vector3& other, float _w) :
		x(other.x), y(other.y), z(other.z), w(_w)
	{}
	Vector4::Vector4(const IntVector3& other, float _w) :
		x(static_cast<float>(other.x)),
		y(static_cast<float>(other.y)),
		z(static_cast<float>(other.z)),
		w(_w)
	{}

	float Vector4::getMagnitude()
	{
		return std::sqrtf(x * x + y * y + z * z + w * w);
	}
	float Vector4::getDot(const Vector4& other)
	{
		return x * other.x + y * other.y + z * other.z + w * other.w;
	}
	float Vector4::getDistance(const Vector4& other)
	{
		return  std::sqrtf(
			x - other.x * x - other.x +
			y - other.y * y - other.y +
			z - other.z * z - other.z +
			w - other.w * w - other.w);
	}

	bool Vector4::operator==(const Vector4& other)
	{
		return x == other.x && y == other.y && z == other.z && w == other.w;
	}
	bool Vector4::operator!=(const Vector4& other)
	{
		return x != other.x && y != other.y && z != other.z && w != other.w;
	}

	Vector4& Vector4::operator--()
	{
		--x;
		--y;
		--z;
		--w;
		return *this;
	}
	Vector4& Vector4::operator++()
	{
		++x;
		++y;
		++z;
		++w;
		return *this;
	}
	Vector4 Vector4::operator--(int)
	{
		auto result = Vector4(*this);
		--x;
		--y;
		--z;
		--w;
		return result;
	}
	Vector4 Vector4::operator++(int)
	{
		auto result = Vector4(*this);
		++x;
		++y;
		++z;
		++w;
		return result;
	}

	Vector4 Vector4::operator-(const Vector4& other)
	{
		return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
	}
	Vector4 Vector4::operator+(const Vector4& other)
	{
		return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
	}
	Vector4 Vector4::operator/(const Vector4& other)
	{
		return Vector4(x / other.x, y / other.y, z / other.z, w / other.w);
	}
	Vector4 Vector4::operator*(const Vector4& other)
	{
		return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
	}
	Vector4& Vector4::operator-=(const Vector4& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}
	Vector4& Vector4::operator+=(const Vector4& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}
	Vector4& Vector4::operator/=(const Vector4& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;
		return *this;
	}
	Vector4& Vector4::operator*=(const Vector4& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;
		return *this;
	}

	Vector4 Vector4::operator-(const IntVector4& other)
	{
		return Vector4(x - other.x, y - other.y, z - other.z, w - other.w);
	}
	Vector4 Vector4::operator+(const IntVector4& other)
	{
		return Vector4(x + other.x, y + other.y, z + other.z, w + other.w);
	}
	Vector4 Vector4::operator/(const IntVector4& other)
	{
		return Vector4(x / other.x, y / other.y, z / other.z, w / other.w);
	}
	Vector4 Vector4::operator*(const IntVector4& other)
	{
		return Vector4(x * other.x, y * other.y, z * other.z, w * other.w);
	}
	Vector4& Vector4::operator-=(const IntVector4& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;
		w -= other.w;
		return *this;
	}
	Vector4& Vector4::operator+=(const IntVector4& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;
		w += other.w;
		return *this;
	}
	Vector4& Vector4::operator/=(const IntVector4& other)
	{
		x /= other.x;
		y /= other.y;
		z /= other.z;
		w /= other.w;
		return *this;
	}
	Vector4& Vector4::operator*=(const IntVector4& other)
	{
		x *= other.x;
		y *= other.y;
		z *= other.z;
		w *= other.w;
		return *this;
	}

	Vector4 Vector4::operator-(float value)
	{
		return Vector4(x - value, y - value, z - value, w - value);
	}
	Vector4 Vector4::operator+(float value)
	{
		return Vector4(x + value, y + value, z + value, w + value);
	}
	Vector4 Vector4::operator/(float value)
	{
		return Vector4(x / value, y / value, z / value, w / value);
	}
	Vector4 Vector4::operator*(float value)
	{
		return Vector4(x * value, y * value, z * value, w * value);
	}
	Vector4& Vector4::operator-=(float value)
	{
		x -= value;
		y -= value;
		z -= value;
		w -= value;
		return *this;
	}
	Vector4& Vector4::operator+=(float value)
	{
		x += value;
		y += value;
		z += value;
		w += value;
		return *this;
	}
	Vector4& Vector4::operator/=(float value)
	{
		x /= value;
		y /= value;
		z /= value;
		w /= value;
		return *this;
	}
	Vector4& Vector4::operator*=(float value)
	{
		x *= value;
		y *= value;
		z *= value;
		w *= value;
		return *this;
	}
}
