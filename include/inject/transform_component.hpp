#pragma once
#include <entityx/entityx.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace inject
{
	struct TransformComponent final : public entityx::Component<TransformComponent>
	{
		glm::vec3 scale;
		glm::vec3 position;
		glm::quat rotation;
		glm::mat4 matrix;
		bool changed;

		TransformComponent(const glm::vec3 _scale = glm::vec3(1.0f),
			const glm::vec3 _position = glm::vec3(0.0f),
			const glm::quat _rotation = glm::quat(glm::vec3(0.0f)),
			const glm::mat4 _matrix = glm::mat4(1.0f),
			const bool _changed = true) :
			scale(_scale),
			position(_position),
			rotation(_rotation),
			matrix(_matrix),
			changed(_changed)
		{}
	};
}
