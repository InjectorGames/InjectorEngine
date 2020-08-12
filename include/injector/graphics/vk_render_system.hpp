#pragma once
#include <injector/graphics/render_system.hpp>
#include <injector/graphics/vk_window.hpp>

namespace INJECTOR_NAMESPACE
{
	class VkRenderSystem : public RenderSystem
	{
	protected:
		VkWindowHandle window;
	public:
		VkRenderSystem(const VkWindowHandle& window);
		virtual ~VkRenderSystem();

		WindowHandle getWindow() const override;
		void update() override;
	};
}
