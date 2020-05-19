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
	struct PerspCameraComponent final : entityx::Component<PerspCameraComponent>
	{
		int queue;
		float aspectRatio;
		float fieldOfView;
		bool updateAspectRatio;
		glm::vec2 clipPlane;
		glm::mat4 matrix;
		bool changed;

		PerspCameraComponent(const int _queue = 0,
			const float _aspectRatio = 1.0f,
			const float _fieldOfView = glm::radians(60.0f),
			const bool _updateAspectRatio = true,
			const glm::vec2& _clipPlane = glm::vec2(0.01f, 1000.0f),
			const glm::mat4& _matrix = glm::mat4(1.0f),
			const bool _changed = true) :
			queue(_queue),
			aspectRatio(_aspectRatio),
			fieldOfView(_fieldOfView),
			updateAspectRatio(_updateAspectRatio),
			clipPlane(_clipPlane),
			matrix(_matrix),
			changed(_changed)
		{}
	};
}
