#pragma once
#include "Vector2.hpp"

namespace Injector
{
	template<class T = float>
	struct Vector3 final
	{
		T x, y, z;

		Vector3() noexcept :
			x(static_cast<T>(0)),
			y(static_cast<T>(0)),
			z(static_cast<T>(0))
		{
		}
		explicit Vector3(
			T xyz) noexcept :
			x(xyz),
			y(xyz),
			z(xyz)
		{
		}
		Vector3(
			T _x,
			T _y,
			T _z) noexcept :
			x(_x),
			y(_y),
			z(_z)
		{
		}
		Vector3(
			const Vector2<T>& vector,
			T _z) noexcept :
			x(vector.x),
			y(vector.y),
			z(_z)
		{
		}
		Vector3(
			T _x,
			const Vector2<T>& vector) noexcept :
			x(_x),
			y(vector.x),
			z(vector.y)
		{
		}

		std::string getString() const noexcept
		{
			auto ss = std::stringstream();
			ss << x << " " << y << " " << z;
			return ss.str();
		}
		T getDotProduct(
			const Vector3<T>& vector) const noexcept
		{
			auto result = *this * vector;
			return result.x + result.y + result.z;
		}
		Vector3<T> getCrossProduct(
			const Vector3<T>& vector) const noexcept
		{
			return Vector3<T>(
				y * vector.z - z * vector.y,
				z * vector.x - x * vector.z,
				x * vector.y - y * vector.x);
		}
		T getLength() const noexcept
		{
			return static_cast<T>(sqrt(
				getDotProduct(*this)));
		}
		T getDistance(
			const Vector3<T>& vector) const noexcept
		{
			return static_cast<T>(sqrt(
				getDotProduct(*this - vector)));
		}
		Vector3<T> getNormalized() const noexcept
		{
			return *this * (static_cast<T>(1) /
				static_cast<T>(sqrt(getDotProduct(*this))));
		}
		Vector3<T> getReflected(
			const Vector3<T>& normal) const noexcept
		{
			return *this - normal *
				getDotProduct(normal) * static_cast<T>(2);
		}
		Vector3<T> getRefracted(
			const Vector3<T>& normal,
			T eta) const noexcept
		{
			auto dot = getDotProduct(normal);

			auto k = (static_cast<T>(1) - eta * eta *
				(static_cast<T>(1) - dot * dot));

			return Vector3<T>(k >= static_cast<T>(0) ?
				(*this * eta - normal * (eta * dot + static_cast<T>(sqrt(k)))) :
				Vector3<T>());
		}
		Vector3<T> getSine() const noexcept
		{
			return Vector3<T>(
				static_cast<T>(sin(x)),
				static_cast<T>(sin(y)),
				static_cast<T>(sin(z)));
		}
		Vector3<T> getCosine() const noexcept
		{
			return Vector3<T>(
				static_cast<T>(cos(x)),
				static_cast<T>(cos(y)),
				static_cast<T>(cos(z)));
		}
		Vector3<T> getTangent() const noexcept
		{
			return Vector3<T>(
				static_cast<T>(tan(x)),
				static_cast<T>(tan(y)),
				static_cast<T>(tan(z)));
		}
		Vector3<T> getCotangent() const noexcept
		{
			return Vector3<T>(
				static_cast<T>(static_cast<T>(1) / tan(x)),
				static_cast<T>(static_cast<T>(1) / tan(y)),
				static_cast<T>(static_cast<T>(1) / tan(z)));
		}

		bool operator==(
			const Vector3<T>& vector) const noexcept
		{
			return
				x == vector.x &&
				y == vector.y &&
				z == vector.z;
		}
		bool operator!=(
			const Vector3<T>& vector) const noexcept
		{
			return
				x != vector.x ||
				y != vector.y ||
				z != vector.z;
		}

		Vector3<T>& operator--() noexcept
		{
			--x;
			--y;
			--z;
			return *this;
		}
		Vector3<T>& operator++() noexcept
		{
			++x;
			++y;
			++z;
			return *this;
		}
		Vector3<T> operator--(int) noexcept
		{
			auto result =
				Vector3<T>(*this);

			--x;
			--y;
			--z;
			return result;
		}
		Vector3<T> operator++(int) noexcept
		{
			auto result =
				Vector3<T>(*this);

			++x;
			++y;
			++z;
			return result;
		}
		Vector3<T> operator-() const noexcept
		{
			return Vector3<T>(
				static_cast<T>(-x),
				static_cast<T>(-y),
				static_cast<T>(-z));
		}

		Vector3<T> operator-(
			const Vector3<T>& vector) const noexcept
		{
			return Vector3<T>(
				x - vector.x,
				y - vector.y,
				z - vector.z);
		}
		Vector3<T> operator+(
			const Vector3<T>& vector) const noexcept
		{
			return Vector3<T>(
				x + vector.x,
				y + vector.y,
				z + vector.z);
		}
		Vector3<T> operator/(
			const Vector3<T>& vector) const noexcept
		{
			return Vector3<T>(
				x / vector.x,
				y / vector.y,
				z / vector.z);
		}
		Vector3<T> operator*(
			const Vector3<T>& vector) const noexcept
		{
			return Vector3<T>(
				x * vector.x,
				y * vector.y,
				z * vector.z);
		}
		Vector3<T>& operator-=(
			const Vector3<T>& vector) noexcept
		{
			x -= vector.x;
			y -= vector.y;
			z -= vector.z;
			return *this;
		}
		Vector3<T>& operator+=(
			const Vector3<T>& vector) noexcept
		{
			x += vector.x;
			y += vector.y;
			z += vector.z;
			return *this;
		}
		Vector3<T>& operator/=(
			const Vector3<T>& vector) noexcept
		{
			x /= vector.x;
			y /= vector.y;
			z /= vector.z;
			return *this;
		}
		Vector3<T>& operator*=(
			const Vector3<T>& vector) noexcept
		{
			x *= vector.x;
			y *= vector.y;
			z *= vector.z;
			return *this;
		}

		Vector3<T> operator-(
			T value) const noexcept
		{
			return Vector3<T>(
				x - value,
				y - value,
				z - value);
		}
		Vector3<T> operator+(
			T value) const noexcept
		{
			return Vector3<T>(
				x + value,
				y + value,
				z + value);
		}
		Vector3<T> operator/(
			T value) const noexcept
		{
			return Vector3<T>(
				x / value,
				y / value,
				z / value);
		}
		Vector3<T> operator*(
			T value) const noexcept
		{
			return Vector3<T>(
				x * value,
				y * value,
				z * value);
		}
		Vector3<T>& operator-=(
			T value) noexcept
		{
			x -= value;
			y -= value;
			z -= value;
			return *this;
		}
		Vector3<T>& operator+=(
			T value) noexcept
		{
			x += value;
			y += value;
			z += value;
			return *this;
		}
		Vector3<T>& operator/=(
			T value) noexcept
		{
			x /= value;
			y /= value;
			z /= value;
			return *this;
		}
		Vector3<T>& operator*=(
			T value) noexcept
		{
			x *= value;
			y *= value;
			z *= value;
			return *this;
		}

		struct Less
		{
			bool operator()(
				const Vector3<T>& a,
				const Vector3<T>& b) const noexcept
			{
				return std::tie(a.x, a.y, a.z) <
					std::tie(b.x, b.y, b.z);
			}
		};
	};

	using FloatVector3 = Vector3<float>;
	using DoubleVector3 = Vector3<double>;
	using CharVector3 = Vector3<char>;
	using ByteVector3 = Vector3<uint8_t>;
	using SbyteVector3 = Vector3<int8_t>;
	using ShortVector3 = Vector3<int16_t>;
	using UshortVector3 = Vector3<uint16_t>;
	using IntVector3 = Vector3<int32_t>;
	using UintVector3 = Vector3<uint32_t>;
	using LongVector3 = Vector3<int64_t>;
	using UlongVector3 = Vector3<uint64_t>;
}
