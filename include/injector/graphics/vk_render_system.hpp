#pragma once
#include <injector/graphics/render_system.hpp>
#include <injector/graphics/vk_window.hpp>

namespace INJECTOR_NAMESPACE
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
