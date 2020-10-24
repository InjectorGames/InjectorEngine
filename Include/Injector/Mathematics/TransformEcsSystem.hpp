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

		void update() override;

		size_t getTransformCount() const noexcept;
		size_t getTranslateCount() const noexcept;
		size_t getRotateCount() const noexcept;

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
