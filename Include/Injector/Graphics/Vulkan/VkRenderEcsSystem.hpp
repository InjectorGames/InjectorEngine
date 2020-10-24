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

		void update() override;
	};
}
