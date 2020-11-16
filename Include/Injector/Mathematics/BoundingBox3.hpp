#pragma once
#include "Injector/Mathematics/Vector3.hpp"

namespace Injector
{
	struct BoundingBox3 final
	{
		FloatVector3 minimum;
		FloatVector3 maximum;

		BoundingBox3(
			const FloatVector3& minimum,
			const FloatVector3& maximum) noexcept;

		void setCenterAndSize(
			const FloatVector3& center,
			const FloatVector3& size) noexcept;
		void setCenterAndExtent(
			const FloatVector3& center,
			const FloatVector3& extent) noexcept;

		void resize(
			const FloatVector3& offset) noexcept;

		bool isColliding(
			const FloatVector3& point) const noexcept;
		bool isColliding(
			const BoundingBox3& box) const noexcept;

		static BoundingBox3 createCenterAndSize(
			const FloatVector3& center,
			const FloatVector3& size) noexcept;
		static BoundingBox3 createCenterAndExtent(
			const FloatVector3& center,
			const FloatVector3& extent) noexcept;

		// [-0.5f, 0.5f]
		static const BoundingBox3 one;
	};
}