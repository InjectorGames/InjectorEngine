#pragma once
#include <inject/glm_defines.hpp>
#include <entityx/entityx.h>

namespace inject
{
	struct TranslateComponent final : public entityx::Component<TranslateComponent>
	{
		glm::vec3 translation;

		TranslateComponent(const glm::vec3& _translation = glm::vec3(0.0f)) :
			translation(_translation)
		{}
	};
}
