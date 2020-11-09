#include "Injector/Mathematics/BoundingBox.hpp"

namespace Injector
{
	BoundingBox::BoundingBox(
		const Vector3& _minimum,
		const Vector3& _maximum) noexcept :
		minimum(_minimum),
		maximum(_maximum)
	{
	}

	void BoundingBox::setCenterAndSize(
		const Vector3& center,
		const Vector3& size) noexcept
	{
		auto half = size / 2.0f;
		minimum = center - half;
		maximum = center + half;
	}
	void BoundingBox::setCenterAndExtent(
		const Vector3& center,
		const Vector3& extent) noexcept
	{
		minimum = center - extent;
		maximum = center + extent;
	}

	void BoundingBox::resize(
		const Vector3& offset) noexcept
	{
		minimum -= offset;
		maximum += offset;
	}

	bool BoundingBox::isColliding(
		const Vector3& point) noexcept
	{
		return
			minimum.x <= point.x && maximum.x >= point.x &&
			minimum.y <= point.y && maximum.y >= point.y &&
			minimum.z <= point.z && maximum.z >= point.z;
	}
	bool BoundingBox::isColliding(
		const BoundingBox& box) noexcept
	{
		return
			minimum.x <= box.maximum.x && maximum.x >= box.minimum.x &&
			minimum.y <= box.maximum.y && maximum.y >= box.minimum.y &&
			minimum.z <= box.maximum.z && maximum.z >= box.minimum.z;
	}
}
