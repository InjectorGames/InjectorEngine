#include "Injector/Mathematics/Bounding/BoundingBox2.hpp"

namespace Injector
{
	BoundingBox2::BoundingBox2(
		const Vector2& _minimum,
		const Vector2& _maximum) noexcept :
		minimum(_minimum),
		maximum(_maximum)
	{
	}

	void BoundingBox2::setCenterAndSize(
		const Vector2& center,
		const Vector2& size) noexcept
	{
		auto half = size / 2.0f;
		minimum = center - half;
		maximum = center + half;
	}
	void BoundingBox2::setCenterAndExtent(
		const Vector2& center,
		const Vector2& extent) noexcept
	{
		minimum = center - extent;
		maximum = center + extent;
	}

	void BoundingBox2::resize(
		const Vector2& offset) noexcept
	{
		minimum -= offset;
		maximum += offset;
	}

	bool BoundingBox2::isColliding(
		const Vector2& point) const noexcept
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
		const Vector2& center,
		const Vector2& size) noexcept
	{
		auto half = size / 2.0f;

		return BoundingBox2(
			center - half,
			center + half);
	}
	BoundingBox2 BoundingBox2::createCenterAndExtent(
		const Vector2& center,
		const Vector2& extent) noexcept
	{
		return BoundingBox2(
			center - extent,
			center + extent);
	}

	const BoundingBox2 BoundingBox2::one = BoundingBox2(
		-Vector2::half, Vector2::half);
}
