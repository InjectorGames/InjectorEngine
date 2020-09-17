#pragma once

namespace Injector
{
	struct IntVector2
	{
		int x, y;

		IntVector2();
		IntVector2(int xy);
		IntVector2(int x, int y);

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

		static const IntVector2 zero;
		static const IntVector2 minusOne;
		static const IntVector2 one;
		static const IntVector2 minimum;
		static const IntVector2 maximum;
	};
}
