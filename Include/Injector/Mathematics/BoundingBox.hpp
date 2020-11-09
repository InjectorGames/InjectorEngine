#pragma once
#include "Injector/Mathematics/Vector/Vector3.hpp"

namespace Injector
{
	struct BoundingBox
	{
		Vector3 position;
		Vector3 size;

		BoundingBox(
			const Vector3& position,
			const Vector3& size);

		bool isColliding(
			const BoundingBox& box) noexcept;
		bool isColliding(
			const Vector3& point) noexcept;
	};
}