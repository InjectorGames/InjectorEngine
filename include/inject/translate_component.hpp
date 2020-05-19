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
	struct TranslateComponent final : public entityx::Component<TranslateComponent>
	{
		glm::vec3 translation;

		TranslateComponent(const glm::vec3& _translation = glm::vec3(0.0f)) :
			translation(_translation)
		{}
	};
}
