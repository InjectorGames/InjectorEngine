#pragma once
#include "BoundingBox3.hpp"

namespace Injector
{
	struct BoundingSphere3 final
	{
		Vector3 center;
		float radius;

		BoundingSphere3(
			Vector3 center,
			float radius) noexcept;

		bool isColliding(
			const Vector3& point) const noexcept;
		bool isColliding(
			const BoundingSphere3& sphere) const noexcept;
		bool isColliding(
			const BoundingBox3& box) const noexcept;
	};
}