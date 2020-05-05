#pragma once
#include <entityx/entityx.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace njng
{
	struct TransformComponent final : public entityx::Component<TransformComponent>
	{
		glm::vec3 scale;
		glm::vec3 position;
		glm::quat rotation;
		glm::mat4 matrix;
		bool changed;
	};
}
