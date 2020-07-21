#pragma once
#include <injector/manager.hpp>
#include <injector/transform_component.hpp>

namespace INJECTOR_NAMESPACE
{
	class TransformSystem : public System
	{
	protected:
		std::set<EntityHandle> transforms;
		std::set<EntityHandle> translates;
		std::set<EntityHandle> rotates;
	public:
		TransformSystem();
		virtual ~TransformSystem();

		void update() override;

		bool createTransformComponent(
			const EntityHandle& entity,
			TransformComponent::Type type = TransformComponent::Type::Spin,
			const EntityHandle& parent = nullptr,
			const Vector3& scale = Vector3::one,
			const Vector3& position = Vector3::zero,
			const Quaternion& rotation = Quaternion(Vector3::zero),
			const Matrix4& matrix = Matrix4::identity,
			const bool changed = true) noexcept;
		bool destroyTransformComponent(
			const EntityHandle& entity) noexcept;
		void destroyTransformComponents() noexcept;
		size_t transformComponentCount() const noexcept;
	};
}
