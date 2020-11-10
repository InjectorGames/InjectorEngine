#pragma once
#include "Injector/Mathematics/Vector/Vector3.hpp"

namespace Injector
{
	struct BoundingBox3 final
	{
		Vector3 minimum;
		Vector3 maximum;

		BoundingBox3(
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
			const Vector3& point) const noexcept;
		bool isColliding(
			const BoundingBox3& box) const noexcept;

		static BoundingBox3 createCenterAndSize(
			const Vector3& center,
			const Vector3& size) noexcept;
		static BoundingBox3 createCenterAndExtent(
			const Vector3& center,
			const Vector3& extent) noexcept;

		// [-0.5f, 0.5f]
		static const BoundingBox3 one;
	};
}