#pragma once
#include <injector/defines.hpp>

#include <vulkan/vulkan.hpp>
#include <vk_mem_alloc.h>

namespace INJECTOR_NAMESPACE
{
	struct VkSwapchainData
	{
		vk::Device device;
		vk::Image image;
		vk::ImageView imageView;
		vk::Framebuffer framebuffer;
		vk::CommandPool graphicsCommandPool;
		vk::CommandPool presentCommandPool;
		vk::CommandBuffer graphicsCommandBuffer;
		vk::CommandBuffer presentCommandBuffer;
		vk::DescriptorSet descriptorSet;

		VkSwapchainData(
			vk::Device device,
			vk::Image image,
			vk::SwapchainKHR swapchain,
			vk::RenderPass renderPass,
			vk::CommandPool graphicsCommandPool,
			vk::CommandPool presentCommandPool,
			vk::Format surfaceFormat,
			vk::Extent2D surfaceExtent);
		virtual ~VkSwapchainData();
	};
}