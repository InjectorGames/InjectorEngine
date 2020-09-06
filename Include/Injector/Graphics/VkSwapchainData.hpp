#pragma once
#include "Injector/Graphics/VmaDefines.hpp"
#include "vulkan/vulkan.hpp"

namespace Injector::Graphics
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
			vk::RenderPass renderPass,
			vk::CommandPool graphicsCommandPool,
			vk::CommandPool presentCommandPool,
			vk::Format surfaceFormat,
			vk::Extent2D surfaceExtent);
		virtual ~VkSwapchainData();
	};
}
