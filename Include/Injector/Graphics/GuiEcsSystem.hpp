#pragma once
#include "Injector/ECS/EcsSystem.hpp"
#include "Injector/Graphics/GpuWindow.hpp"
#include "Injector/Graphics/GuiEcsComponent.hpp"

#include <set>

namespace Injector
{
	class GuiEcsSystem : public EcsSystem
	{
	 protected:
		std::shared_ptr<RenderEcsSystem> renderSystem;
		std::shared_ptr<RenderEcsComponent> renderComponent;
		std::set<std::shared_ptr<EcsEntity>> guis;
	 public:
		GuiEcsSystem() noexcept;

		const std::set<std::shared_ptr<EcsEntity>>&
			getGuis() const noexcept;

		void initialize(
			const std::shared_ptr<GpuWindow>& window,
			const std::shared_ptr<RenderEcsSystem>& renderSystem);

		void onUpdate() override;

		bool addGui(
			const std::shared_ptr<EcsEntity>& entity) noexcept;
		bool removeGui(
			const std::shared_ptr<EcsEntity>& entity) noexcept;

		void removeGuis() noexcept;
	};
}
