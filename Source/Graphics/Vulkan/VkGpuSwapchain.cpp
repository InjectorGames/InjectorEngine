#include "Injector/Graphics/Vulkan/VkGpuSwapchain.hpp"
#include "Injector/Exception/NullException.hpp"

namespace Injector
{
	vk::SurfaceFormatKHR VkGpuSwapchain::getBestSurfaceFormat(
		vk::PhysicalDevice physicalDevice,
		vk::SurfaceKHR surface)
	{
		auto surfaceFormats =
			physicalDevice.getSurfaceFormatsKHR(surface);

		auto surfaceFormat = surfaceFormats.at(0);

		for (auto& format : surfaceFormats)
		{
			if (format.format == vk::Format::eB8G8R8A8Srgb &&
				format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear)
			{
				surfaceFormat = format;
				break;
			}
		}

		return surfaceFormat;
	}
	vk::PresentModeKHR VkGpuSwapchain::getBestPresentMode(
		vk::PhysicalDevice physicalDevice,
		vk::SurfaceKHR surface)
	{
		auto presentModes =
			physicalDevice.getSurfacePresentModesKHR(surface);

		auto presentMode = vk::PresentModeKHR::eFifo;

		for (auto mode : presentModes)
		{
			if (mode == vk::PresentModeKHR::eMailbox)
			{
				presentMode = mode;
				break;
			}
		}
		for (auto mode : presentModes)
		{
			if (mode == vk::PresentModeKHR::eFifoRelaxed)
			{
				presentMode = mode;
				break;
			}
		}

		return presentMode;
	}
	vk::Extent2D VkGpuSwapchain::getBestExtent(
		const vk::SurfaceCapabilitiesKHR& surfaceCapabilities,
		const IntVector2& size)
	{
		if (surfaceCapabilities.currentExtent.width == UINT32_MAX)
		{
			return vk::Extent2D(
				std::clamp(static_cast<uint32_t>(size.x),
					surfaceCapabilities.minImageExtent.width,
					surfaceCapabilities.maxImageExtent.width),
				std::clamp(static_cast<uint32_t>(size.y),
					surfaceCapabilities.minImageExtent.height,
					surfaceCapabilities.maxImageExtent.height));
		}
		else
		{
			return surfaceCapabilities.currentExtent;
		}
	}
	uint32_t VkGpuSwapchain::getBestImageCount(
		const vk::SurfaceCapabilitiesKHR& capabilities)
	{
		auto imageCount =
			capabilities.minImageCount + 1;

		if (capabilities.maxImageCount > 0 &&
			imageCount > capabilities.maxImageCount)
			imageCount = capabilities.maxImageCount;

		return imageCount;
	}
	vk::SurfaceTransformFlagBitsKHR VkGpuSwapchain::getBestTransform(
		const vk::SurfaceCapabilitiesKHR& capabilities)
	{
		if(capabilities.supportedTransforms &
		   vk::SurfaceTransformFlagBitsKHR::eIdentity)
		{
			return vk::SurfaceTransformFlagBitsKHR::eIdentity;
		}
		else
		{
			return capabilities.currentTransform;
		}
	}
	vk::CompositeAlphaFlagBitsKHR VkGpuSwapchain::getBestCompositeAlpha(
		const vk::SurfaceCapabilitiesKHR& capabilities)
	{
		if (capabilities.supportedCompositeAlpha &
			vk::CompositeAlphaFlagBitsKHR::eOpaque)
		{
			return vk::CompositeAlphaFlagBitsKHR::eOpaque;
		}
		else if (capabilities.supportedCompositeAlpha &
				 vk::CompositeAlphaFlagBitsKHR::ePreMultiplied)
		{
			return vk::CompositeAlphaFlagBitsKHR::ePreMultiplied;
		}
		else if (capabilities.supportedCompositeAlpha &
				 vk::CompositeAlphaFlagBitsKHR::ePostMultiplied)
		{
			return vk::CompositeAlphaFlagBitsKHR::ePostMultiplied;
		}
		else if (capabilities.supportedCompositeAlpha &
				 vk::CompositeAlphaFlagBitsKHR::eInherit)
		{
			return vk::CompositeAlphaFlagBitsKHR::eInherit;
		}
		else
		{
			throw Exception(
				"VkGpuSwapchain",
				"createSwapchain",
				"No supported composite alpha");
		}
	}
	vk::SwapchainKHR VkGpuSwapchain::createSwapchain(
		vk::Device device,
		vk::SurfaceKHR surface,
		uint32_t imageCount,
		vk::SurfaceFormatKHR surfaceFormat,
		vk::Extent2D extent,
		vk::SurfaceTransformFlagBitsKHR transform,
		vk::CompositeAlphaFlagBitsKHR compositeAlpha,
		vk::PresentModeKHR presentMode,
		vk::SwapchainKHR oldSwapchain)
	{
		vk::SwapchainKHR swapchain;

		auto swapchainCreateInfo = vk::SwapchainCreateInfoKHR({},
			surface,
			imageCount,
			surfaceFormat.format,
			surfaceFormat.colorSpace,
			extent,
			1,
			vk::ImageUsageFlagBits::eColorAttachment,
			vk::SharingMode::eExclusive,
			0,
			nullptr,
			transform,
			compositeAlpha,
			presentMode,
			true,
			oldSwapchain);

		auto result = device.createSwapchainKHR(
			&swapchainCreateInfo,
			nullptr,
			&swapchain);

		if (result != vk::Result::eSuccess)
		{
			throw Exception(
				"VkGpuSwapchain",
				"VkGpuSwapchain",
				"Failed to create swapchain");
		}

		return swapchain;
	}
	vk::RenderPass VkGpuSwapchain::createRenderPass(
		vk::Device device,
		vk::Format format)
	{
		vk::RenderPass renderPass;

		auto colorAttachmentDescription = vk::AttachmentDescription({},
			format,
			vk::SampleCountFlagBits::e1,
			vk::AttachmentLoadOp::eClear,
			vk::AttachmentStoreOp::eStore,
			vk::AttachmentLoadOp::eDontCare,
			vk::AttachmentStoreOp::eDontCare,
			vk::ImageLayout::eUndefined,
			vk::ImageLayout::ePresentSrcKHR);

		auto colorAttachmentReference = vk::AttachmentReference(
			0,
			vk::ImageLayout::eColorAttachmentOptimal);

		auto subpassDescription = vk::SubpassDescription({},
			vk::PipelineBindPoint::eGraphics,
			0,
			nullptr,
			1,
			&colorAttachmentReference);

		auto subpassDependency = vk::SubpassDependency(
			VK_SUBPASS_EXTERNAL,
			0,
			vk::PipelineStageFlagBits::eColorAttachmentOutput,
			vk::PipelineStageFlagBits::eColorAttachmentOutput,
			{},
			vk::AccessFlagBits::eColorAttachmentWrite,
			{});

		auto renderPassCreateInfo = vk::RenderPassCreateInfo({},
			1,
			&colorAttachmentDescription,
			1,
			&subpassDescription,
			1,
			&subpassDependency);

		auto result = device.createRenderPass(
			&renderPassCreateInfo,
			nullptr,
			&renderPass);

		if (result != vk::Result::eSuccess)
		{
			throw Exception(
				"VkGpuSwapchain",
				"createRenderPass",
				"Failed to create render pass");
		}

		return renderPass;
	}
	std::vector<std::shared_ptr<VkSwapchainData>> VkGpuSwapchain::createDatas(
		vk::Device device,
		vk::SwapchainKHR swapchain,
		vk::RenderPass renderPass,
		vk::CommandPool graphicsCommandPool,
		vk::CommandPool presentCommandPool,
		vk::Format format,
		const vk::Extent2D& extent)
	{
		auto images = device.getSwapchainImagesKHR(swapchain);
		auto datas = std::vector<std::shared_ptr<VkSwapchainData>>(images.size());

		for (size_t i = 0; i < images.size(); i++)
		{
			datas[i] = std::make_shared<VkSwapchainData>(
				device,
				images[i],
				renderPass,
				graphicsCommandPool,
				presentCommandPool,
				format,
				extent);
		}

		return std::move(datas);
	}

	VkGpuSwapchain::VkGpuSwapchain() noexcept :
		device(),
		physicalDevice(),
		extent(),
		swapchain(),
		renderPass(),
		datas()
	{
	}
	VkGpuSwapchain::VkGpuSwapchain(
		vk::Device _device,
		vk::PhysicalDevice _physicalDevice,
		vk::SurfaceKHR surface,
		vk::CommandPool graphicsCommandPool,
		vk::CommandPool presentCommandPool,
		const IntVector2& size) :
		device(_device),
		physicalDevice(_physicalDevice)
	{
		if(!_device)
		{
			throw NullException(
				"VkGpuSwapchain",
				"VkGpuSwapchain",
				"device");
		}
		if(!_physicalDevice)
		{
			throw NullException(
				"VkGpuSwapchain",
				"VkGpuSwapchain",
				"physicalDevice");
		}
		if(!surface)
		{
			throw NullException(
				"VkGpuSwapchain",
				"VkGpuSwapchain",
				"surface");
		}
		if(!graphicsCommandPool)
		{
			throw NullException(
				"VkGpuSwapchain",
				"VkGpuSwapchain",
				"graphicsCommandPool");
		}
		if(!presentCommandPool)
		{
			throw NullException(
				"VkGpuSwapchain",
				"VkGpuSwapchain",
				"presentCommandPool");
		}

		auto surfaceFormat = getBestSurfaceFormat(
			_physicalDevice,
			surface);
		auto presentMode = getBestPresentMode(
			_physicalDevice,
			surface);

		auto capabilities =
			_physicalDevice.getSurfaceCapabilitiesKHR(surface);

		extent = getBestExtent(
			capabilities,
			size);

		auto imageCount = getBestImageCount(
			capabilities);
		auto transform = getBestTransform(
			capabilities);
		auto compositeAlpha = getBestCompositeAlpha(
			capabilities);

		swapchain = createSwapchain(
			_device,
			surface,
			imageCount,
			surfaceFormat,
			extent,
			transform,
			compositeAlpha,
			presentMode);

		renderPass = createRenderPass(
			_device,
			surfaceFormat.format);

		datas = createDatas(
			_device,
			swapchain,
			renderPass,
			graphicsCommandPool,
			presentCommandPool,
			surfaceFormat.format,
			extent);
	}
	VkGpuSwapchain::VkGpuSwapchain(
		VkGpuSwapchain&& _swapchain) noexcept
	{
		device = _swapchain.device;
		physicalDevice = _swapchain.physicalDevice;
		extent = _swapchain.extent;
		swapchain = _swapchain.swapchain;
		renderPass = _swapchain.renderPass;
		datas = std::move(_swapchain.datas);
		_swapchain.device = nullptr;
	}
	VkGpuSwapchain::~VkGpuSwapchain()
	{
		datas.clear();

		if(device)
		{
			device.destroyRenderPass(renderPass);
			device.destroySwapchainKHR(swapchain);
		}
	}

	vk::Device VkGpuSwapchain::getDevice() const noexcept
	{
		return device;
	}
	vk::PhysicalDevice VkGpuSwapchain::getPhysicalDevice() const noexcept
	{
		return physicalDevice;
	}
	const vk::Extent2D& VkGpuSwapchain::getExtent() const noexcept
	{
		return extent;
	}
	vk::SwapchainKHR VkGpuSwapchain::getSwapchain() const noexcept
	{
		return swapchain;
	}
	vk::RenderPass VkGpuSwapchain::getRenderPass() const noexcept
	{
		return renderPass;
	}
	const std::vector<std::shared_ptr<VkSwapchainData>>&
		VkGpuSwapchain::getDatas() const noexcept
	{
		return datas;
	}

	void VkGpuSwapchain::resize(
		vk::SurfaceKHR surface,
		vk::CommandPool graphicsCommandPool,
		vk::CommandPool presentCommandPool,
		const IntVector2& size)
	{
		if(!device)
		{
			throw NullException(
				"VkGpuSwapchain",
				"VkGpuSwapchain",
				"device");
		}

		datas.clear();

		device.destroyRenderPass(renderPass);

		auto surfaceFormat = getBestSurfaceFormat(
			physicalDevice,
			surface);
		auto presentMode = getBestPresentMode(
			physicalDevice,
			surface);

		auto capabilities =
			physicalDevice.getSurfaceCapabilitiesKHR(surface);

		extent = getBestExtent(
			capabilities,
			size);

		auto imageCount = getBestImageCount(
			capabilities);
		auto transform = getBestTransform(
			capabilities);
		auto compositeAlpha = getBestCompositeAlpha(
			capabilities);

		auto newSwapchain = createSwapchain(
			device,
			surface,
			imageCount,
			surfaceFormat,
			extent,
			transform,
			compositeAlpha,
			presentMode,
			swapchain);

		device.destroySwapchainKHR(swapchain);
		swapchain = newSwapchain;

		renderPass = createRenderPass(
			device,
			surfaceFormat.format);

		datas = createDatas(
			device,
			swapchain,
			renderPass,
			graphicsCommandPool,
			presentCommandPool,
			surfaceFormat.format,
			extent);
	}

	VkGpuSwapchain& VkGpuSwapchain::operator=(
		VkGpuSwapchain&& _swapchain) noexcept
	{
		if(this != &_swapchain)
		{
			device = _swapchain.device;
			physicalDevice = _swapchain.physicalDevice;
			extent = _swapchain.extent;
			swapchain = _swapchain.swapchain;
			renderPass = _swapchain.renderPass;
			datas = std::move(_swapchain.datas);
			_swapchain.device = nullptr;
		}

		return *this;
	}
}