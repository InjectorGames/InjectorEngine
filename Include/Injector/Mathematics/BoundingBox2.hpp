#pragma once
#include "Injector/Mathematics/Vector2.hpp"

namespace Injector
{
	struct BoundingBox2 final
	{
		FloatVector2 minimum;
		FloatVector2 maximum;

		BoundingBox2(
			const FloatVector2& minimum,
			const FloatVector2& maximum) noexcept;

		void setCenterAndSize(
			const FloatVector2& center,
			const FloatVector2& size) noexcept;
		void setCenterAndExtent(
			const FloatVector2& center,
			const FloatVector2& extent) noexcept;

		void resize(
			const FloatVector2& offset) noexcept;

		bool isColliding(
			const FloatVector2& point) const noexcept;
		bool isColliding(
			const BoundingBox2& box) const noexcept;

		static BoundingBox2 createCenterAndSize(
			const FloatVector2& center,
			const FloatVector2& size) noexcept;
		static BoundingBox2 createCenterAndExtent(
			const FloatVector2& center,
			const FloatVector2& extent) noexcept;

		// [-0.5f, 0.5f]
		static const BoundingBox2 one;
	};
}