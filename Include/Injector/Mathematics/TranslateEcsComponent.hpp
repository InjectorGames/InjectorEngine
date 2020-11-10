#pragma once
#include "Injector/ECS/EcsComponent.hpp"
#include "Injector/Mathematics/Vector/Vector3.hpp"

namespace Injector
{
	struct TranslateEcsComponent final : public EcsComponent
	{
		Vector3 translation;

		explicit TranslateEcsComponent(
			const Vector3& translation = Vector3::one) noexcept;
	};
}