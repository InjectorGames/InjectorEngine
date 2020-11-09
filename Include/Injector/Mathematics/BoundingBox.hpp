#pragma once
#include "Injector/Mathematics/Vector/Vector3.hpp"

namespace Injector
{
	struct BoundingBox
	{
		Vector3 minimum;
		Vector3 maximum;

		BoundingBox(
			const Vector3& minimum,
			const Vector3& maximum) noexcept;

		void setCenterAndSize(
			const Vector3& center,
			const Vector3& size) noexcept;
		void setCenterAndExtent(
			const Vector3& center,
			const Vector3& extent) noexcept;

		void resize(
			const Vector3& offset) noexcept;

		bool isColliding(
			const Vector3& point) noexcept;
		bool isColliding(
			const BoundingBox& box) noexcept;
	};
}