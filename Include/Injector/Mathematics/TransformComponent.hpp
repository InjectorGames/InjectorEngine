#pragma once
#include "Injector/Component.hpp"
#include "Injector/Entity.hpp"
#include "Injector/Mathematics/Quaternion.hpp"
#include "Injector/Mathematics/RotationOrigin.hpp"

#include <memory>

namespace Injector
{
	struct TransformComponent : public Component
	{
		Vector3 position;
		Quaternion rotation;
		Vector3 scale;
		RotationOrigin origin;
		Matrix4 matrix;
		std::shared_ptr<Entity> parent;

		TransformComponent(
			const Vector3& position = Vector3::zero,
			const Quaternion& rotation = Quaternion(Vector3::zero),
			const Vector3& scale = Vector3::one,
			RotationOrigin origin = RotationOrigin::Spin,
			const Matrix4& matrix = Matrix4::identity,
			const std::shared_ptr<Entity>& parent = nullptr) noexcept;
	};
}
