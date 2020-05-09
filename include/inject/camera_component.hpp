#pragma once
#include <entityx/entityx.h>
#include <glm/glm.hpp>

#include <cstdio>

namespace inject
{
	struct CameraComponent final : entityx::Component<CameraComponent>
	{
		enum class Type
		{
			Perspective,
			Orthographic,
		};

		Type type;
		int renderQueue;
		float fieldOfView;
		float aspectRatio;
		bool updateAspectRatio;
		glm::vec4 frustum;
		glm::vec2 clipPlane;
		glm::mat4 projMatrix;
		bool projChanged;

		CameraComponent(const Type _type = Type::Perspective,
			const int _renderQueue = 0,
			const float _fieldOfView = glm::radians(60.0f),
			const float _aspectRatio = 4.0f / 3.0f,
			const bool _updateAspectRatio = true,
			const glm::vec4 _frustum = glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f),
			const glm::vec2 _clipPlane = glm::vec2(0.01f, 1000.0f),
			const glm::mat4 _projMatrix = glm::mat4(1.0f),
			const bool _projChanged = true) :
			type(_type),
			renderQueue(_renderQueue),
			fieldOfView(_fieldOfView),
			aspectRatio(_aspectRatio),
			updateAspectRatio(_updateAspectRatio),
			frustum(_frustum),
			clipPlane(_clipPlane),
			projMatrix(_projMatrix),
			projChanged(_projChanged)
		{}
	};
}
