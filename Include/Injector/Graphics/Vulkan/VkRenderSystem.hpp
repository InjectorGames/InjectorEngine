#pragma once
#include "Injector/Graphics/RenderSystem.hpp"
#include "Injector/Graphics/Vulkan/VkWindow.hpp"

namespace Injector
{
	class VkRenderSystem : public RenderSystem
	{
	 protected:
		std::shared_ptr<VkWindow> window;
	 public:
		explicit VkRenderSystem(
			const std::shared_ptr<VkWindow>& window);

		void update() override;
	};
}
