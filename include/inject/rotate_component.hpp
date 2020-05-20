#pragma once
#include <inject/glm_defines.hpp>
#include <entityx/entityx.h>

namespace inject
{
	struct RotateComponent final : public entityx::Component<RotateComponent>
	{
		glm::vec3 rotation;

		RotateComponent(const glm::vec3& _rotation = glm::vec3(0.0f)) :
			rotation(_rotation)
		{}
	};
}