#pragma once
#include "Injector/Component.hpp"
#include "Injector/Mathematics/Quaternion.hpp"

namespace Injector
{
	struct RotateComponent : public Component
	{
		Quaternion rotation;

		RotateComponent(
			const Quaternion& rotation =
				Quaternion(Vector3::one)) noexcept;
	};
}