#include "Injector/Mathematics/Vector4.hpp"
#include "Injector/CpuInfo.hpp"

#include <cmath>
#include <immintrin.h>

namespace Injector
{
	bool (* Vector4::cmpeq)(const Vector4&, const Vector4&) = nullptr;
	bool (* Vector4::cmpneq)(const Vector4&, const Vector4&) = nullptr;
	bool (* Vector4::cmple)(const Vector4&, const Vector4&) = nullptr;
	bool (* Vector4::cmpge)(const Vector4&, const Vector4&) = nullptr;
	bool (* Vector4::cmplt)(const Vector4&, const Vector4&) = nullptr;
	bool (* Vector4::cmpgt)(const Vector4&, const Vector4&) = nullptr;
	Vector4 (* Vector4::sub)(const Vector4&, const Vector4&) = nullptr;
	Vector4 (* Vector4::add)(const Vector4&, const Vector4&) = nullptr;
	Vector4 (* Vector4::div)(const Vector4&, const Vector4&) = nullptr;
	Vector4 (* Vector4::mul)(const Vector4&, const Vector4&) = nullptr;
	Vector4 (* Vector4::sub1)(const Vector4&, float) = nullptr;
	Vector4 (* Vector4::add1)(const Vector4&, float) = nullptr;
	Vector4 (* Vector4::div1)(const Vector4&, float) = nullptr;
	Vector4 (* Vector4::mul1)(const Vector4&, float) = nullptr;

	bool Vector4::cmpeqRAW(const Vector4& a, const Vector4& b)
	{
		return
			a.x == b.x &&
			a.y == b.y &&
			a.z == b.z &&
			a.w == b.w;
	}
	bool Vector4::cmpeqSSE(const Vector4& _a, const Vector4& _b)
	{
		auto result = Vector4();
		auto a = _mm_loadu_ps(reinterpret_cast<const float*>(&_a));
		auto b = _mm_loadu_ps(reinterpret_cast<const float*>(&_b));
		auto r = _mm_cmpeq_ps(a, b);
		return _mm_movemask_ps(r) == 0xF;
	}
	bool Vector4::cmpneqRAW(const Vector4& a, const Vector4& b)
	{
		return
			a.x != b.x ||
			a.y != b.y ||
			a.z != b.z ||
			a.w != b.w;
	}
	bool Vector4::cmpneqSSE(const Vector4& _a, const Vector4& _b)
	{
		auto result = Vector4();
		auto a = _mm_loadu_ps(reinterpret_cast<const float*>(&_a));
		auto b = _mm_loadu_ps(reinterpret_cast<const float*>(&_b));
		auto r = _mm_cmpneq_ps(a, b);
		return _mm_movemask_ps(r) != 0;
	}
	bool Vector4::cmpleRAW(const Vector4& a, const Vector4& b)
	{
		return
			a.x <= b.x &&
			a.y <= b.y &&
			a.z <= b.z &&
			a.w <= b.w;
	}
	bool Vector4::cmpleSSE(const Vector4& _a, const Vector4& _b)
	{
		auto result = Vector4();
		auto a = _mm_loadu_ps(reinterpret_cast<const float*>(&_a));
		auto b = _mm_loadu_ps(reinterpret_cast<const float*>(&_b));
		auto r = _mm_cmple_ps(a, b);
		return _mm_movemask_ps(r) == 0xF;
	}
	bool Vector4::cmpgeRAW(const Vector4& a, const Vector4& b)
	{
		return
			a.x >= b.x &&
			a.y >= b.y &&
			a.z >= b.z &&
			a.w >= b.w;
	}
	bool Vector4::cmpgeSSE(const Vector4& _a, const Vector4& _b)
	{
		auto result = Vector4();
		auto a = _mm_loadu_ps(reinterpret_cast<const float*>(&_a));
		auto b = _mm_loadu_ps(reinterpret_cast<const float*>(&_b));
		auto r = _mm_cmpge_ps(a, b);
		return _mm_movemask_ps(r) == 0xF;
	}
	bool Vector4::cmpltRAW(const Vector4& a, const Vector4& b)
	{
		return
			a.x < b.x &&
			a.y < b.y &&
			a.z < b.z &&
			a.w < b.w;
	}
	bool Vector4::cmpltSSE(const Vector4& _a, const Vector4& _b)
	{
		auto result = Vector4();
		auto a = _mm_loadu_ps(reinterpret_cast<const float*>(&_a));
		auto b = _mm_loadu_ps(reinterpret_cast<const float*>(&_b));
		auto r = _mm_cmplt_ps(a, b);
		return _mm_movemask_ps(r) == 0xF;
	}
	bool Vector4::cmpgtRAW(const Vector4& a, const Vector4& b)
	{
		return
			a.x > b.x &&
			a.y > b.y &&
			a.z > b.z &&
			a.w > b.w;
	}
	bool Vector4::cmpgtSSE(const Vector4& _a, const Vector4& _b)
	{
		auto result = Vector4();
		auto a = _mm_loadu_ps(reinterpret_cast<const float*>(&_a));
		auto b = _mm_loadu_ps(reinterpret_cast<const float*>(&_b));
		auto r = _mm_cmpgt_ps(a, b);
		return _mm_movemask_ps(r) == 0xF;
	}
	Vector4 Vector4::subRAW(const Vector4& a, const Vector4& b)
	{
		return Vector4(
			a.x - b.x,
			a.y - b.y,
			a.z - b.z,
			a.w - b.w);
	}
	Vector4 Vector4::subSSE(const Vector4& _a, const Vector4& _b)
	{
		auto result = Vector4();
		auto a = _mm_loadu_ps(reinterpret_cast<const float*>(&_a));
		auto b = _mm_loadu_ps(reinterpret_cast<const float*>(&_b));
		auto r = _mm_sub_ps(a, b);
		_mm_storeu_ps(reinterpret_cast<float*>(&result), r);
		return result;
	}
	Vector4 Vector4::addRAW(const Vector4& a, const Vector4& b)
	{
		return Vector4(
			a.x + b.x,
			a.y + b.y,
			a.z + b.z,
			a.w + b.w);
	}
	Vector4 Vector4::addSSE(const Vector4& _a, const Vector4& _b)
	{
		auto result = Vector4();
		auto a = _mm_loadu_ps(reinterpret_cast<const float*>(&_a));
		auto b = _mm_loadu_ps(reinterpret_cast<const float*>(&_b));
		auto r = _mm_add_ps(a, b);
		_mm_storeu_ps(reinterpret_cast<float*>(&result), r);
		return result;
	}
	Vector4 Vector4::divRAW(const Vector4& a, const Vector4& b)
	{
		return Vector4(
			a.x / b.x,
			a.y / b.y,
			a.z / b.z,
			a.w / b.w);
	}
	Vector4 Vector4::divSSE(const Vector4& _a, const Vector4& _b)
	{
		auto result = Vector4();
		auto a = _mm_loadu_ps(reinterpret_cast<const float*>(&_a));
		auto b = _mm_loadu_ps(reinterpret_cast<const float*>(&_b));
		auto r = _mm_div_ps(a, b);
		_mm_storeu_ps(reinterpret_cast<float*>(&result), r);
		return result;
	}
	Vector4 Vector4::mulRAW(const Vector4& a, const Vector4& b)
	{
		return Vector4(
			a.x * b.x,
			a.y * b.y,
			a.z * b.z,
			a.w * b.w);
	}
	Vector4 Vector4::mulSSE(const Vector4& _a, const Vector4& _b)
	{
		auto result = Vector4();
		auto a = _mm_loadu_ps(reinterpret_cast<const float*>(&_a));
		auto b = _mm_loadu_ps(reinterpret_cast<const float*>(&_b));
		auto r = _mm_mul_ps(a, b);
		_mm_storeu_ps(reinterpret_cast<float*>(&result), r);
		return result;
	}
	Vector4 Vector4::sub1RAW(const Vector4& a, float b)
	{
		return Vector4(
			a.x - b,
			a.y - b,
			a.z - b,
			a.w - b);
	}
	Vector4 Vector4::sub1SSE(const Vector4& _a, float _b)
	{
		auto result = Vector4();
		auto a = _mm_loadu_ps(reinterpret_cast<const float*>(&_a));
		auto b = _mm_load1_ps(reinterpret_cast<const float*>(&_b));
		auto r = _mm_sub_ps(a, b);
		_mm_storeu_ps(reinterpret_cast<float*>(&result), r);
		return result;
	}
	Vector4 Vector4::add1RAW(const Vector4& a, float b)
	{
		return Vector4(
			a.x + b,
			a.y + b,
			a.z + b,
			a.w + b);
	}
	Vector4 Vector4::add1SSE(const Vector4& _a, float _b)
	{
		auto result = Vector4();
		auto a = _mm_loadu_ps(reinterpret_cast<const float*>(&_a));
		auto b = _mm_load1_ps(reinterpret_cast<const float*>(&_b));
		auto r = _mm_add_ps(a, b);
		_mm_storeu_ps(reinterpret_cast<float*>(&result), r);
		return result;
	}
	Vector4 Vector4::div1RAW(const Vector4& a, float b)
	{
		return Vector4(
			a.x / b,
			a.y / b,
			a.z / b,
			a.w / b);
	}
	Vector4 Vector4::div1SSE(const Vector4& _a, float _b)
	{
		auto result = Vector4();
		auto a = _mm_loadu_ps(reinterpret_cast<const float*>(&_a));
		auto b = _mm_load1_ps(reinterpret_cast<const float*>(&_b));
		auto r = _mm_div_ps(a, b);
		_mm_storeu_ps(reinterpret_cast<float*>(&result), r);
		return result;
	}
	Vector4 Vector4::mul1RAW(const Vector4& a, float b)
	{
		return Vector4(
			a.x * b,
			a.y * b,
			a.z * b,
			a.w * b);
	}
	Vector4 Vector4::mul1SSE(const Vector4& _a, float _b)
	{
		auto result = Vector4();
		auto a = _mm_loadu_ps(reinterpret_cast<const float*>(&_a));
		auto b = _mm_load1_ps(reinterpret_cast<const float*>(&_b));
		auto r = _mm_mul_ps(a, b);
		_mm_storeu_ps(reinterpret_cast<float*>(&result), r);
		return result;
	}

	Vector4::Vector4() :
		x(0.0f),
		y(0.0f),
		z(0.0f),
		w(0.0f)
	{
	}
	Vector4::Vector4(
		float xyzw) :
		x(xyzw),
		y(xyzw),
		z(xyzw),
		w(xyzw)
	{
	}
	Vector4::Vector4(
		float _x,
		float _y,
		float _z,
		float _w) :
		x(_x),
		y(_y),
		z(_z),
		w(_w)
	{
	}
	Vector4::Vector4(
		const Vector2& vector,
		float _z,
		float _w) :
		x(vector.x),
		y(vector.y),
		z(_z),
		w(_w)
	{
	}
	Vector4::Vector4(
		float _x,
		const Vector2& vector,
		float _w) :
		x(_x),
		y(vector.x),
		z(vector.y),
		w(_w)
	{
	}
	Vector4::Vector4(
		float _x,
		float _y,
		const Vector2& vector) :
		x(_x),
		y(_y),
		z(vector.x),
		w(vector.y)
	{
	}
	Vector4::Vector4(
		const Vector3& vector,
		float _w) :
		x(vector.x),
		y(vector.y),
		z(vector.z),
		w(_w)
	{
	}
	Vector4::Vector4(
		float _x,
		const Vector3& vector) :
		x(_x),
		y(vector.x),
		z(vector.y),
		w(vector.z)
	{
	}
	Vector4::Vector4(
		const IntVector4& vector) :
		x(static_cast<float>(vector.x)),
		y(static_cast<float>(vector.y)),
		z(static_cast<float>(vector.z)),
		w(static_cast<float>(vector.w))
	{
	}
	Vector4::Vector4(
		const IntVector2& vector,
		float _z,
		float _w) :
		x(static_cast<float>(vector.x)),
		y(static_cast<float>(vector.y)),
		z(_z),
		w(_w)
	{
	}
	Vector4::Vector4(
		float _x,
		const IntVector2& vector,
		float _w) :
		x(_x),
		y(static_cast<float>(vector.x)),
		z(static_cast<float>(vector.y)),
		w(_w)
	{
	}
	Vector4::Vector4(
		float _x,
		float _y,
		const IntVector2& vector) :
		x(_x),
		y(_y),
		z(static_cast<float>(vector.x)),
		w(static_cast<float>(vector.y))
	{
	}
	Vector4::Vector4(
		const IntVector3& vector,
		float _w) :
		x(static_cast<float>(vector.x)),
		y(static_cast<float>(vector.y)),
		z(static_cast<float>(vector.z)),
		w(_w)
	{
	}
	Vector4::Vector4(
		float _x,
		const IntVector3& vector) :
		x(_x),
		y(static_cast<float>(vector.x)),
		z(static_cast<float>(vector.y)),
		w(static_cast<float>(vector.z))
	{
	}

	float Vector4::getDotProduct(const Vector4& vector) const noexcept
	{
		auto result = *this * vector;
		return (result.x + result.y) + (result.z + result.w);
	}
	float Vector4::getDotProduct(const IntVector4& vector) const noexcept
	{
		auto result = *this * vector;
		return (result.x + result.y) + (result.z + result.w);
	}
	float Vector4::getLength() const noexcept
	{
		return sqrt(getDotProduct(*this));
	}
	float Vector4::getDistance(const Vector4& vector) const noexcept
	{
		return sqrt(getDotProduct(*this - vector));
	}
	float Vector4::getDistance(const IntVector4& vector) const noexcept
	{
		return sqrt(getDotProduct(*this - vector));
	}
	Vector4 Vector4::getNormalized() const noexcept
	{
		return *this * (1.0f / sqrt(getDotProduct(*this)));
	}
	Vector4 Vector4::getReflected(const Vector4& normal) const noexcept
	{
		return *this - normal * getDotProduct(normal) * 2.0f;
	}
	Vector4 Vector4::getRefracted(const Vector4& normal, float eta) const noexcept
	{
		auto dot = getDotProduct(normal);
		auto k = (1.0f - eta * eta * (1.0f - dot * dot));

		return Vector4(k >= 0.0f ?
			(*this * eta - normal * (eta * dot + sqrt(k))) :
			Vector4(0.0f));
	}
	Vector4 Vector4::getSine() const noexcept
	{
		return Vector4(
			sin(x),
			sin(y),
			sin(z),
			sin(w));
	}
	Vector4 Vector4::getCosine() const noexcept
	{
		return Vector4(
			cos(x),
			cos(y),
			cos(z),
			cos(w));
	}
	Vector4 Vector4::getTangent() const noexcept
	{
		return Vector4(
			tan(x),
			tan(y),
			tan(z),
			tan(w));
	}
	Vector4 Vector4::getCotangent() const noexcept
	{
		return Vector4(
			1.0f / tan(x),
			1.0f / tan(y),
			1.0f / tan(z),
			1.0f / tan(w));
	}

	Vector2 Vector4::getVector2() const noexcept
	{
		return Vector2(x, y);
	}
	Vector3 Vector4::getVector3() const noexcept
	{
		return Vector3(x, y, z);
	}

	bool Vector4::operator==(const Vector4& vector) const noexcept
	{
		return cmpeq(*this, vector);
	}
	bool Vector4::operator!=(const Vector4& vector) const noexcept
	{
		return cmpneq(*this, vector);
	}
	bool Vector4::operator<=(const Vector4& vector) const noexcept
	{
		return cmple(*this, vector);
	}
	bool Vector4::operator>=(const Vector4& vector) const noexcept
	{
		return cmpge(*this, vector);
	}
	bool Vector4::operator<(const Vector4& vector) const noexcept
	{
		return cmplt(*this, vector);
	}
	bool Vector4::operator>(const Vector4& vector) const noexcept
	{
		return cmpgt(*this, vector);
	}

	Vector4& Vector4::operator--() noexcept
	{
		return *this = sub1(*this, 1);
	}
	Vector4& Vector4::operator++() noexcept
	{
		return *this = add1(*this, 1);
	}
	Vector4 Vector4::operator--(int) noexcept
	{
		auto result = Vector4(*this);
		*this = sub1(*this, 1);
		return result;
	}
	Vector4 Vector4::operator++(int) noexcept
	{
		auto result = Vector4(*this);
		*this = add1(*this, 1);
		return result;
	}
	Vector4 Vector4::operator-() const noexcept
	{
		return mul(*this, -1);
	}

	Vector4 Vector4::operator-(const Vector4& vector) const noexcept
	{
		return sub(*this, vector);
	}
	Vector4 Vector4::operator+(const Vector4& vector) const noexcept
	{
		return add(*this, vector);
	}
	Vector4 Vector4::operator/(const Vector4& vector) const noexcept
	{
		return div(*this, vector);
	}
	Vector4 Vector4::operator*(const Vector4& vector) const noexcept
	{
		return mul(*this, vector);
	}
	Vector4& Vector4::operator-=(const Vector4& vector) noexcept
	{
		return *this = sub(*this, vector);
	}
	Vector4& Vector4::operator+=(const Vector4& vector) noexcept
	{
		return *this = add(*this, vector);
	}
	Vector4& Vector4::operator/=(const Vector4& vector) noexcept
	{
		return *this = div(*this, vector);
	}
	Vector4& Vector4::operator*=(const Vector4& vector) noexcept
	{
		return *this = mul(*this, vector);
	}

	Vector4 Vector4::operator-(const IntVector4& vector) const noexcept
	{
		return sub(*this, Vector4(vector));
	}
	Vector4 Vector4::operator+(const IntVector4& vector) const noexcept
	{
		return add(*this, Vector4(vector));
	}
	Vector4 Vector4::operator/(const IntVector4& vector) const noexcept
	{
		return div(*this, Vector4(vector));
	}
	Vector4 Vector4::operator*(const IntVector4& vector) const noexcept
	{
		return mul(*this, Vector4(vector));
	}
	Vector4& Vector4::operator-=(const IntVector4& vector) noexcept
	{
		return *this = sub(*this, Vector4(vector));
	}
	Vector4& Vector4::operator+=(const IntVector4& vector) noexcept
	{
		return *this = add(*this, Vector4(vector));
	}
	Vector4& Vector4::operator/=(const IntVector4& vector) noexcept
	{
		return *this = div(*this, Vector4(vector));
	}
	Vector4& Vector4::operator*=(const IntVector4& vector) noexcept
	{
		return *this = mul(*this, Vector4(vector));
	}

	Vector4 Vector4::operator-(float value) const noexcept
	{
		return sub(*this, value);
	}
	Vector4 Vector4::operator+(float value) const noexcept
	{
		return add(*this, value);
	}
	Vector4 Vector4::operator/(float value) const noexcept
	{
		return div(*this, value);
	}
	Vector4 Vector4::operator*(float value) const noexcept
	{
		return mul(*this, value);
	}
	Vector4& Vector4::operator-=(float value) noexcept
	{
		return *this = sub(*this, value);
	}
	Vector4& Vector4::operator+=(float value) noexcept
	{
		return *this = add(*this, value);
	}
	Vector4& Vector4::operator/=(float value) noexcept
	{
		return *this = div(*this, value);
	}
	Vector4& Vector4::operator*=(float value) noexcept
	{
		return *this = mul(*this, value);
	}

	void Vector4::initialize()
	{
		if (CpuInfo::hasSSE())
		{
			cmpeq = cmpeqSSE;
			cmpneq = cmpneqSSE;
			cmple = cmpleSSE;
			cmpge = cmpgeSSE;
			cmplt = cmpltSSE;
			cmpgt = cmpgtSSE;
			sub = subSSE;
			add = addSSE;
			div = divSSE;
			mul = mulSSE;
		}
		else
		{
			cmpeq = cmpeqRAW;
			cmpneq = cmpneqRAW;
			cmple = cmpleRAW;
			cmpge = cmpgeRAW;
			cmplt = cmpltRAW;
			cmpgt = cmpgtRAW;
			sub = subRAW;
			add = addRAW;
			div = divRAW;
			mul = mulRAW;
		}
	}

	const Vector4 Vector4::zero = Vector4(0.0f);
	const Vector4 Vector4::minusOne = Vector4(-1.0f);
	const Vector4 Vector4::one = Vector4(1.0f);
}
