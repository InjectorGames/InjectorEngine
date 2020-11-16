#include "Injector/Mathematics/BoundingSphere2.hpp"

namespace Injector
{
	BoundingSphere2::BoundingSphere2(
		FloatVector2 _center,
		float _radius) noexcept :
		center(_center),
		radius(_radius)
	{
	}

	bool BoundingSphere2::isColliding(
		const FloatVector2& point) const noexcept
	{
		return center.getDotProduct(center - point) <= radius * radius;
	}
	bool BoundingSphere2::isColliding(
		const BoundingSphere2& sphere) const noexcept
	{
		return
			center.getDotProduct(center - sphere.center) <=
			(radius + sphere.radius) * (radius + sphere.radius);
	}
	bool BoundingSphere2::isColliding(
		const BoundingBox2& box) const noexcept
	{
		auto point = Vector2(
			std::max(box.minimum.x, std::min(center.x, box.maximum.x)),
			std::max(box.minimum.y, std::min(center.y, box.maximum.y)));
		return center.getDotProduct(center - point) <= radius * radius;
	}
}
