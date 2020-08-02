#pragma once
#include <injector/graphics/window.hpp>

#include <vulkan/vulkan.hpp>
#include <SDL_vulkan.h>

namespace INJECTOR_NAMESPACE
{
	class VkWindow : public Window
	{
		vk::Instance instance;
		vk::DebugReportCallbackEXT debugReport;
		vk::SurfaceKHR surface;
		vk::PhysicalDevice physicalDevice;
		vk::Device logicalDevice;
		uint32_t graphicsQueueFamilyIndex;
		uint32_t presentQueueFamilyIndex;
		vk::SurfaceFormatKHR surfaceFormat;
		vk::PresentModeKHR presentMode;
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
