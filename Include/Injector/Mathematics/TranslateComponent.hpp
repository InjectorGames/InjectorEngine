#pragma once
#include "Injector/ECS/Component.hpp"
#include "Injector/Mathematics/Vector/Vector3.hpp"

namespace Injector
{
	struct TranslateComponent : public Component
	{
		Vector3 translation;

		TranslateComponent(
			const Vector3& translation =
				Vector3::one) noexcept;
	};
}