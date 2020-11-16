#include "Injector/Mathematics/BoundingSphere3.hpp"

namespace Injector
{
	BoundingSphere3::BoundingSphere3(
		FloatVector3 _center,
		float _radius) noexcept :
		center(_center),
		radius(_radius)
	{
	}

	bool BoundingSphere3::isColliding(
		const FloatVector3& point) const noexcept
	{
		return center.getDotProduct(center - point) <= radius * radius;
	}
	bool BoundingSphere3::isColliding(
		const BoundingSphere3& sphere) const noexcept
	{
		return
			center.getDotProduct(center - sphere.center) <=
			(radius + sphere.radius) * (radius + sphere.radius);
	}
	bool BoundingSphere3::isColliding(
		const BoundingBox3& box) const noexcept
	{
		auto point = Vector3(
			std::max(box.minimum.x, std::min(center.x, box.maximum.x)),
			std::max(box.minimum.y, std::min(center.y, box.maximum.y)),
			std::max(box.minimum.z, std::min(center.z, box.maximum.z)));
		return center.getDotProduct(center - point) <= radius * radius;
	}
}
