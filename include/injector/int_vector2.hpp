#pragma once
#include <injector/defines.hpp>

namespace INJECTOR_NAMESPACE
{
	struct IntVector2
	{
		int x, y;

		IntVector2(int x = 0, int y = 0);

		float getMagnitude();
		int getDot(const IntVector2& other);
		float getDistance(const IntVector2& other);

		bool operator==(const IntVector2& other);
		bool operator!=(const IntVector2& other);

		IntVector2& operator--();
		IntVector2& operator++();
		IntVector2 operator--(int);
		IntVector2 operator++(int);

		IntVector2 operator-(const IntVector2& other);
		IntVector2 operator+(const IntVector2& other);
		IntVector2 operator/(const IntVector2& other);
		IntVector2 operator*(const IntVector2& other);
		IntVector2 operator%(const IntVector2& other);
		IntVector2 operator|(const IntVector2& other);
		IntVector2 operator&(const IntVector2& other);
		IntVector2 operator^(const IntVector2& other);
		IntVector2 operator<<(const IntVector2& other);
		IntVector2 operator>>(const IntVector2& other);
		IntVector2& operator-=(const IntVector2& other);
		IntVector2& operator+=(const IntVector2& other);
		IntVector2& operator/=(const IntVector2& other);
		IntVector2& operator*=(const IntVector2& other);
		IntVector2& operator%=(const IntVector2& other);
		IntVector2& operator|=(const IntVector2& other);
		IntVector2& operator&=(const IntVector2& other);
		IntVector2& operator^=(const IntVector2& other);
		IntVector2& operator<<=(const IntVector2& other);
		IntVector2& operator>>=(const IntVector2& other);

		IntVector2 operator-(int value);
		IntVector2 operator+(int value);
		IntVector2 operator/(int value);
		IntVector2 operator*(int value);
		IntVector2 operator%(int value);
		IntVector2 operator|(int value);
		IntVector2 operator&(int value);
		IntVector2 operator^(int value);
		IntVector2 operator<<(int value);
		IntVector2 operator>>(int value);
		IntVector2& operator-=(int value);
		IntVector2& operator+=(int value);
		IntVector2& operator/=(int value);
		IntVector2& operator*=(int value);
		IntVector2& operator%=(int value);
		IntVector2& operator|=(int value);
		IntVector2& operator&=(int value);
		IntVector2& operator^=(int value);
		IntVector2& operator<<=(int value);
		IntVector2& operator>>=(int value);
	};
}
