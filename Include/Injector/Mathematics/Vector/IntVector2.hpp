#pragma once
#include <string>

namespace Injector
{
	struct IntVector2 final
	{
		int x, y;

		IntVector2() noexcept;
		explicit IntVector2(int xy) noexcept;
		IntVector2(int x, int y) noexcept;

		std::string getString() const noexcept;
		int getDotProduct(const IntVector2& vector) const noexcept;
		float getLength() const noexcept;
		float getDistance(const IntVector2& vector) const noexcept;
		IntVector2 getReflected(const IntVector2& normal) const noexcept;

		bool operator==(const IntVector2& vector) const noexcept;
		bool operator!=(const IntVector2& vector) const noexcept;

		IntVector2& operator--() noexcept;
		IntVector2& operator++() noexcept;
		IntVector2 operator--(int) noexcept;
		IntVector2 operator++(int) noexcept;
		IntVector2 operator-() const noexcept;

		IntVector2 operator-(const IntVector2& vector) const noexcept;
		IntVector2 operator+(const IntVector2& vector) const noexcept;
		IntVector2 operator/(const IntVector2& vector) const noexcept;
		IntVector2 operator*(const IntVector2& vector) const noexcept;
		IntVector2 operator%(const IntVector2& vector) const noexcept;
		IntVector2 operator|(const IntVector2& vector) const noexcept;
		IntVector2 operator&(const IntVector2& vector) const noexcept;
		IntVector2 operator^(const IntVector2& vector) const noexcept;
		IntVector2 operator<<(const IntVector2& vector) const noexcept;
		IntVector2 operator>>(const IntVector2& vector) const noexcept;
		IntVector2& operator-=(const IntVector2& vector) noexcept;
		IntVector2& operator+=(const IntVector2& vector) noexcept;
		IntVector2& operator/=(const IntVector2& vector) noexcept;
		IntVector2& operator*=(const IntVector2& vector) noexcept;
		IntVector2& operator%=(const IntVector2& vector) noexcept;
		IntVector2& operator|=(const IntVector2& vector) noexcept;
		IntVector2& operator&=(const IntVector2& vector) noexcept;
		IntVector2& operator^=(const IntVector2& vector) noexcept;
		IntVector2& operator<<=(const IntVector2& vector) noexcept;
		IntVector2& operator>>=(const IntVector2& vector) noexcept;

		IntVector2 operator-(int value) const noexcept;
		IntVector2 operator+(int value) const noexcept;
		IntVector2 operator/(int value) const noexcept;
		IntVector2 operator*(int value) const noexcept;
		IntVector2 operator%(int value) const noexcept;
		IntVector2 operator|(int value) const noexcept;
		IntVector2 operator&(int value) const noexcept;
		IntVector2 operator^(int value) const noexcept;
		IntVector2 operator<<(int value) const noexcept;
		IntVector2 operator>>(int value) const noexcept;
		IntVector2& operator-=(int value) noexcept;
		IntVector2& operator+=(int value) noexcept;
		IntVector2& operator/=(int value) noexcept;
		IntVector2& operator*=(int value) noexcept;
		IntVector2& operator%=(int value) noexcept;
		IntVector2& operator|=(int value) noexcept;
		IntVector2& operator&=(int value) noexcept;
		IntVector2& operator^=(int value) noexcept;
		IntVector2& operator<<=(int value) noexcept;
		IntVector2& operator>>=(int value) noexcept;

		// (0, 0)
		static const IntVector2 zero;
		// (-1, -1)
		static const IntVector2 minusOne;
		// (1, 1)
		static const IntVector2 one;
		// (INT32_MIN, INT32_MIN)
		static const IntVector2 minimum;
		// (INT32_MAX, INT32_MAX)
		static const IntVector2 maximum;

		static bool less(
			const IntVector2& a,
			const IntVector2& b) noexcept;

		struct Less
		{
			bool operator()(
				const IntVector2& a,
				const IntVector2& b) const noexcept
			{
				return less(a, b);
			}
		};
	};
}
