#pragma once
#include "Injector/Graphics/Vulkan/VmaDefines.hpp"
#include "vulkan/vulkan.hpp"

namespace Injector
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
			vk::Format format,
			vk::ImageView depthImageView,
			const vk::Extent2D& surfaceExtent);
		VkSwapchainData(const VkSwapchainData& data) = delete;
		VkSwapchainData(VkSwapchainData&& data) = delete;
		virtual ~VkSwapchainData();
	};
}
