#pragma once
#include <entityx/entityx.h>
#include <glm/glm.hpp>

namespace njng
{
	struct TranslateComponent final : public entityx::Component<TranslateComponent>
	{
		glm::vec3 translation;
	};
}
