#pragma once
#include "Injector/ECS/EcsSystem.hpp"
#include "Injector/Graphics/GpuWindow.hpp"
#include "Injector/Graphics/GuiEcsComponent.hpp"
#include "Injector/Mathematics/TransformEcsSystem.hpp"

#include <set>

namespace Injector
{
	class GuiEcsSystem : public EcsSystem
	{
	 protected:
		std::shared_ptr<GpuWindow> window;
		std::shared_ptr<EcsEntity> cameraEntity;
		std::shared_ptr<EcsEntity> guiEntity;
		std::set<std::shared_ptr<EcsEntity>> guis;
	 public:
		explicit GuiEcsSystem(
			const std::shared_ptr<GpuWindow>& window);
		~GuiEcsSystem() override;

		const std::set<std::shared_ptr<EcsEntity>>&
			getGuis() const noexcept;

		void initialize(
			const std::shared_ptr<TransformEcsSystem>& transformSystem,
			const std::shared_ptr<CameraEcsSystem>& cameraSystem,
			const std::shared_ptr<RenderEcsSystem>& renderSystem);

		void onUpdate() override;

		bool removeEntity(
			const std::shared_ptr<EcsEntity>& entity) override;

		bool addGui(
			const std::shared_ptr<EcsEntity>& entity) noexcept;
		bool removeGui(
			const std::shared_ptr<EcsEntity>& entity) noexcept;

		void removeGuis() noexcept;
	};
}
