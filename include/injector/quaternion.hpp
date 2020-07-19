#pragma once
#include <injector/vector3.hpp>

namespace INJECTOR_NAMESPACE
{
	struct Quaternion
	{
		float x, y, z, w;

		Quaternion(float x = 0.0f, float y = 0.0f, float z = 0.0f, float w = 0.0f);
		Quaternion(const Vector3& other, float w = 0.0f);
		Quaternion(const Vector3& eulerAngles);

		bool operator==(const Quaternion& other) const noexcept;
		bool operator!=(const Quaternion& other) const noexcept;

		float getMagnitude() const noexcept;
		float getDot(const Quaternion& other) const noexcept;
		Quaternion getNormalized() const noexcept;
		Quaternion getCross(const Quaternion& other) const noexcept;
	};
}