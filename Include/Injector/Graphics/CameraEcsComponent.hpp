#pragma once
#include "Injector/ECS/EcsComponent.hpp"
#include "Injector/ECS/EcsEntity.hpp"
#include "Injector/Graphics/CameraType.hpp"
#include "Injector/Mathematics/Matrix4.hpp"
#include "Injector/Mathematics/Angle.hpp"

#include <set>
#include <memory>

namespace Injector
{
	// Camera ECS component structure
	struct CameraEcsComponent final : public EcsComponent
	{
		// Camera component render queue value
		int renderQueue;
		// Camera component type value
		CameraType type;
		// Camera component field of view value
		float fieldOfView;
		// Camera component frustum value
		FloatVector4 frustum;
		// Camera component clip plane value
		FloatVector2 clipPlane;
		// Camera component aspect ratio value
		float aspectRatio;
		// Camera component projection matrix value
		FloatMatrix4 matrix;
		// Is camera component should be rendered
		bool render;
		// Camera component render container
		std::set<std::shared_ptr<EcsEntity>> renders;

		// Creates a new camera ECS component
		explicit CameraEcsComponent(
			int queue = 0,
			CameraType type = CameraType::Perspective,
			float fieldOfView = Angle::toRadians(60.0f),
			const FloatVector4& frustum = FloatVector4(-1.0f, 1.0f, -1.0f, 1.0f),
			const FloatVector2& clipPlane = FloatVector2(0.01f, 1000.0f),
			float aspectRatio = 1.0f,
			bool render = true,
			const FloatMatrix4& matrix = FloatMatrix4(),
			const std::set<std::shared_ptr<EcsEntity>>& renders = {}) noexcept;
	};
}
