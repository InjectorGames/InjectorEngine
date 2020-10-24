#pragma once
#include "Injector/ECS/EcsSystem.hpp"
#include "Injector/ECS/EcsEntity.hpp"
#include "Injector/Graphics/CameraEcsComponent.hpp"
#include "Injector/Graphics/GUI/GuiEcsComponent.hpp"
#include "Injector/Mathematics/TransformEcsComponent.hpp"

#include <set>
#include <memory>

namespace Injector
{
	class GuiSystem : public EcsSystem
	{
	 protected:
		std::set<std::shared_ptr<EcsEntity>> guis;
	 public:
		std::shared_ptr<EcsEntity> camera;

		explicit GuiSystem() noexcept;

		size_t getGuiCount() const noexcept;

		void update() override;

		bool addGui(
			const std::shared_ptr<EcsEntity>& entity) noexcept;
		bool removeGui(
			const std::shared_ptr<EcsEntity>& entity) noexcept;
		void removeGuis() noexcept;
	};
}
