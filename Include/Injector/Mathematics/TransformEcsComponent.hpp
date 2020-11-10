#pragma once
#include "Injector/ECS/EcsComponent.hpp"
#include "Injector/ECS/EcsEntity.hpp"
#include "Injector/Mathematics/Quaternion.hpp"
#include "Injector/Mathematics/RotationOrigin.hpp"

#include <memory>

namespace Injector
{
	struct TransformEcsComponent final : public EcsComponent
	{
		Vector3 position;
		Quaternion rotation;
		Vector3 scale;
		RotationOrigin origin;
		Matrix4 matrix;
		std::shared_ptr<EcsEntity> parent;

		explicit TransformEcsComponent(
			const Vector3& position = Vector3::zero,
			const Quaternion& rotation = Quaternion::zero,
			const Vector3& scale = Vector3::one,
			RotationOrigin origin = RotationOrigin::Spin,
			const Matrix4& matrix = Matrix4::identity,
			const std::shared_ptr<EcsEntity>& parent = nullptr) noexcept;
	};
}
