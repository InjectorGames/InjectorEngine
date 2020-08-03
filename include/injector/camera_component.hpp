#pragma once
#include <injector/component.hpp>
#include <injector/mathematics/matrix4.hpp>
#include <injector/engine.hpp>

namespace INJECTOR_NAMESPACE
{
	struct CameraComponent final : public Component
	{
		enum class Type
		{
			Perspective,
			Orthographic,
		};

		int queue;
		Type type;
		float aspectRatio;
		float fieldOfView;
		Vector4 frustum;
		Vector2 clipPlane;
		bool changed;
		Matrix4 matrix;

		CameraComponent(
			int queue = 0,
			Type type = Type::Perspective,
			float aspectRatio = 1.0f,
			float fieldOfView = Engine::toRadians(60.0f),
			const Vector4& frustum = Vector4(-1.0f, 1.0f, -1.0f, 1.0f),
			const Vector2& clipPlane = Vector2(0.01f, 1000.0f),
			const Matrix4& matrix = Matrix4::identity,
			bool changed = true);
	};
}
