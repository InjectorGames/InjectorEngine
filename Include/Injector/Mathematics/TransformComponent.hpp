#pragma once
#include "Injector/Component.hpp"
#include "Injector/Mathematics/Quaternion.hpp"
#include "Injector/Mathematics/RotationOrigin.hpp"

namespace Injector::Mathematics
{
	struct TransformComponent : public Component
	{
		Vector3 position;
		Quaternion rotation;
		Vector3 scale;
		RotationOrigin origin;
		Matrix4 matrix;
		bool changed;

		TransformComponent(
			const Vector3& position = Vector3::zero,
			const Quaternion& rotation = Quaternion::zero,
			const Vector3& scale = Vector3::one,
			RotationOrigin origin = RotationOrigin::Spin,
			const Matrix4& matrix = Matrix4::identity,
			const bool changed = true);
		virtual ~TransformComponent();
	};
}
