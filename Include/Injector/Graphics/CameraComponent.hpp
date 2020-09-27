#pragma once
#include "Injector/Component.hpp"
#include "Injector/Entity.hpp"
#include "Injector/Graphics/CameraType.hpp"
#include "Injector/Mathematics/Matrix4.hpp"
#include "Injector/Mathematics/Converter.hpp"

#include <set>
#include <memory>

namespace Injector
{
	struct CameraComponent : public Component
	{
		int queue;
		CameraType type;
		float aspectRatio;
		bool updateAspect;
		float fieldOfView;
		Vector4 frustum;
		Vector2 clipPlane;
		Matrix4 matrix;
		bool render;
		std::set<std::shared_ptr<Entity>> renders;

		CameraComponent(
			int queue = 0,
			CameraType type = CameraType::Perspective,
			float aspectRatio = 1.0f,
			bool updateAspect = true,
			float fieldOfView = Converter::toRadians(60.0f),
			const Vector4& frustum = Vector4(-1.0f, 1.0f, -1.0f, 1.0f),
			const Vector2& clipPlane = Vector2(0.01f, 1000.0f),
			const Matrix4& matrix = Matrix4::identity,
			bool render = true,
			const std::set<std::shared_ptr<Entity>>& renders = {});
		virtual ~CameraComponent();
	};
}
