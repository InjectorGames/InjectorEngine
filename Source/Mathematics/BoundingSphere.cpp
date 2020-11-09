#include "Injector/Mathematics/BoundingSphere.hpp"

namespace Injector
{
	BoundingSphere::BoundingSphere(
		Vector3 _center,
		float _radius) noexcept :
		center(_center),
		radius(_radius)
	{
	}

	bool BoundingSphere::isColliding(
		const Vector3& point) noexcept
	{
		return center.getDotProduct(center - point) < radius * radius;
	}
	bool BoundingSphere::isColliding(
		const BoundingSphere& sphere) noexcept
	{
		return
			center.getDotProduct(center - sphere.center) <
			(radius + sphere.radius) * (radius + sphere.radius);
	}
	bool BoundingSphere::isColliding(
		const BoundingBox& box) noexcept
	{
		auto point = Vector3(
			std::max(box.minimum.x, std::min(center.x, box.maximum.x)),
			std::max(box.minimum.y, std::min(center.y, box.maximum.y)),
			std::max(box.minimum.z, std::min(center.z, box.maximum.z)));
		return center.getDotProduct(center - point) < radius * radius;
	}
}
