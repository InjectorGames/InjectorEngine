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

		float getMagnitude();
		int getDot(const IntVector4& other);
		float getDistance(const IntVector4& other);

		bool operator==(const IntVector4& other);
		bool operator!=(const IntVector4& other);

		IntVector4& operator--();
		IntVector4& operator++();
		IntVector4 operator--(int);
		IntVector4 operator++(int);

		IntVector4 operator-(const IntVector4& other);
		IntVector4 operator+(const IntVector4& other);
		IntVector4 operator/(const IntVector4& other);
		IntVector4 operator*(const IntVector4& other);
		IntVector4 operator%(const IntVector4& other);
		IntVector4 operator|(const IntVector4& other);
		IntVector4 operator&(const IntVector4& other);
		IntVector4 operator^(const IntVector4& other);
		IntVector4 operator<<(const IntVector4& other);
		IntVector4 operator>>(const IntVector4& other);
		IntVector4& operator-=(const IntVector4& other);
		IntVector4& operator+=(const IntVector4& other);
		IntVector4& operator/=(const IntVector4& other);
		IntVector4& operator*=(const IntVector4& other);
		IntVector4& operator%=(const IntVector4& other);
		IntVector4& operator|=(const IntVector4& other);
		IntVector4& operator&=(const IntVector4& other);
		IntVector4& operator^=(const IntVector4& other);
		IntVector4& operator<<=(const IntVector4& other);
		IntVector4& operator>>=(const IntVector4& other);

		IntVector4 operator-(int value);
		IntVector4 operator+(int value);
		IntVector4 operator/(int value);
		IntVector4 operator*(int value);
		IntVector4 operator%(int value);
		IntVector4 operator|(int value);
		IntVector4 operator&(int value);
		IntVector4 operator^(int value);
		IntVector4 operator<<(int value);
		IntVector4 operator>>(int value);
		IntVector4& operator-=(int value);
		IntVector4& operator+=(int value);
		IntVector4& operator/=(int value);
		IntVector4& operator*=(int value);
		IntVector4& operator%=(int value);
		IntVector4& operator|=(int value);
		IntVector4& operator&=(int value);
		IntVector4& operator^=(int value);
		IntVector4& operator<<=(int value);
		IntVector4& operator>>=(int value);
	};
}
