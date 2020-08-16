#pragma once
#include <injector/system.hpp>
#include <injector/mathematics/rotate_component.hpp>
#include <injector/mathematics/attach_component.hpp>
#include <injector/mathematics/transform_component.hpp>
#include <injector/mathematics/translate_component.hpp>

#include <set>

namespace INJECTOR_NAMESPACE
{
	class TransformSystem : public System
	{
	protected:
		std::set<EntityHandle> transforms;
		std::set<EntityHandle> translates;
		std::set<EntityHandle> rotates;
		std::set<EntityHandle> attaches;
	public:
		virtual ~TransformSystem();

		void update() override;

		size_t getTransformCount() const noexcept;

		bool addTransform(const EntityHandle& entity) noexcept;
		bool removeTransform(const EntityHandle& entity) noexcept;
		void removeTransforms() noexcept;

		bool addTranslate(const EntityHandle& entity) noexcept;
		bool removeTranslate(const EntityHandle& entity) noexcept;
		void removeTranslates() noexcept;

		bool addRotate(const EntityHandle& entity) noexcept;
		bool removeRotate(const EntityHandle& entity) noexcept;
		void removeRotates() noexcept;

		bool addAttach(const EntityHandle& entity) noexcept;
		bool removeAttach(const EntityHandle& entity) noexcept;
		void removeAttaches() noexcept;
	};

	using TransformSystemHandle = std::shared_ptr<TransformSystem>;
}
