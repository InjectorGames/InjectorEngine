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
	struct OrthoCameraComponent final : entityx::Component<OrthoCameraComponent>
	{
		int queue;
		glm::vec4 frustum;
		glm::vec2 clipPlane;
		bool changed;
		glm::mat4 matrix;

		OrthoCameraComponent(const int _queue = 0,
			const glm::vec4& _frustum = glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f),
			const glm::vec2& _clipPlane = glm::vec2(-1.0f, 1.0f),
			const glm::mat4& _matrix = glm::mat4(1.0f),
			const bool _changed = true) :
			queue(_queue),
			frustum(_frustum),
			clipPlane(_clipPlane),
			matrix(_matrix),
			changed(_changed)
		{}
	};
}
