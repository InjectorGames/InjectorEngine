#pragma once
#include "Injector/Mathematics/BoundingBox.hpp"

namespace Injector
{
	struct BoundingSphere
	{
		Vector3 center;
		float radius;

		BoundingSphere(
			Vector3 center,
			float radius) noexcept;

		bool isColliding(
			const Vector3& point) noexcept;
		bool isColliding(
			const BoundingSphere& sphere) noexcept;
		bool isColliding(
			const BoundingBox& box) noexcept;
	};
}