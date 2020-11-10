#include "Injector/Mathematics/Bounding/BoundingBox3.hpp"

namespace Injector
{
	BoundingBox3::BoundingBox3(
		const Vector3& _minimum,
		const Vector3& _maximum) noexcept :
		minimum(_minimum),
		maximum(_maximum)
	{
	}

	void BoundingBox3::setCenterAndSize(
		const Vector3& center,
		const Vector3& size) noexcept
	{
		auto half = size / 2.0f;
		minimum = center - half;
		maximum = center + half;
	}
	void BoundingBox3::setCenterAndExtent(
		const Vector3& center,
		const Vector3& extent) noexcept
	{
		minimum = center - extent;
		maximum = center + extent;
	}

	void BoundingBox3::resize(
		const Vector3& offset) noexcept
	{
		minimum -= offset;
		maximum += offset;
	}

	bool BoundingBox3::isColliding(
		const Vector3& point) const noexcept
	{
		return
			minimum.x <= point.x && maximum.x >= point.x &&
			minimum.y <= point.y && maximum.y >= point.y &&
			minimum.z <= point.z && maximum.z >= point.z;
	}
	bool BoundingBox3::isColliding(
		const BoundingBox3& box)  const noexcept
	{
		return
			minimum.x <= box.maximum.x && maximum.x >= box.minimum.x &&
			minimum.y <= box.maximum.y && maximum.y >= box.minimum.y &&
			minimum.z <= box.maximum.z && maximum.z >= box.minimum.z;
	}

	BoundingBox3 BoundingBox3::createCenterAndSize(
		const Vector3& center,
		const Vector3& size) noexcept
	{
		auto half = size / 2.0f;

		return BoundingBox3(
			center - half,
			center + half);
	}
	BoundingBox3 BoundingBox3::createCenterAndExtent(
		const Vector3& center,
		const Vector3& extent) noexcept
	{
		return BoundingBox3(
			center - extent,
			center + extent);
	}

	const BoundingBox3 BoundingBox3::one = BoundingBox3(
		-Vector3::half, Vector3::half);
}
