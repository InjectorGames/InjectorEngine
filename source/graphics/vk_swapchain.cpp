#include <injector/graphics/vk_swapchain.hpp>

#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>

namespace INJECTOR_NAMESPACE
{
	VkSwapchain::VkSwapchain(
		const vk::PhysicalDevice& physicalDevice,
		const vk::SurfaceKHR& surface,
		const vk::Device& _device,
		uint32_t graphicsQueueFamilyIndex,
		uint32_t presentQueueFamilyIndex,
		const IntVector2& size) :
		device(_device)
	{
		auto surfaceFormats = physicalDevice.getSurfaceFormatsKHR(surface);

		if (surfaceFormats.size() == 0)
			throw std::runtime_error("Failed to get Vulkan surface formats");

		std::cout << "VULKAN PHYSICAL DEVICE SURFACE FORMATS:\n";
		for (auto& foramt : surfaceFormats)
			std::cout << "   format: " << vk::to_string(foramt.format) <<
			", color_space: " << vk::to_string(foramt.colorSpace) << "\n";

		surfaceFormat = surfaceFormats[0];

		for (auto& format : surfaceFormats)
		{
			if (format.format == vk::Format::eB8G8R8A8Srgb &&
				format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear)
			{
				surfaceFormat = format;
				break;
			}
		}

		if (surfaceFormat == vk::Format::eUndefined)
			surfaceFormat = vk::Format::eB8G8R8A8Srgb;

		auto surfacePresentModes = physicalDevice.getSurfacePresentModesKHR(surface);

		if (surfaceFormats.size() == 0)
			throw std::runtime_error("Failed to get Vulkan surface present modes");

		std::cout << "VULKAN PHYSICAL DEVICE SURFACE PRESENT MODES:\n";
		for (auto mode : surfacePresentModes)
			std::cout << "   mode: " << vk::to_string(mode) << "\n";

		presentMode = vk::PresentModeKHR::eFifo;

		// TODO: Test all modes to pick best
		for (auto mode : surfacePresentModes)
		{
			if (mode == vk::PresentModeKHR::eMailbox)
			{
				presentMode = mode;
				break;
			}
		}
		for (auto mode : surfacePresentModes)
		{
			if (mode == vk::PresentModeKHR::eFifoRelaxed)
			{
				presentMode = mode;
				break;
			}
		}
		for (auto mode : surfacePresentModes)
		{
			if (mode == vk::PresentModeKHR::eImmediate)
			{
				presentMode = mode;
				break;
			}
		}

		auto surfaceCapabilities = physicalDevice.getSurfaceCapabilitiesKHR(surface);

		if (surfaceCapabilities.currentExtent.width == UINT32_MAX)
		{
			extent.width = std::max(surfaceCapabilities.minImageExtent.width, std::min(
				surfaceCapabilities.maxImageExtent.width, static_cast<uint32_t>(size.x)));
			extent.height = std::max(surfaceCapabilities.minImageExtent.height, std::min(
				surfaceCapabilities.maxImageExtent.height, static_cast<uint32_t>(size.y)));
		}
		else
		{
			extent = surfaceCapabilities.currentExtent;
		}

		auto imageCount = surfaceCapabilities.minImageCount + 1;

		if (surfaceCapabilities.maxImageCount > 0 &&
			imageCount > surfaceCapabilities.maxImageCount)
			imageCount = surfaceCapabilities.maxImageCount;

		auto swapchainCreateInfo = vk::SwapchainCreateInfoKHR();
		swapchainCreateInfo.surface = surface;
		swapchainCreateInfo.minImageCount = imageCount;
		swapchainCreateInfo.imageFormat = surfaceFormat.format;
		swapchainCreateInfo.imageColorSpace = surfaceFormat.colorSpace;
		swapchainCreateInfo.imageExtent = extent;
		swapchainCreateInfo.imageArrayLayers = 1;
		swapchainCreateInfo.imageUsage = vk::ImageUsageFlagBits::eColorAttachment;

		if (graphicsQueueFamilyIndex == presentQueueFamilyIndex)
		{
			swapchainCreateInfo.imageSharingMode = vk::SharingMode::eExclusive;
			swapchainCreateInfo.queueFamilyIndexCount = 0;
			swapchainCreateInfo.pQueueFamilyIndices = nullptr;
		}
		else
		{
			auto queueFamilyIndices = std::vector<uint32_t>
			{
				graphicsQueueFamilyIndex, presentQueueFamilyIndex,
			};

			swapchainCreateInfo.imageSharingMode = vk::SharingMode::eConcurrent;
			swapchainCreateInfo.queueFamilyIndexCount = queueFamilyIndices.size();
			swapchainCreateInfo.pQueueFamilyIndices = queueFamilyIndices.data();
		}

		swapchainCreateInfo.preTransform = surfaceCapabilities.currentTransform;
		// TODO: find supported composite alpha
		swapchainCreateInfo.compositeAlpha = vk::CompositeAlphaFlagBitsKHR::eOpaque;
		swapchainCreateInfo.presentMode = presentMode;
		swapchainCreateInfo.clipped = true;
		swapchainCreateInfo.oldSwapchain = nullptr;

		swapchain = _device.createSwapchainKHR(swapchainCreateInfo);

		if (!swapchain)
			throw std::runtime_error("Failed to create Vulkan swapchain");

		images = _device.getSwapchainImagesKHR(swapchain);

		if (images.size() == 0)
			throw std::runtime_error("Failed to get Vulkan swapchain images");

		auto imageViewCreateInfo = vk::ImageViewCreateInfo();
		imageViewCreateInfo.viewType = vk::ImageViewType::e2D;
		imageViewCreateInfo.format = surfaceFormat.format;
		imageViewCreateInfo.components.r = vk::ComponentSwizzle::eIdentity;
		imageViewCreateInfo.components.g = vk::ComponentSwizzle::eIdentity;
		imageViewCreateInfo.components.b = vk::ComponentSwizzle::eIdentity;
		imageViewCreateInfo.components.a = vk::ComponentSwizzle::eIdentity;
		imageViewCreateInfo.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
		imageViewCreateInfo.subresourceRange.baseMipLevel = 0;
		imageViewCreateInfo.subresourceRange.levelCount = 1;
		imageViewCreateInfo.subresourceRange.baseArrayLayer = 0;
		imageViewCreateInfo.subresourceRange.layerCount = 1;

		imageViews = std::vector<vk::ImageView>(images.size());

		for (size_t i = 0; i < images.size(); i++)
		{
			imageViewCreateInfo.image = images[i];
			auto newImageView = _device.createImageView(imageViewCreateInfo);

			if (!newImageView)
			{
				for (auto& imageView : imageViews)
				{
					if(imageView)
						_device.destroyImageView(imageView);
				}

				_device.destroySwapchainKHR(swapchain);
				throw std::runtime_error("Failed to get Vulkan swapchain image view");
			}

			imageViews[i] = newImageView;
		}
	}
	VkSwapchain::~VkSwapchain()
	{
		for (auto& imageView : imageViews)
			device.destroyImageView(imageView);

		device.destroySwapchainKHR(swapchain);
	}
}
