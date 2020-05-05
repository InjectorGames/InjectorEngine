#pragma once
#include <entityx/entityx.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace njng
{
	struct RotateComponent final : public entityx::Component<RotateComponent>
	{
		glm::vec3 rotation;
	};
}