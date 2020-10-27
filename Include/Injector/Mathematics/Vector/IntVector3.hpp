#pragma once
#include "Injector/Mathematics/Vector/IntVector2.hpp"

namespace Injector
{
	struct IntVector3 final
	{
		int x, y, z;

		IntVector3() noexcept;
		explicit IntVector3(int xyz) noexcept;
		IntVector3(int x, int y, int z) noexcept;
		IntVector3(const IntVector2& vectorS, int z) noexcept;
		IntVector3(int x, const IntVector2& vector) noexcept;

		std::string getString() const noexcept;
		int getDotProduct(const IntVector3& vector) const noexcept;
		IntVector3 getCrossProduct(const IntVector3& vector) const noexcept;
		float getLength() const noexcept;
		float getDistance(const IntVector3& vector) const noexcept;
		IntVector3 getReflected(const IntVector3& normal) const noexcept;

		IntVector2 getIntVector2() const noexcept;

		bool operator==(const IntVector3& vector) const noexcept;
		bool operator!=(const IntVector3& vector) const noexcept;

		IntVector3& operator--() noexcept;
		IntVector3& operator++() noexcept;
		IntVector3 operator--(int) noexcept;
		IntVector3 operator++(int) noexcept;
		IntVector3 operator-() const noexcept;

		IntVector3 operator-(const IntVector3& vector) const noexcept;
		IntVector3 operator+(const IntVector3& vector) const noexcept;
		IntVector3 operator/(const IntVector3& vector) const noexcept;
		IntVector3 operator*(const IntVector3& vector) const noexcept;
		IntVector3 operator%(const IntVector3& vector) const noexcept;
		IntVector3 operator|(const IntVector3& vector) const noexcept;
		IntVector3 operator&(const IntVector3& vector) const noexcept;
		IntVector3 operator^(const IntVector3& vector) const noexcept;
		IntVector3 operator<<(const IntVector3& vector) const noexcept;
		IntVector3 operator>>(const IntVector3& vector) const noexcept;
		IntVector3& operator-=(const IntVector3& vector) noexcept;
		IntVector3& operator+=(const IntVector3& vector) noexcept;
		IntVector3& operator/=(const IntVector3& vector) noexcept;
		IntVector3& operator*=(const IntVector3& vector) noexcept;
		IntVector3& operator%=(const IntVector3& vector) noexcept;
		IntVector3& operator|=(const IntVector3& vector) noexcept;
		IntVector3& operator&=(const IntVector3& vector) noexcept;
		IntVector3& operator^=(const IntVector3& vector) noexcept;
		IntVector3& operator<<=(const IntVector3& vector) noexcept;
		IntVector3& operator>>=(const IntVector3& vector) noexcept;

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

		// (0, 0, 0)
		static const IntVector3 zero;
		// (-1, -1, -1)
		static const IntVector3 minusOne;
		// (1, 1, 1)
		static const IntVector3 one;
		// (-1, 0, 0)
		static const IntVector3 left;
		// (1, 0, 0)
		static const IntVector3 right;
		// (0, -1, 0)
		static const IntVector3 down;
		// (0, 1, 0)
		static const IntVector3 up;
		// (0, 0, -1)
		static const IntVector3 back;
		// (0, 0, 1)
		static const IntVector3 forward;
		// (INT32_MIN, INT32_MIN, INT32_MIN)
		static const IntVector3 minimum;
		// (INT32_MAX, INT32_MAX, INT32_MAX)
		static const IntVector3 maximum;

		static bool less(
			const IntVector3& a,
			const IntVector3& b) noexcept;

		struct Less
		{
			bool operator()(
				const IntVector3& a,
				const IntVector3& b) const noexcept
			{
				return less(a, b);
			}
		};
	};
}
