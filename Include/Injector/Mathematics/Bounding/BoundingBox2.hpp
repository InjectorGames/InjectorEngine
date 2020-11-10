#pragma once
#include "Injector/Mathematics/Vector/Vector2.hpp"

namespace Injector
{
	struct BoundingBox2 final
	{
		Vector2 minimum;
		Vector2 maximum;

		BoundingBox2(
			const Vector2& minimum,
			const Vector2& maximum) noexcept;

		void setCenterAndSize(
			const Vector2& center,
			const Vector2& size) noexcept;
		void setCenterAndExtent(
			const Vector2& center,
			const Vector2& extent) noexcept;

		void resize(
			const Vector2& offset) noexcept;

		bool isColliding(
			const Vector2& point) const noexcept;
		bool isColliding(
			const BoundingBox2& box) const noexcept;

		static BoundingBox2 createCenterAndSize(
			const Vector2& center,
			const Vector2& size) noexcept;
		static BoundingBox2 createCenterAndExtent(
			const Vector2& center,
			const Vector2& extent) noexcept;

		// [-0.5f, 0.5f]
		static const BoundingBox2 one;
	};
}