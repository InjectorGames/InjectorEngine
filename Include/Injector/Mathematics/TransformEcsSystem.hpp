#pragma once
#include "Injector/ECS/EcsSystem.hpp"
#include "Injector/Mathematics/RotateEcsComponent.hpp"
#include "Injector/Mathematics/TransformEcsComponent.hpp"
#include "Injector/Mathematics/TranslateEcsComponent.hpp"

#include <set>

namespace Injector
{
	class TransformEcsSystem : public EcsSystem
	{
	 protected:
		std::set<std::shared_ptr<EcsEntity>> transforms;
		std::set<std::shared_ptr<EcsEntity>> translates;
		std::set<std::shared_ptr<EcsEntity>> rotates;
	 public:
		TransformEcsSystem() noexcept;

		const std::set<std::shared_ptr<EcsEntity>>&
			getTransforms() const noexcept;
		const std::set<std::shared_ptr<EcsEntity>>&
			getTranslates() const noexcept;
		const std::set<std::shared_ptr<EcsEntity>>&
			getRotates() const noexcept;

		void onUpdate() override;

		bool removeEntity(
			const std::shared_ptr<EcsEntity>& entity) override;

		bool addTransform(
			const std::shared_ptr<EcsEntity>& entity) noexcept;
		bool addTranslate(
			const std::shared_ptr<EcsEntity>& entity) noexcept;
		bool addRotate(
			const std::shared_ptr<EcsEntity>& entity) noexcept;

		bool removeTransform(
			const std::shared_ptr<EcsEntity>& entity) noexcept;
		bool removeTranslate(
			const std::shared_ptr<EcsEntity>& entity) noexcept;
		bool removeRotate(
			const std::shared_ptr<EcsEntity>& entity) noexcept;

		void removeTransforms() noexcept;
		void removeTranslates() noexcept;
		void removeRotates() noexcept;
	};
}
