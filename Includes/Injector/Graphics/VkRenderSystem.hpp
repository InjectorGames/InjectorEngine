#pragma once
#include "Injector/Graphics/RenderSystem.hpp"
#include "Injector/Graphics/VkWindow.hpp"

namespace Injector
{
	class VkRenderSystem : public RenderSystem
	{
	protected:
		VkWindow& window;
	public:
		VkRenderSystem(VkWindow& window);
		virtual ~VkRenderSystem();

		void update() override;
	};
}
