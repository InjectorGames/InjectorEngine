#include "Injector/Mathematics/BoundingBox2.hpp"

namespace Injector
{
	BoundingBox2::BoundingBox2(
		const FloatVector2& _minimum,
		const FloatVector2& _maximum) noexcept :
		minimum(_minimum),
		maximum(_maximum)
	{
	}

	void BoundingBox2::setCenterAndSize(
		const FloatVector2& center,
		const FloatVector2& size) noexcept
	{
		auto half = size / 2.0f;
		minimum = center - half;
		maximum = center + half;
	}
	void BoundingBox2::setCenterAndExtent(
		const FloatVector2& center,
		const FloatVector2& extent) noexcept
	{
		minimum = center - extent;
		maximum = center + extent;
	}

	void BoundingBox2::resize(
		const FloatVector2& offset) noexcept
	{
		minimum -= offset;
		maximum += offset;
	}

	bool BoundingBox2::isColliding(
		const FloatVector2& point) const noexcept
	{
		return
			minimum.x <= point.x && maximum.x >= point.x &&
			minimum.y <= point.y && maximum.y >= point.y;
	}
	bool BoundingBox2::isColliding(
		const BoundingBox2& box) const noexcept
	{
		return
			minimum.x <= box.maximum.x && maximum.x >= box.minimum.x &&
			minimum.y <= box.maximum.y && maximum.y >= box.minimum.y;
	}

	BoundingBox2 BoundingBox2::createCenterAndSize(
		const FloatVector2& center,
		const FloatVector2& size) noexcept
	{
		auto half = size / 2.0f;

		return BoundingBox2(
			center - half,
			center + half);
	}
	BoundingBox2 BoundingBox2::createCenterAndExtent(
		const FloatVector2& center,
		const FloatVector2& extent) noexcept
	{
		return BoundingBox2(
			center - extent,
			center + extent);
	}

	const BoundingBox2 BoundingBox2::one = BoundingBox2(
		Vector2(-0.5f),
		Vector2(0.5f));
}
