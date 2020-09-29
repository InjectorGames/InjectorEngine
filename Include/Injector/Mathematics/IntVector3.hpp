#pragma once
#include "Injector/Mathematics/IntVector2.hpp"

namespace Injector
{
	struct IntVector3 final
	{
		int x, y, z;

		IntVector3();
		explicit IntVector3(int xyz);
		IntVector3(int x, int y, int z);
		IntVector3(const IntVector2& vectorS, int z);
		IntVector3(int x, const IntVector2& vector);

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

		static const IntVector3 zero;
		static const IntVector3 minusOne;
		static const IntVector3 one;
		static const IntVector3 minimum;
		static const IntVector3 maximum;
	};
}
