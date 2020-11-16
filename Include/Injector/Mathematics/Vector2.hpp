#pragma once
#include <sstream>

namespace Injector
{
	template<class T = float>
	struct Vector2 final
	{
		T x, y;

		Vector2() noexcept :
			x(static_cast<T>(0)),
			y(static_cast<T>(0))
		{
		}
		explicit Vector2(
			T xy) noexcept :
			x(xy),
			y(xy)
		{
		}
		Vector2(
			T _x,
			T _y) noexcept :
			x(_x),
			y(_y)
		{
		}

		std::string getString() const noexcept
		{
			auto ss = std::stringstream();
			ss << x << " " << y;
			return ss.str();
		}
		T getDotProduct(
			const Vector2<T>& vector) const noexcept
		{
			auto result = *this * vector;
			return result.x + result.y;
		}
		T getLength() const noexcept
		{
			return static_cast<T>(sqrt(
				getDotProduct(*this)));
		}
		T getDistance(
			const Vector2<T>& vector) const noexcept
		{
			return static_cast<T>(sqrt(
				getDotProduct(*this - vector)));
		}
		Vector2<T> getNormalized() const noexcept
		{
			return *this * (static_cast<T>(1) /
				static_cast<T>(sqrt(getDotProduct(*this))));
		}
		Vector2<T> getReflected(
			const Vector2<T>& normal) const noexcept
		{
			return *this - normal *
				getDotProduct(normal) * static_cast<T>(2);
		}
		Vector2<T> getRefracted(
			const Vector2<T>& normal,
			T eta) const noexcept
		{
			auto dot = getDotProduct(normal);

			auto k = (static_cast<T>(1) - eta * eta *
				(static_cast<T>(1) - dot * dot));

			return Vector2<T>(k >= static_cast<T>(0) ?
				(*this * eta - normal * (eta * dot + static_cast<T>(sqrt(k)))) :
				Vector2<T>());
		}
		Vector2<T> getSine() const noexcept
		{
			return Vector2<T>(
				static_cast<T>(sin(x)),
				static_cast<T>(sin(y)));
		}
		Vector2<T> getCosine() const noexcept
		{
			return Vector2<T>(
				static_cast<T>(cos(x)),
				static_cast<T>(cos(y)));
		}
		Vector2<T> getTangent() const noexcept
		{
			return Vector2<T>(
				static_cast<T>(tan(x)),
				static_cast<T>(tan(y)));
		}
		Vector2<T> getCotangent() const noexcept
		{
			return Vector2<T>(
				static_cast<T>(static_cast<T>(1) / tan(x)),
				static_cast<T>(static_cast<T>(1) / tan(y)));
		}

		bool operator==(
			const Vector2<T>& vector) const noexcept
		{
			return
				x == vector.x &&
				y == vector.y;
		}
		bool operator!=(
			const Vector2<T>& vector) const noexcept
		{
			return
				x != vector.x ||
				y != vector.y;
		}

		Vector2<T>& operator--() noexcept
		{
			--x;
			--y;
			return *this;
		}
		Vector2<T>& operator++() noexcept
		{
			++x;
			++y;
			return *this;
		}
		Vector2<T> operator--(int) noexcept
		{
			auto result =
				Vector2<T>(*this);

			--x;
			--y;
			return result;
		}
		Vector2<T> operator++(int) noexcept
		{
			auto result =
				Vector2<T>(*this);

			++x;
			++y;
			return result;
		}
		Vector2<T> operator-() const noexcept
		{
			return Vector2<T>(
				static_cast<T>(-x),
				static_cast<T>(-y));
		}

		Vector2<T> operator-(
			const Vector2<T>& vector) const noexcept
		{
			return Vector2<T>(
				x - vector.x,
				y - vector.y);
		}
		Vector2<T> operator+(
			const Vector2<T>& vector) const noexcept
		{
			return Vector2<T>(
				x + vector.x,
				y + vector.y);
		}
		Vector2<T> operator/(
			const Vector2<T>& vector) const noexcept
		{
			return Vector2<T>(
				x / vector.x,
				y / vector.y);
		}
		Vector2<T> operator*(
			const Vector2<T>& vector) const noexcept
		{
			return Vector2<T>(
				x * vector.x,
				y * vector.y);
		}
		Vector2<T>& operator-=(
			const Vector2<T>& vector) noexcept
		{
			x -= vector.x;
			y -= vector.y;
			return *this;
		}
		Vector2<T>& operator+=(
			const Vector2<T>& vector) noexcept
		{
			x += vector.x;
			y += vector.y;
			return *this;
		}
		Vector2<T>& operator/=(
			const Vector2<T>& vector) noexcept
		{
			x /= vector.x;
			y /= vector.y;
			return *this;
		}
		Vector2<T>& operator*=(
			const Vector2<T>& vector) noexcept
		{
			x *= vector.x;
			y *= vector.y;
			return *this;
		}

		Vector2<T> operator-(
			T value) const noexcept
		{
			return Vector2<T>(
				x - value,
				y - value);
		}
		Vector2<T> operator+(
			T value) const noexcept
		{
			return Vector2<T>(
				x + value,
				y + value);
		}
		Vector2<T> operator/(
			T value) const noexcept
		{
			return Vector2<T>(
				x / value,
				y / value);
		}
		Vector2<T> operator*(
			T value) const noexcept
		{
			return Vector2<T>(
				x * value,
				y * value);
		}
		Vector2<T>& operator-=(
			T value) noexcept
		{
			x -= value;
			y -= value;
			return *this;
		}
		Vector2<T>& operator+=(
			T value) noexcept
		{
			x += value;
			y += value;
			return *this;
		}
		Vector2<T>& operator/=(
			T value) noexcept
		{
			x /= value;
			y /= value;
			return *this;
		}
		Vector2<T>& operator*=(
			T value) noexcept
		{
			x *= value;
			y *= value;
			return *this;
		}

		struct Less
		{
			bool operator()(
				const Vector2<T>& a,
				const Vector2<T>& b) const noexcept
			{
				return std::tie(a.x, a.y) <
					std::tie(b.x, b.y);
			}
		};
	};

	using FloatVector2 = Vector2<float>;
	using DoubleVector2 = Vector2<double>;
	using CharVector2 = Vector2<char>;
	using ByteVector2 = Vector2<uint8_t>;
	using SbyteVector2 = Vector2<int8_t>;
	using ShortVector2 = Vector2<int16_t>;
	using UshortVector2 = Vector2<uint16_t>;
	using IntVector2 = Vector2<int32_t>;
	using UintVector2 = Vector2<uint32_t>;
	using LongVector2 = Vector2<int64_t>;
	using UlongVector2 = Vector2<uint64_t>;
}
