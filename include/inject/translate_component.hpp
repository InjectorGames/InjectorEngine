#pragma once
#include <entityx/entityx.h>
#include <glm/glm.hpp>

namespace inject
{
	struct TranslateComponent final : public entityx::Component<TranslateComponent>
	{
		glm::vec3 translation;

		TranslateComponent(const glm::vec3& _translation = glm::vec3()) :
			translation(_translation)
		{}
	};
}
