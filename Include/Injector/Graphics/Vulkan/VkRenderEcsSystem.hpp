#pragma once
#include "Injector/Graphics/RenderEcsSystem.hpp"
#include "Injector/Graphics/Vulkan/VkGpuWindow.hpp"

namespace Injector
{
	class VkRenderEcsSystem : public RenderEcsSystem
	{
	 protected:
		std::shared_ptr<VkGpuWindow> window;
	 public:
		explicit VkRenderEcsSystem(
			const std::shared_ptr<VkGpuWindow>& window);

		const std::shared_ptr<VkGpuWindow>&
			getWindow() const noexcept;

		void onUpdate() override;
		void onRender() override;
	};
}
