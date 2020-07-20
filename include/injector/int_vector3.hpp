#pragma once
#include <injector/int_vector2.hpp>

namespace INJECTOR_NAMESPACE
{
	struct IntVector3
	{
		int x, y, z;

		IntVector3();
		IntVector3(int x, int y, int z);
		IntVector3(const IntVector2& other, int z);
		IntVector3(int x, const IntVector2& other);

		float getMagnitude() const noexcept;
		int getDot(const IntVector3& other) const noexcept;
		float getDistance(const IntVector3& other) const noexcept;
		IntVector3 getNegative() const noexcept;
		IntVector3 getCross(const IntVector3& other) const noexcept;

		bool operator==(const IntVector3& other) const noexcept;
		bool operator!=(const IntVector3& other) const noexcept;

		IntVector3& operator--() noexcept;
		IntVector3& operator++() noexcept;
		IntVector3 operator--(int) noexcept;
		IntVector3 operator++(int) noexcept;

		IntVector3 operator-(const IntVector3& other) const noexcept;
		IntVector3 operator+(const IntVector3& other) const noexcept;
		IntVector3 operator/(const IntVector3& other) const noexcept;
		IntVector3 operator*(const IntVector3& other) const noexcept;
		IntVector3 operator%(const IntVector3& other) const noexcept;
		IntVector3 operator|(const IntVector3& other) const noexcept;
		IntVector3 operator&(const IntVector3& other) const noexcept;
		IntVector3 operator^(const IntVector3& other) const noexcept;
		IntVector3 operator<<(const IntVector3& other) const noexcept;
		IntVector3 operator>>(const IntVector3& other) const noexcept;
		IntVector3& operator=(const IntVector3& other) noexcept;
		IntVector3& operator-=(const IntVector3& other) noexcept;
		IntVector3& operator+=(const IntVector3& other) noexcept;
		IntVector3& operator/=(const IntVector3& other) noexcept;
		IntVector3& operator*=(const IntVector3& other) noexcept;
		IntVector3& operator%=(const IntVector3& other) noexcept;
		IntVector3& operator|=(const IntVector3& other) noexcept;
		IntVector3& operator&=(const IntVector3& other) noexcept;
		IntVector3& operator^=(const IntVector3& other) noexcept;
		IntVector3& operator<<=(const IntVector3& other) noexcept;
		IntVector3& operator>>=(const IntVector3& other) noexcept;

		IntVector3 operator-(int value) const noexcept;
		IntVector3 operator+(int value) const noexcept;
		IntVector3 operator/(int value) const noexcept;
		IntVector3 operator*(int value) const noexcept;
		IntVector3 operator%(int value) const noexcept;
		IntVector3 operator|(int value) const noexcept;
		IntVector3 operator&(int value) const noexcept;
		IntVector3 operator^(int value) const noexcept;
		IntVector3 operator<<(int value) const noexcept;
		IntVector3 operator>>(int value) const noexcept;
		IntVector3& operator=(int value) noexcept;
		IntVector3& operator-=(int value) noexcept;
		IntVector3& operator+=(int value) noexcept;
		IntVector3& operator/=(int value) noexcept;
		IntVector3& operator*=(int value) noexcept;
		IntVector3& operator%=(int value) noexcept;
		IntVector3& operator|=(int value) noexcept;
		IntVector3& operator&=(int value) noexcept;
		IntVector3& operator^=(int value) noexcept;
		IntVector3& operator<<=(int value) noexcept;
		IntVector3& operator>>=(int value) noexcept;

		static const IntVector3 zero;
		static const IntVector3 minusOne;
		static const IntVector3 one;
	};
}
