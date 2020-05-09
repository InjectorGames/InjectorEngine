#pragma once
#include <entityx/entityx.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

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
		float aspectRatio;
		float fieldOfView;
		bool updateAspectRatio;
		bool viewChanged;
		bool projChanged;
		glm::vec2 clipPlane;
		glm::vec3 scale;
		glm::vec3 position;
		glm::vec4 frustum;
		glm::quat rotation;
		glm::mat4 viewMatrix;
		glm::mat4 projMatrix;

		CameraComponent(const Type _type = Type::Perspective,
			const int _renderQueue = 0,
			const float _aspectRatio = 1.0f,
			const float _fieldOfView = glm::radians(60.0f),
			const bool _updateAspectRatio = true,
			const bool _viewChanged = true,
			const bool _projChanged = true,
			const glm::vec2 _clipPlane = glm::vec2(0.01f, 1000.0f),
			const glm::vec3 _scale = glm::vec3(1.0f),
			const glm::vec3 _position = glm::vec3(0.0f),
			const glm::vec4 _frustum = glm::vec4(-1.0f, 1.0f, -1.0f, 1.0f),
			const glm::quat _rotation = glm::quat(glm::vec3(0.0f)),
			const glm::mat4 _viewMatrix = glm::mat4(1.0f),
			const glm::mat4 _projMatrix = glm::mat4(1.0f)) :
			type(_type),
			renderQueue(_renderQueue),
			aspectRatio(_aspectRatio),
			fieldOfView(_fieldOfView),
			updateAspectRatio(_updateAspectRatio),
			viewChanged(_viewChanged),
			projChanged(_projChanged),
			clipPlane(_clipPlane),
			scale(_scale),
			position(_position),
			frustum(_frustum),
			rotation(_rotation),
			viewMatrix(_viewMatrix),
			projMatrix(_projMatrix)
		{}
	};
}
