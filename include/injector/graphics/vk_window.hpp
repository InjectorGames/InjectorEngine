#pragma once
#include <injector/graphics/window.hpp>

#include <vulkan/vulkan.hpp>
#include <SDL_vulkan.h>

namespace INJECTOR_NAMESPACE
{
	class VkWindow : public Window
	{
		vk::Instance instance;
		vk::DispatchLoaderDynamic dispatchDynamic;
		vk::DebugUtilsMessengerEXT debugMessenger;
		vk::SurfaceKHR surface;
		vk::PhysicalDevice physicalDevice;
		vk::Device logicalDevice;
		uint32_t graphicsQueueFamilyIndex;
		uint32_t presentQueueFamilyIndex;
		vk::Queue graphicsQueue;
		vk::Queue presentQueue;
		vk::SurfaceFormatKHR surfaceFormat;
		vk::PresentModeKHR presentMode;
		vk::Extent2D extent;
		vk::SwapchainKHR swapchain;
		std::vector<vk::Image> images;
		std::vector<vk::ImageView> imageViews;
		std::vector<vk::Semaphore> imageAcquiredSemaphores;
		std::vector<vk::Semaphore> drawCompleteSemaphores;
		std::vector<vk::Semaphore> imageOwnershipSemaphores;

		static VkBool32 VKAPI_CALL debugMessengerCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageTypes,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData);
	public:
		VkWindow(const std::string& title = defaultTitle,
			const IntVector2& position = defaultPosition,
			const IntVector2& size = defaultSize,
			uint32_t flags = defaultFlags);
		virtual ~VkWindow();
	};
}
