#pragma once
#include "Injector/Mathematics/Vector3.hpp"
#include "Injector/Mathematics/IntVector4.hpp"

namespace Injector
{
	struct Vector4
	{
	 protected:
		static bool (* cmpeq)(const Vector4&, const Vector4&);
		static bool (* cmpneq)(const Vector4&, const Vector4&);
		static bool (* cmple)(const Vector4&, const Vector4&);
		static bool (* cmpge)(const Vector4&, const Vector4&);
		static bool (* cmplt)(const Vector4&, const Vector4&);
		static bool (* cmpgt)(const Vector4&, const Vector4&);
		static Vector4 (* sub)(const Vector4&, const Vector4&);
		static Vector4 (* add)(const Vector4&, const Vector4&);
		static Vector4 (* div)(const Vector4&, const Vector4&);
		static Vector4 (* mul)(const Vector4&, const Vector4&);
		static Vector4 (* sub1)(const Vector4&, float);
		static Vector4 (* add1)(const Vector4&, float);
		static Vector4 (* div1)(const Vector4&, float);
		static Vector4 (* mul1)(const Vector4&, float);

		static bool cmpeqRAW(const Vector4& a, const Vector4& b);
		static bool cmpeqSSE(const Vector4& a, const Vector4& b);
		static bool cmpneqRAW(const Vector4& a, const Vector4& b);
		static bool cmpneqSSE(const Vector4& a, const Vector4& b);
		static bool cmpleRAW(const Vector4& a, const Vector4& b);
		static bool cmpleSSE(const Vector4& a, const Vector4& b);
		static bool cmpgeRAW(const Vector4& a, const Vector4& b);
		static bool cmpgeSSE(const Vector4& a, const Vector4& b);
		static bool cmpltRAW(const Vector4& a, const Vector4& b);
		static bool cmpltSSE(const Vector4& a, const Vector4& b);
		static bool cmpgtRAW(const Vector4& a, const Vector4& b);
		static bool cmpgtSSE(const Vector4& a, const Vector4& b);
		static Vector4 subRAW(const Vector4& a, const Vector4& b);
		static Vector4 subSSE(const Vector4& a, const Vector4& b);
		static Vector4 addRAW(const Vector4& a, const Vector4& b);
		static Vector4 addSSE(const Vector4& a, const Vector4& b);
		static Vector4 divRAW(const Vector4& a, const Vector4& b);
		static Vector4 divSSE(const Vector4& a, const Vector4& b);
		static Vector4 mulRAW(const Vector4& a, const Vector4& b);
		static Vector4 mulSSE(const Vector4& a, const Vector4& b);
		static Vector4 sub1RAW(const Vector4& a, float b);
		static Vector4 sub1SSE(const Vector4& a, float b);
		static Vector4 add1RAW(const Vector4& a, float b);
		static Vector4 add1SSE(const Vector4& a, float b);
		static Vector4 div1RAW(const Vector4& a, float b);
		static Vector4 div1SSE(const Vector4& a, float b);
		static Vector4 mul1RAW(const Vector4& a, float b);
		static Vector4 mul1SSE(const Vector4& a, float b);
	 public:
		float x, y, z, w;

		Vector4();
		Vector4(float xyzw);
		Vector4(float x, float y, float z, float w);
		Vector4(const Vector2& vector, float z, float w);
		Vector4(float x, const Vector2& vector, float w);
		Vector4(float x, float y, const Vector2& vector);
		Vector4(const Vector3& vector, float w);
		Vector4(float x, const Vector3& vector);
		Vector4(const IntVector4& vector);
		Vector4(const IntVector2& vector, float z, float w);
		Vector4(float x, const IntVector2& vector, float w);
		Vector4(float x, float y, const IntVector2& vector);
		Vector4(const IntVector3& vector, float w);
		Vector4(float x, const IntVector3& vector);

		float getDotProduct(const Vector4& vector) const noexcept;
		float getDotProduct(const IntVector4& vector) const noexcept;
		float getLength() const noexcept;
		float getDistance(const Vector4& vector) const noexcept;
		float getDistance(const IntVector4& vector) const noexcept;
		Vector4 getNormalized() const noexcept;
		Vector4 getReflected(const Vector4& normal) const noexcept;
		Vector4 getRefracted(const Vector4& normal, float eta) const noexcept;
		Vector4 getSine() const noexcept;
		Vector4 getCosine() const noexcept;
		Vector4 getTangent() const noexcept;
		Vector4 getCotangent() const noexcept;

		Vector2 getVector2() const noexcept;
		Vector3 getVector3() const noexcept;

		bool operator==(const Vector4& vector) const noexcept;
		bool operator!=(const Vector4& vector) const noexcept;
		bool operator<=(const Vector4& vector) const noexcept;
		bool operator>=(const Vector4& vector) const noexcept;
		bool operator<(const Vector4& vector) const noexcept;
		bool operator>(const Vector4& vector) const noexcept;


		Vector4& operator--() noexcept;
		Vector4& operator++() noexcept;
		Vector4 operator--(int) noexcept;
		Vector4 operator++(int) noexcept;
		Vector4 operator-() const noexcept;

		Vector4 operator-(const Vector4& vector) const noexcept;
		Vector4 operator+(const Vector4& vector) const noexcept;
		Vector4 operator/(const Vector4& vector) const noexcept;
		Vector4 operator*(const Vector4& vector) const noexcept;
		Vector4& operator-=(const Vector4& vector) noexcept;
		Vector4& operator+=(const Vector4& vector) noexcept;
		Vector4& operator/=(const Vector4& vector) noexcept;
		Vector4& operator*=(const Vector4& vector) noexcept;

		Vector4 operator-(const IntVector4& vector) const noexcept;
		Vector4 operator+(const IntVector4& vector) const noexcept;
		Vector4 operator/(const IntVector4& vector) const noexcept;
		Vector4 operator*(const IntVector4& vector) const noexcept;
		Vector4& operator-=(const IntVector4& vector) noexcept;
		Vector4& operator+=(const IntVector4& vector) noexcept;
		Vector4& operator/=(const IntVector4& vector) noexcept;
		Vector4& operator*=(const IntVector4& vector) noexcept;

		Vector4 operator-(float value) const noexcept;
		Vector4 operator+(float value) const noexcept;
		Vector4 operator/(float value) const noexcept;
		Vector4 operator*(float value) const noexcept;
		Vector4& operator-=(float value) noexcept;
		Vector4& operator+=(float value) noexcept;
		Vector4& operator/=(float value) noexcept;
		Vector4& operator*=(float value) noexcept;

		static void initialize();

		static const Vector4 zero;
		static const Vector4 minusOne;
		static const Vector4 one;
	};
}
