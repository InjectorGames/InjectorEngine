#pragma once
#include <injector/manager.hpp>
#include <injector/transform_component.hpp>
#include <injector/translate_component.hpp>
#include <injector/rotate_component.hpp>

namespace INJECTOR_NAMESPACE
{
	class TransformSystem final : public System
	{
	private:
		std::set<EntityHandle> transforms;
	public:
		TransformSystem();

		void update() override;

		bool addTransform(const EntityHandle& entity) noexcept;
		bool removeTransform(const EntityHandle& entity) noexcept;
		void removeTransforms() noexcept;
		size_t getTransformCount() const noexcept;
	};
}
