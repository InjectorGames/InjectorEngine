#pragma once
#include <injector/system.hpp>
#include <injector/mathematics/transform_component.hpp>
#include <injector/mathematics/translate_component.hpp>
#include <injector/mathematics/rotate_component.hpp>

#include <set>

namespace INJECTOR_NAMESPACE
{
	class TransformSystem : public System
	{
	protected:
		std::set<EntityHandle> transforms;
	public:
		TransformSystem();
		virtual ~TransformSystem();

		void update() override;

		size_t getTransformCount() const noexcept;

		bool addTransform(const EntityHandle& entity) noexcept;
		bool removeTransform(const EntityHandle& entity) noexcept;
		void removeTransforms() noexcept;
	};

	using TransformSystemHandle = std::shared_ptr<TransformSystem>;
}
