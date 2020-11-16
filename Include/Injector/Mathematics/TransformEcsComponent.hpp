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
		FloatVector3 position;
		Quaternion rotation;
		FloatVector3 scale;
		RotationOrigin origin;
		FloatMatrix4 matrix;
		std::shared_ptr<EcsEntity> parent;

		explicit TransformEcsComponent(
			const FloatVector3& position = FloatVector3(),
			const Quaternion& rotation = Quaternion(),
			const FloatVector3& scale = FloatVector3(),
			RotationOrigin origin = RotationOrigin::Spin,
			const FloatMatrix4& matrix = FloatMatrix4(),
			const std::shared_ptr<EcsEntity>& parent = nullptr) noexcept;
	};
}
