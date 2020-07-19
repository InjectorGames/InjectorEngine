#pragma once
#include <injector/defines.hpp>

namespace INJECTOR_NAMESPACE
{
	struct IntVector2
	{
		int x, y;

		IntVector2(int x = 0, int y = 0);

		float getMagnitude() const noexcept;
		int getDot(const IntVector2& other) const noexcept;
		float getDistance(const IntVector2& other) const noexcept;
		IntVector2 getNegative() const noexcept;

		bool operator==(const IntVector2& other) const noexcept;
		bool operator!=(const IntVector2& other) const noexcept;

		IntVector2& operator--() noexcept;
		IntVector2& operator++() noexcept;
		IntVector2 operator--(int) noexcept;
		IntVector2 operator++(int) noexcept;

		IntVector2 operator-(const IntVector2& other) const noexcept;
		IntVector2 operator+(const IntVector2& other) const noexcept;
		IntVector2 operator/(const IntVector2& other) const noexcept;
		IntVector2 operator*(const IntVector2& other) const noexcept;
		IntVector2 operator%(const IntVector2& other) const noexcept;
		IntVector2 operator|(const IntVector2& other) const noexcept;
		IntVector2 operator&(const IntVector2& other) const noexcept;
		IntVector2 operator^(const IntVector2& other) const noexcept;
		IntVector2 operator<<(const IntVector2& other) const noexcept;
		IntVector2 operator>>(const IntVector2& other) const noexcept;
		IntVector2& operator=(const IntVector2& other) noexcept;
		IntVector2& operator-=(const IntVector2& other) noexcept;
		IntVector2& operator+=(const IntVector2& other) noexcept;
		IntVector2& operator/=(const IntVector2& other) noexcept;
		IntVector2& operator*=(const IntVector2& other) noexcept;
		IntVector2& operator%=(const IntVector2& other) noexcept;
		IntVector2& operator|=(const IntVector2& other) noexcept;
		IntVector2& operator&=(const IntVector2& other) noexcept;
		IntVector2& operator^=(const IntVector2& other) noexcept;
		IntVector2& operator<<=(const IntVector2& other) noexcept;
		IntVector2& operator>>=(const IntVector2& other) noexcept;

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
		IntVector2& operator=(int value) noexcept;
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
	};
}
