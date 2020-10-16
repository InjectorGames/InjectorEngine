#include "Injector/Graphics/Vulkan/VkSwapchainData.hpp"
#include "Injector/Exception/NullException.hpp"

namespace Injector
{
	VkSwapchainData::VkSwapchainData(
		vk::Device _device,
		vk::Image _image,
		vk::RenderPass renderPass,
		vk::CommandPool _graphicsCommandPool,
		vk::CommandPool _presentCommandPool,
		vk::Format surfaceFormat,
		const vk::Extent2D& surfaceExtent) :
		device(_device),
		image(_image),
		graphicsCommandPool(_graphicsCommandPool),
		presentCommandPool(_presentCommandPool)
	{
		if(!_device)
		{
			throw NullException(
				"VkSwapchainData",
				"VkSwapchainData",
				"device");
		}
		if(!_image)
		{
			throw NullException(
				"VkSwapchainData",
				"VkSwapchainData",
				"image");
		}
		if(!renderPass)
		{
			throw NullException(
				"VkSwapchainData",
				"VkSwapchainData",
				"renderPass");
		}
		if(!_graphicsCommandPool)
		{
			throw NullException(
				"VkSwapchainData",
				"VkSwapchainData",
				"graphicsCommandPool");
		}
		if(!_presentCommandPool)
		{
			throw NullException(
				"VkSwapchainData",
				"VkSwapchainData",
				"presentCommandPool");
		}

		auto imageViewCreateInfo = vk::ImageViewCreateInfo({},
			_image,
			vk::ImageViewType::e2D,
			surfaceFormat,
			vk::ComponentMapping(
				vk::ComponentSwizzle::eIdentity,
				vk::ComponentSwizzle::eIdentity,
				vk::ComponentSwizzle::eIdentity,
				vk::ComponentSwizzle::eIdentity),
			vk::ImageSubresourceRange(
				vk::ImageAspectFlagBits::eColor,
				0,
				1,
				0,
				1));

		auto result = _device.createImageView(
			&imageViewCreateInfo,
			nullptr,
			&imageView);

		if (result != vk::Result::eSuccess)
		{
			throw Exception(
				"VkSwapchainData",
				"VkSwapchainData",
				"Failed to create image view");
		}

		auto framebufferCreateInfo = vk::FramebufferCreateInfo({},
			renderPass,
			1,
			&imageView,
			surfaceExtent.width,
			surfaceExtent.height,
			1);
		result = _device.createFramebuffer(
			&framebufferCreateInfo,
			nullptr,
			&framebuffer);

		if (result != vk::Result::eSuccess)
		{
			throw Exception(
				"VkSwapchainData",
				"VkSwapchainData",
				"Failed to create framebuffer");
		}

		auto commandBufferAllocateInfo = vk::CommandBufferAllocateInfo(
			_graphicsCommandPool,
			vk::CommandBufferLevel::ePrimary,
			1);
		result = _device.allocateCommandBuffers(
			&commandBufferAllocateInfo,
			&graphicsCommandBuffer);

		if (result != vk::Result::eSuccess)
		{
			throw Exception(
				"VkSwapchainData",
				"VkSwapchainData",
				"Failed to allocate command buffers");
		}

		if (_graphicsCommandPool != _presentCommandPool)
		{
			commandBufferAllocateInfo.commandPool = _presentCommandPool;

			result = _device.allocateCommandBuffers(
				&commandBufferAllocateInfo,
				&presentCommandBuffer);

			if (result != vk::Result::eSuccess)
			{
				throw Exception(
					"VkSwapchainData",
					"VkSwapchainData",
					"Failed to allocate command buffers");
			}
		}
		else
		{
			presentCommandBuffer = graphicsCommandBuffer;
		}
	}
	VkSwapchainData::~VkSwapchainData()
	{
		if (graphicsCommandPool != presentCommandPool)
		{
			device.freeCommandBuffers(
				graphicsCommandPool,
				graphicsCommandBuffer);
			device.freeCommandBuffers(
				presentCommandPool,
				presentCommandBuffer);
		}
		else
		{
			device.freeCommandBuffers(
				graphicsCommandPool,
				graphicsCommandBuffer);
		}

		device.destroyFramebuffer(framebuffer);
		device.destroyImageView(imageView);
	}
}
