#pragma once
#include "BoundingBox3.hpp"

namespace Injector
{
	struct BoundingSphere3 final
	{
		FloatVector3 center;
		float radius;

		BoundingSphere3(
			FloatVector3 center,
			float radius) noexcept;

		bool isColliding(
			const FloatVector3& point) const noexcept;
		bool isColliding(
			const BoundingSphere3& sphere) const noexcept;
		bool isColliding(
			const BoundingBox3& box) const noexcept;
	};
}