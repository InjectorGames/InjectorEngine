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
		vk::Format format,
		vk::ImageView depthImageView,
		const vk::Extent2D& surfaceExtent) :
		device(_device),
		image(_image),
		graphicsCommandPool(_graphicsCommandPool),
		presentCommandPool(_presentCommandPool)
	{
		if(!_device)
		{
			throw NullException(
				std::string(typeid(VkSwapchainData).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"device");
		}
		if(!_image)
		{
			throw NullException(
				std::string(typeid(VkSwapchainData).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"image");
		}
		if(!renderPass)
		{
			throw NullException(
				std::string(typeid(VkSwapchainData).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"renderPass");
		}
		if(!_graphicsCommandPool)
		{
			throw NullException(
				std::string(typeid(VkSwapchainData).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"graphicsCommandPool");
		}
		if(!_presentCommandPool)
		{
			throw NullException(
				std::string(typeid(VkSwapchainData).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"presentCommandPool");
		}
		if(!depthImageView)
		{
			throw NullException(
				std::string(typeid(VkSwapchainData).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"depthImageView");
		}

		auto imageViewCreateInfo = vk::ImageViewCreateInfo(
			vk::ImageViewCreateFlags(),
			_image,
			vk::ImageViewType::e2D,
			format,
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
				std::string(typeid(VkSwapchainData).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"Failed to create image view");
		}

		vk::ImageView imageViews[2] =
		{
			imageView,
			depthImageView
		};

		auto framebufferCreateInfo = vk::FramebufferCreateInfo(
			vk::FramebufferCreateFlags(),
			renderPass,
			2,
			imageViews,
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
				std::string(typeid(VkSwapchainData).name()),
				std::string(__func__),
				std::to_string(__LINE__),
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
				std::string(typeid(VkSwapchainData).name()),
				std::string(__func__),
				std::to_string(__LINE__),
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
					std::string(typeid(VkSwapchainData).name()),
					std::string(__func__),
					std::to_string(__LINE__),
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
