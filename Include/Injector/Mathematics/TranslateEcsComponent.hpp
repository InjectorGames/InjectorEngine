#pragma once
#include "Injector/ECS/EcsComponent.hpp"
#include "Injector/Mathematics/Vector3.hpp"

namespace Injector
{
	struct TranslateEcsComponent final : public EcsComponent
	{
		FloatVector3 translation;

		explicit TranslateEcsComponent(
			const FloatVector3& translation = FloatVector3()) noexcept;
	};
}