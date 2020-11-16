#pragma once
#include "Vector3.hpp"

namespace Injector
{
	template<class T = float>
	struct Vector4 final
	{
		T x, y, z, w;

		Vector4() noexcept :
			x(static_cast<T>(0)),
			y(static_cast<T>(0)),
			z(static_cast<T>(0)),
			w(static_cast<T>(0))
		{
		}
		explicit Vector4(
			T xyzw) noexcept :
			x(xyzw),
			y(xyzw),
			z(xyzw),
			w(xyzw)
		{
		}
		Vector4(
			T _x,
			T _y,
			T _z,
			T _w) noexcept :
			x(_x),
			y(_y),
			z(_z),
			w(_w)
		{
		}
		Vector4(
			const Vector3<T>& vector,
			T _w) noexcept :
			x(vector.x),
			y(vector.y),
			z(vector.z),
			w(_w)
		{
		}
		Vector4(
			T _x,
			const Vector3<T>& vector) noexcept :
			x(_x),
			y(vector.x),
			z(vector.y),
			w(vector.z)
		{
		}
		Vector4(
			const Vector2<T>& vector,
			T _z,
			T _w) noexcept :
			x(vector.x),
			y(vector.y),
			z(_z),
			w(_w)
		{
		}
		Vector4(
			T _x,
			const Vector2<T>& vector,
			T _w) noexcept :
			x(_x),
			y(vector.x),
			z(vector.y),
			w(_w)
		{
		}
		Vector4(
			T _x,
			T _y,
			const Vector2<T>& vector) noexcept :
			x(_x),
			y(_y),
			z(vector.x),
			w(vector.y)
		{
		}

		std::string getString() const noexcept
		{
			auto ss = std::stringstream();
			ss << x << " " << y << " " << z << " " << w;
			return ss.str();
		}
		T getDotProduct(
			const Vector4<T>& vector) const noexcept
		{
			auto result = *this * vector;
			return result.x + result.y + result.z;
		}
		T getLength() const noexcept
		{
			return static_cast<T>(sqrt(
				getDotProduct(*this)));
		}
		T getDistance(
			const Vector4<T>& vector) const noexcept
		{
			return static_cast<T>(sqrt(
				getDotProduct(*this - vector)));
		}
		Vector4<T> getNormalized() const noexcept
		{
			return *this * (static_cast<T>(1) /
				static_cast<T>(sqrt(getDotProduct(*this))));
		}
		Vector4<T> getReflected(
			const Vector4<T>& normal) const noexcept
		{
			return *this - normal *
				getDotProduct(normal) * static_cast<T>(2);
		}
		Vector4<T> getRefracted(
			const Vector4<T>& normal,
			T eta) const noexcept
		{
			auto dot = getDotProduct(normal);

			auto k = (static_cast<T>(1) - eta * eta *
				(static_cast<T>(1) - dot * dot));

			return Vector4<T>(k >= static_cast<T>(0) ?
				(*this * eta - normal * (eta * dot + static_cast<T>(sqrt(k)))) :
				Vector4<T>());
		}
		Vector4<T> getSine() const noexcept
		{
			return Vector4<T>(
				static_cast<T>(sin(x)),
				static_cast<T>(sin(y)),
				static_cast<T>(sin(z)),
				static_cast<T>(sin(w)));
		}
		Vector4<T> getCosine() const noexcept
		{
			return Vector4<T>(
				static_cast<T>(cos(x)),
				static_cast<T>(cos(y)),
				static_cast<T>(cos(z)),
				static_cast<T>(cos(w)));
		}
		Vector4<T> getTangent() const noexcept
		{
			return Vector4<T>(
				static_cast<T>(tan(x)),
				static_cast<T>(tan(y)),
				static_cast<T>(tan(z)),
				static_cast<T>(tan(w)));
		}
		Vector4<T> getCotangent() const noexcept
		{
			return Vector4<T>(
				static_cast<T>(static_cast<T>(1) / tan(x)),
				static_cast<T>(static_cast<T>(1) / tan(y)),
				static_cast<T>(static_cast<T>(1) / tan(z)),
				static_cast<T>(static_cast<T>(1) / tan(w)));
		}

		bool operator==(
			const Vector4<T>& vector) const noexcept
		{
			return
				x == vector.x &&
				y == vector.y &&
				z == vector.z &&
				w == vector.w;
		}
		bool operator!=(
			const Vector4<T>& vector) const noexcept
		{
			return
				x != vector.x ||
				y != vector.y ||
				z != vector.z ||
				w != vector.w;
		}

		Vector4<T>& operator--() noexcept
		{
			--x;
			--y;
			--z;
			--w;
			return *this;
		}
		Vector4<T>& operator++() noexcept
		{
			++x;
			++y;
			++z;
			++w;
			return *this;
		}
		Vector4<T> operator--(int) noexcept
		{
			auto result =
				Vector4<T>(*this);

			--x;
			--y;
			--z;
			--w;
			return result;
		}
		Vector4<T> operator++(int) noexcept
		{
			auto result =
				Vector4<T>(*this);

			++x;
			++y;
			++z;
			++w;
			return result;
		}
		Vector4<T> operator-() const noexcept
		{
			return Vector4<T>(
				static_cast<T>(-x),
				static_cast<T>(-y),
				static_cast<T>(-z),
				static_cast<T>(-w));
		}

		Vector4<T> operator-(
			const Vector4<T>& vector) const noexcept
		{
			return Vector4<T>(
				x - vector.x,
				y - vector.y,
				z - vector.z,
				w - vector.w);
		}
		Vector4<T> operator+(
			const Vector4<T>& vector) const noexcept
		{
			return Vector4<T>(
				x + vector.x,
				y + vector.y,
				z + vector.z,
				w + vector.w);
		}
		Vector4<T> operator/(
			const Vector4<T>& vector) const noexcept
		{
			return Vector4<T>(
				x / vector.x,
				y / vector.y,
				z / vector.z,
				w / vector.w);
		}
		Vector4<T> operator*(
			const Vector4<T>& vector) const noexcept
		{
			return Vector4<T>(
				x * vector.x,
				y * vector.y,
				z * vector.z,
				w * vector.w);
		}
		Vector4<T>& operator-=(
			const Vector4<T>& vector) noexcept
		{
			x -= vector.x;
			y -= vector.y;
			z -= vector.z;
			w -= vector.w;
			return *this;
		}
		Vector4<T>& operator+=(
			const Vector4<T>& vector) noexcept
		{
			x += vector.x;
			y += vector.y;
			z += vector.z;
			w += vector.w;
			return *this;
		}
		Vector4<T>& operator/=(
			const Vector4<T>& vector) noexcept
		{
			x /= vector.x;
			y /= vector.y;
			z /= vector.z;
			w /= vector.w;
			return *this;
		}
		Vector4<T>& operator*=(
			const Vector4<T>& vector) noexcept
		{
			x *= vector.x;
			y *= vector.y;
			z *= vector.z;
			w *= vector.w;
			return *this;
		}

		Vector4<T> operator-(
			T value) const noexcept
		{
			return Vector4<T>(
				x - value,
				y - value,
				z - value,
				w - value);
		}
		Vector4<T> operator+(
			T value) const noexcept
		{
			return Vector4<T>(
				x + value,
				y + value,
				z + value,
				w + value);
		}
		Vector4<T> operator/(
			T value) const noexcept
		{
			return Vector4<T>(
				x / value,
				y / value,
				z / value,
				w / value);
		}
		Vector4<T> operator*(
			T value) const noexcept
		{
			return Vector4<T>(
				x * value,
				y * value,
				z * value,
				w * value);
		}
		Vector4<T>& operator-=(
			T value) noexcept
		{
			x -= value;
			y -= value;
			z -= value;
			w -= value;
			return *this;
		}
		Vector4<T>& operator+=(
			T value) noexcept
		{
			x += value;
			y += value;
			z += value;
			w += value;
			return *this;
		}
		Vector4<T>& operator/=(
			T value) noexcept
		{
			x /= value;
			y /= value;
			z /= value;
			w /= value;
			return *this;
		}
		Vector4<T>& operator*=(
			T value) noexcept
		{
			x *= value;
			y *= value;
			z *= value;
			w *= value;
			return *this;
		}

		struct Less
		{
			bool operator()(
				const Vector4<T>& a,
				const Vector4<T>& b) const noexcept
			{
				return std::tie(a.x, a.y, a.z, a.w) <
					std::tie(b.x, b.y, b.z, b.w);
			}
		};
	};

	using FloatVector4 = Vector4<float>;
	using DoubleVector4 = Vector4<double>;
	using CharVector4 = Vector4<char>;
	using ByteVector4 = Vector4<uint8_t>;
	using SbyteVector4 = Vector4<int8_t>;
	using ShortVector4 = Vector4<int16_t>;
	using UshortVector4 = Vector4<uint16_t>;
	using IntVector4 = Vector4<int32_t>;
	using UintVector4 = Vector4<uint32_t>;
	using LongVector4 = Vector4<int64_t>;
	using UlongVector4 = Vector4<uint64_t>;
}
