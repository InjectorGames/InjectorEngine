#pragma once
#include <injector/graphics/window.hpp>
#include <injector/graphics/vk_window_instance.hpp>
#include <injector/graphics/vk_surface.hpp>
#include <injector/graphics/vk_logical_device.hpp>
#include <injector/graphics/vk_swapchain.hpp>

namespace INJECTOR_NAMESPACE
{
	class VkWindow : public Window
	{
	protected:
		VkWindowInstance* windowInstance;
		VkSurface* surface;
		VkLogicalDevice* logicalDevice;
		VkSwapchain* swapchain;
		
		std::vector<vk::Semaphore> imageAcquiredSemaphores;
		std::vector<vk::Semaphore> drawCompleteSemaphores;
		std::vector<vk::Semaphore> imageOwnershipSemaphores;
	public:
		VkWindow(const std::string& title = defaultTitle,
			const IntVector2& position = defaultPosition,
			const IntVector2& size = defaultSize,
			uint32_t flags = defaultFlags);
		virtual ~VkWindow();
	};
}
