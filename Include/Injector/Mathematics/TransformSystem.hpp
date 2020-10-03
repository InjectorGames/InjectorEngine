#pragma once
#include "Injector/System.hpp"
#include "Injector/Mathematics/RotateComponent.hpp"
#include "Injector/Mathematics/TransformComponent.hpp"
#include "Injector/Mathematics/TranslateComponent.hpp"

#include <set>

namespace Injector
{
	class TransformSystem : public System
	{
	 protected:
		std::set<std::shared_ptr<Entity>> transforms;
		std::set<std::shared_ptr<Entity>> translates;
		std::set<std::shared_ptr<Entity>> rotates;
	 public:
		TransformSystem() noexcept;

		void update() override;

		size_t getTransformCount() const noexcept;
		size_t getTranslateCount() const noexcept;
		size_t getRotateCount() const noexcept;

		bool addTransform(
			const std::shared_ptr<Entity>& entity) noexcept;
		bool addTranslate(
			const std::shared_ptr<Entity>& entity) noexcept;
		bool addRotate(
			const std::shared_ptr<Entity>& entity) noexcept;

		bool removeTransform(
			const std::shared_ptr<Entity>& entity) noexcept;
		bool removeTranslate(
			const std::shared_ptr<Entity>& entity) noexcept;
		bool removeRotate(
			const std::shared_ptr<Entity>& entity) noexcept;

		void removeTransforms() noexcept;
		void removeTranslates() noexcept;
		void removeRotates() noexcept;
	};
}
