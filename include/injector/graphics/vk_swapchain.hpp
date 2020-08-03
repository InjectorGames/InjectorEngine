#pragma once
#include <injector/defines.hpp>
#include <injector/mathematics/int_vector2.hpp>

#include <vulkan/vulkan.hpp>
#include <SDL_vulkan.h>

namespace INJECTOR_NAMESPACE
{
	class VkSwapchain
	{
	protected:
		vk::Device device;
		vk::SurfaceFormatKHR surfaceFormat;
		vk::PresentModeKHR presentMode;
		vk::Extent2D extent;
		vk::SwapchainKHR swapchain;
		std::vector<vk::Image> images;
		std::vector<vk::ImageView> imageViews;
	public:
		VkSwapchain(
			const vk::PhysicalDevice& physicalDevice,
			const vk::SurfaceKHR& surface,
			const vk::Device& device,
			uint32_t graphicsQueueFamilyIndex,
			uint32_t presentQueueFamilyIndex,
			const IntVector2& size);
		virtual ~VkSwapchain();
	};
}
