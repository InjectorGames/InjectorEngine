#pragma once
#include <entityx/entityx.h>

#define GLM_FORCE_CXX17
#define GLM_FORCE_INLINE
#define GLM_FORCE_INTRINSICS
#define GLM_FORCE_LEFT_HANDED
#define GLM_FORCE_ALIGNED_GENTYPES
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
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
		entityx::Entity parent;
		glm::vec3 scale;
		glm::vec3 position;
		glm::quat rotation;
		glm::mat4 matrix;
		bool changed;

		TransformComponent(const Type _type = Type::Spin,
			const entityx::Entity& _parent = entityx::Entity(),
			const glm::vec3& _scale = glm::vec3(1.0f),
			const glm::vec3& _position = glm::vec3(0.0f),
			const glm::quat& _rotation = glm::quat(glm::vec3(0.0f)),
			const glm::mat4& _matrix = glm::mat4(1.0f),
			const bool _changed = true) :
			type(_type),
			parent(_parent),
			scale(_scale),
			position(_position),
			rotation(_rotation),
			matrix(_matrix),
			changed(_changed)
		{}
	};
}
