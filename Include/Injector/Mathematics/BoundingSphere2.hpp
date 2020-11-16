#pragma once
#include "BoundingBox2.hpp"

namespace Injector
{
	struct BoundingSphere2 final
	{
		FloatVector2 center;
		float radius;

		BoundingSphere2(
			FloatVector2 center,
			float radius) noexcept;

		bool isColliding(
			const FloatVector2& point) const noexcept;
		bool isColliding(
			const BoundingSphere2& sphere) const noexcept;
		bool isColliding(
			const BoundingBox2& box) const noexcept;
	};
}