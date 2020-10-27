#pragma once
#include "Injector/Mathematics/Vector/IntVector3.hpp"

namespace Injector
{
	struct IntVector4 final
	{
		int x, y, z, w;

		IntVector4() noexcept;
		explicit IntVector4(int xyzw) noexcept;
		IntVector4(int x, int y, int z, int w) noexcept;
		IntVector4(const IntVector2& vector, int z, int w) noexcept;
		IntVector4(int x, const IntVector2& vector, int w) noexcept;
		IntVector4(int x, int y, const IntVector2& vector) noexcept;
		IntVector4(const IntVector3& vector, int w) noexcept;
		IntVector4(int x, const IntVector3& vector) noexcept;

		std::string getString() const noexcept;
		int getDotProduct(const IntVector4& vector) const noexcept;
		float getLength() const noexcept;
		float getDistance(const IntVector4& vector) const noexcept;
		IntVector4 getReflected(const IntVector4& normal) const noexcept;

		IntVector2 getIntVector2() const noexcept;
		IntVector3 getIntVector3() const noexcept;

		bool operator==(const IntVector4& vector) const noexcept;
		bool operator!=(const IntVector4& vector) const noexcept;

		IntVector4& operator--() noexcept;
		IntVector4& operator++() noexcept;
		IntVector4 operator--(int) noexcept;
		IntVector4 operator++(int) noexcept;
		IntVector4 operator-() const noexcept;

		IntVector4 operator-(const IntVector4& vector) const noexcept;
		IntVector4 operator+(const IntVector4& vector) const noexcept;
		IntVector4 operator/(const IntVector4& vector) const noexcept;
		IntVector4 operator*(const IntVector4& vector) const noexcept;
		IntVector4 operator%(const IntVector4& vector) const noexcept;
		IntVector4 operator|(const IntVector4& vector) const noexcept;
		IntVector4 operator&(const IntVector4& vector) const noexcept;
		IntVector4 operator^(const IntVector4& vector) const noexcept;
		IntVector4 operator<<(const IntVector4& vector) const noexcept;
		IntVector4 operator>>(const IntVector4& vector) const noexcept;
		IntVector4& operator-=(const IntVector4& vector) noexcept;
		IntVector4& operator+=(const IntVector4& vector) noexcept;
		IntVector4& operator/=(const IntVector4& vector) noexcept;
		IntVector4& operator*=(const IntVector4& vector) noexcept;
		IntVector4& operator%=(const IntVector4& vector) noexcept;
		IntVector4& operator|=(const IntVector4& vector) noexcept;
		IntVector4& operator&=(const IntVector4& vector) noexcept;
		IntVector4& operator^=(const IntVector4& vector) noexcept;
		IntVector4& operator<<=(const IntVector4& vector) noexcept;
		IntVector4& operator>>=(const IntVector4& vector) noexcept;

		IntVector4 operator-(int value) const noexcept;
		IntVector4 operator+(int value) const noexcept;
		IntVector4 operator/(int value) const noexcept;
		IntVector4 operator*(int value) const noexcept;
		IntVector4 operator%(int value) const noexcept;
		IntVector4 operator|(int value) const noexcept;
		IntVector4 operator&(int value) const noexcept;
		IntVector4 operator^(int value) const noexcept;
		IntVector4 operator<<(int value) const noexcept;
		IntVector4 operator>>(int value) const noexcept;
		IntVector4& operator-=(int value) noexcept;
		IntVector4& operator+=(int value) noexcept;
		IntVector4& operator/=(int value) noexcept;
		IntVector4& operator*=(int value) noexcept;
		IntVector4& operator%=(int value) noexcept;
		IntVector4& operator|=(int value) noexcept;
		IntVector4& operator&=(int value) noexcept;
		IntVector4& operator^=(int value) noexcept;
		IntVector4& operator<<=(int value) noexcept;
		IntVector4& operator>>=(int value) noexcept;

		// (0, 0, 0, 0)
		static const IntVector4 zero;
		// (-1, -1, -1, -1)
		static const IntVector4 minusOne;
		// (1, 1, 1, 1)
		static const IntVector4 one;
		// (INT32_MIN, INT32_MIN, INT32_MIN, INT32_MIN)
		static const IntVector4 minimum;
		// (INT32_MAX, INT32_MAX, INT32_MAX, INT32_MAX)
		static const IntVector4 maximum;

		static bool less(
			const IntVector4& a,
			const IntVector4& b) noexcept;

		struct Less
		{
			bool operator()(
				const IntVector4& a,
				const IntVector4& b) const noexcept
			{
				return less(a, b);
			}
		};
	};
}
