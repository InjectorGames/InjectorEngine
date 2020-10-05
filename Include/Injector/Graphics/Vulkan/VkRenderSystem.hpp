#pragma once
#include "Injector/Graphics/RenderSystem.hpp"
#include "VkWindow.hpp"

namespace Injector
{
	class VkRenderSystem : public RenderSystem
	{
	 protected:
		VkWindow& window;
	 public:
		explicit VkRenderSystem(
			VkWindow& window);

		void update() override;
	};
}
