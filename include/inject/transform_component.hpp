#pragma once
#include <entityx/entityx.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace inject
{
	struct TransformComponent final : public entityx::Component<TransformComponent>
	{
		enum class Type
		{
			Spin,
			Orbit,
		};

		Type type;
		glm::vec3 scale;
		glm::vec3 position;
		glm::quat rotation;
		glm::mat4 matrix;
		bool changed;

		TransformComponent(const Type _type = Type::Spin,
			const glm::vec3& _scale = glm::vec3(1.0f),
			const glm::vec3& _position = glm::vec3(),
			const glm::quat& _rotation = glm::quat(glm::vec3()),
			const glm::mat4& _matrix = glm::mat4(),
			const bool _changed = true) :
			type(_type),
			scale(_scale),
			position(_position),
			rotation(_rotation),
			matrix(_matrix),
			changed(_changed)
		{}
	};
}
