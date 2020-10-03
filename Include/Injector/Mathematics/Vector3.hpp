#pragma once
#include "Injector/Mathematics/Vector2.hpp"
#include "Injector/Mathematics/IntVector3.hpp"

namespace Injector
{
	struct Vector3 final
	{
		float x, y, z;

		Vector3() noexcept;
		explicit Vector3(float xyz) noexcept;
		Vector3(float x, float y, float z) noexcept;
		Vector3(const Vector2& vector, float z) noexcept;
		Vector3(float x, const Vector2& vector) noexcept;
		explicit Vector3(const IntVector3& vector) noexcept;
		Vector3(const IntVector2& vector, float z) noexcept;
		Vector3(float x, const IntVector2& vector) noexcept;

		std::string getString() const noexcept;
		float getDotProduct(const Vector3& vector) const noexcept;
		float getDotProduct(const IntVector3& vector) const noexcept;
		Vector3 getCrossProduct(const Vector3& vector) const noexcept;
		Vector3 getCrossProduct(const IntVector3& vector) const noexcept;
		float getLength() const noexcept;
		float getDistance(const Vector3& vector) const noexcept;
		float getDistance(const IntVector3& vector) const noexcept;
		Vector3 getNormalized() const noexcept;
		Vector3 getReflected(const Vector3& normal) const noexcept;
		Vector3 getRefracted(const Vector3& normal, float eta) const noexcept;
		Vector3 getSine() const noexcept;
		Vector3 getCosine() const noexcept;
		Vector3 getTangent() const noexcept;
		Vector3 getCotangent() const noexcept;

		Vector2 getVector2() const noexcept;

		bool operator==(const Vector3& vector) const noexcept;
		bool operator!=(const Vector3& vector) const noexcept;

		Vector3& operator--() noexcept;
		Vector3& operator++() noexcept;
		Vector3 operator--(int) noexcept;
		Vector3 operator++(int) noexcept;
		Vector3 operator-() const noexcept;

		Vector3 operator-(const Vector3& vector) const noexcept;
		Vector3 operator+(const Vector3& vector) const noexcept;
		Vector3 operator/(const Vector3& vector) const noexcept;
		Vector3 operator*(const Vector3& vector) const noexcept;
		Vector3& operator-=(const Vector3& vector) noexcept;
		Vector3& operator+=(const Vector3& vector) noexcept;
		Vector3& operator/=(const Vector3& vector) noexcept;
		Vector3& operator*=(const Vector3& vector) noexcept;

		Vector3 operator-(const IntVector3& vector) const noexcept;
		Vector3 operator+(const IntVector3& vector) const noexcept;
		Vector3 operator/(const IntVector3& vector) const noexcept;
		Vector3 operator*(const IntVector3& vector) const noexcept;
		Vector3& operator-=(const IntVector3& vector) noexcept;
		Vector3& operator+=(const IntVector3& vector) noexcept;
		Vector3& operator/=(const IntVector3& vector) noexcept;
		Vector3& operator*=(const IntVector3& vector) noexcept;

		Vector3 operator-(float value) const noexcept;
		Vector3 operator+(float value) const noexcept;
		Vector3 operator/(float value) const noexcept;
		Vector3 operator*(float value) const noexcept;
		Vector3& operator-=(float value) noexcept;
		Vector3& operator+=(float value) noexcept;
		Vector3& operator/=(float value) noexcept;
		Vector3& operator*=(float value) noexcept;

		static const Vector3 zero;
		static const Vector3 minusOne;
		static const Vector3 one;

		static bool less(
			const Vector3& a,
			const Vector3& b) noexcept;
	};
}
