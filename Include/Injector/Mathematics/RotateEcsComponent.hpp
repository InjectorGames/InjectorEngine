#pragma once
#include "Injector/ECS/EcsComponent.hpp"
#include "Injector/Mathematics/Quaternion.hpp"

namespace Injector
{
	struct RotateEcsComponent : public EcsComponent
	{
		Quaternion rotation;

		RotateEcsComponent(
			const Quaternion& rotation = Quaternion::zero) noexcept;
	};
}