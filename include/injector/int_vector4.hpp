#pragma once
#include <injector/int_vector3.hpp>

namespace INJECTOR_NAMESPACE
{
	struct IntVector4
	{
		int x, y, z, w;

		IntVector4(int x = 0.0f, int y = 0.0f, int z = 0.0f, int w = 0.0f);
		IntVector4(const IntVector2& other, int z = 0.0f, int w = 0.0f);
		IntVector4(const IntVector3& other, int w = 0.0f);

		float getMagnitude() const noexcept;
		int getDot(const IntVector4& other) const noexcept;
		float getDistance(const IntVector4& other) const noexcept;
		IntVector4 getNegative() const noexcept;

		bool operator==(const IntVector4& other) const noexcept;
		bool operator!=(const IntVector4& other) const noexcept;

		IntVector4& operator--() noexcept;
		IntVector4& operator++() noexcept;
		IntVector4 operator--(int) noexcept;
		IntVector4 operator++(int) noexcept;

		IntVector4 operator-(const IntVector4& other) const noexcept;
		IntVector4 operator+(const IntVector4& other) const noexcept;
		IntVector4 operator/(const IntVector4& other) const noexcept;
		IntVector4 operator*(const IntVector4& other) const noexcept;
		IntVector4 operator%(const IntVector4& other) const noexcept;
		IntVector4 operator|(const IntVector4& other) const noexcept;
		IntVector4 operator&(const IntVector4& other) const noexcept;
		IntVector4 operator^(const IntVector4& other) const noexcept;
		IntVector4 operator<<(const IntVector4& other) const noexcept;
		IntVector4 operator>>(const IntVector4& other) const noexcept;
		IntVector4& operator=(const IntVector4& other) noexcept;
		IntVector4& operator-=(const IntVector4& other) noexcept;
		IntVector4& operator+=(const IntVector4& other) noexcept;
		IntVector4& operator/=(const IntVector4& other) noexcept;
		IntVector4& operator*=(const IntVector4& other) noexcept;
		IntVector4& operator%=(const IntVector4& other) noexcept;
		IntVector4& operator|=(const IntVector4& other) noexcept;
		IntVector4& operator&=(const IntVector4& other) noexcept;
		IntVector4& operator^=(const IntVector4& other) noexcept;
		IntVector4& operator<<=(const IntVector4& other) noexcept;
		IntVector4& operator>>=(const IntVector4& other) noexcept;

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
		IntVector4& operator=(int value) noexcept;
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

		static const IntVector4 zero;
		static const IntVector4 minusOne;
		static const IntVector4 one;
	};
}
