#pragma once
#include "Injector/Graphics/GpuWindow.hpp"
#include "Injector/Graphics/CameraEcsComponent.hpp"
#include "Injector/Graphics/GUI/GuiEcsComponent.hpp"
#include "Injector/Mathematics/TransformEcsComponent.hpp"

#include <set>
#include <memory>

namespace Injector
{
	class GuiEcsSystem : public EcsSystem
	{
	 protected:
		std::shared_ptr<GpuWindow> window;
		std::set<std::shared_ptr<EcsEntity>> guis;
	 public:
		std::shared_ptr<EcsEntity> camera;

		explicit GuiEcsSystem(
			const std::shared_ptr<GpuWindow>& window) noexcept;

		size_t getGuiCount() const noexcept;

		void update() override;

		bool addGui(
			const std::shared_ptr<EcsEntity>& entity) noexcept;
		bool removeGui(
			const std::shared_ptr<EcsEntity>& entity) noexcept;
		void removeGuis() noexcept;
	};
}
