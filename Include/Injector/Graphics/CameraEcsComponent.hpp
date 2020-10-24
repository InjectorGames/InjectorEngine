#pragma once
#include "Injector/ECS/EcsComponent.hpp"
#include "Injector/ECS/EcsEntity.hpp"
#include "Injector/Graphics/CameraType.hpp"
#include "Injector/Mathematics/Matrix/Matrix4.hpp"
#include "Injector/Mathematics/Converter.hpp"

#include <set>
#include <memory>

namespace Injector
{
	struct CameraEcsComponent final : public EcsComponent
	{
		int queue;
		CameraType type;
		float fieldOfView;
		Vector4 frustum;
		Vector2 clipPlane;
		float aspectRatio;
		Matrix4 matrix;
		bool render;
		std::set<std::shared_ptr<EcsEntity>> renders;

		explicit CameraEcsComponent(
			int queue = 0,
			CameraType type = CameraType::Perspective,
			float fieldOfView = Converter::toRadians(60.0f),
			const Vector4& frustum = Vector4(-1.0f, 1.0f, -1.0f, 1.0f),
			const Vector2& clipPlane = Vector2(0.01f, 1000.0f),
			float aspectRatio = 1.0f,
			bool render = true,
			const Matrix4& matrix = Matrix4::identity,
			const std::set<std::shared_ptr<EcsEntity>>& renders = {}) noexcept;
	};
}
