#pragma once
#include <injector/mathematics/int_vector3.hpp>

namespace INJECTOR_NAMESPACE
{
	struct IntVector4
	{
		int x, y, z, w;

		IntVector4();
		IntVector4(int xyzw);
		IntVector4(int x, int y, int z, int w);
		IntVector4(const IntVector2& vector, int z, int w);
		IntVector4(int x, const IntVector2& vector, int w);
		IntVector4(int x, int y, const IntVector2& vector);
		IntVector4(const IntVector3& vector, int w);
		IntVector4(int x, const IntVector3& vector);

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

		static const IntVector4 zero;
		static const IntVector4 minusOne;
		static const IntVector4 one;
	};
}
