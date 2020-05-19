#pragma once
#include <entityx/entityx.h>

#define GLM_FORCE_CXX17
#define GLM_FORCE_INLINE
#define GLM_FORCE_INTRINSICS
#define GLM_FORCE_LEFT_HANDED
#define GLM_FORCE_ALIGNED_GENTYPES
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#include <glm/glm.hpp>

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