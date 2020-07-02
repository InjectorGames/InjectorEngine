#pragma once
#include <inject/defines.hpp>
#include <inject/glm_defines.hpp>
#include <entityx/entityx.h>

namespace INJECT_NAMESPACE
{
	struct PerspCameraComponent final :
		entityx::Component<PerspCameraComponent>
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
