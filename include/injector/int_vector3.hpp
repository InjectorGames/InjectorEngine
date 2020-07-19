#pragma once
#include <injector/int_vector2.hpp>

namespace INJECTOR_NAMESPACE
{
	struct IntVector3
	{
		int x, y, z;

		IntVector3(int x = 0.0f, int y = 0.0f, int z = 0.0f);
		IntVector3(const IntVector2& other, int z = 0.0f);

		float getMagnitude();
		int getDot(const IntVector3& other);
		float getDistance(const IntVector3& other);
		IntVector3 getCross(const IntVector3& other);

		bool operator==(const IntVector3& other);
		bool operator!=(const IntVector3& other);

		IntVector3& operator--();
		IntVector3& operator++();
		IntVector3 operator--(int);
		IntVector3 operator++(int);

		IntVector3 operator-(const IntVector3& other);
		IntVector3 operator+(const IntVector3& other);
		IntVector3 operator/(const IntVector3& other);
		IntVector3 operator*(const IntVector3& other);
		IntVector3 operator%(const IntVector3& other);
		IntVector3 operator|(const IntVector3& other);
		IntVector3 operator&(const IntVector3& other);
		IntVector3 operator^(const IntVector3& other);
		IntVector3 operator<<(const IntVector3& other);
		IntVector3 operator>>(const IntVector3& other);
		IntVector3& operator-=(const IntVector3& other);
		IntVector3& operator+=(const IntVector3& other);
		IntVector3& operator/=(const IntVector3& other);
		IntVector3& operator*=(const IntVector3& other);
		IntVector3& operator%=(const IntVector3& other);
		IntVector3& operator|=(const IntVector3& other);
		IntVector3& operator&=(const IntVector3& other);
		IntVector3& operator^=(const IntVector3& other);
		IntVector3& operator<<=(const IntVector3& other);
		IntVector3& operator>>=(const IntVector3& other);

		IntVector3 operator-(int value);
		IntVector3 operator+(int value);
		IntVector3 operator/(int value);
		IntVector3 operator*(int value);
		IntVector3 operator%(int value);
		IntVector3 operator|(int value);
		IntVector3 operator&(int value);
		IntVector3 operator^(int value);
		IntVector3 operator<<(int value);
		IntVector3 operator>>(int value);
		IntVector3& operator-=(int value);
		IntVector3& operator+=(int value);
		IntVector3& operator/=(int value);
		IntVector3& operator*=(int value);
		IntVector3& operator%=(int value);
		IntVector3& operator|=(int value);
		IntVector3& operator&=(int value);
		IntVector3& operator^=(int value);
		IntVector3& operator<<=(int value);
		IntVector3& operator>>=(int value);
	};
}
