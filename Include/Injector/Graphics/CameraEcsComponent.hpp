#pragma once
#include "Injector/ECS/EcsComponent.hpp"
#include "Injector/ECS/EcsEntity.hpp"
#include "Injector/Graphics/CameraType.hpp"
#include "Injector/Mathematics/Matrix/Matrix4.hpp"
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
		Vector4 frustum;
		// Camera component clip plane value
		Vector2 clipPlane;
		// Camera component aspect ratio value
		float aspectRatio;
		// Camera component projection matrix value
		Matrix4 matrix;
		// Is camera component should be rendered
		bool render;
		// Camera component render container
		std::set<std::shared_ptr<EcsEntity>> renders;

		// Creates a new camera ECS component
		explicit CameraEcsComponent(
			int queue = 0,
			CameraType type = CameraType::Perspective,
			float fieldOfView = Angle::toRadians(60.0f),
			const Vector4& frustum = Vector4(-1.0f, 1.0f, -1.0f, 1.0f),
			const Vector2& clipPlane = Vector2(0.01f, 1000.0f),
			float aspectRatio = 1.0f,
			bool render = true,
			const Matrix4& matrix = Matrix4::identity,
			const std::set<std::shared_ptr<EcsEntity>>& renders = {}) noexcept;
	};
}
