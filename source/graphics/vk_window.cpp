#include <injector/graphics/vk_window.hpp>

#include <injector/graphics/vk_shader.hpp>

#include <map>
#include <vector>
#include <iostream>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
#define FRAME_LAG 2

	VkBool32 VKAPI_CALL VkWindow::debugMessengerCallback(
		VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
		VkDebugUtilsMessageTypeFlagsEXT messageTypes,
		const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
		void* pUserData)
	{
		if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT)
		{
			std::cout << "VULKAN VERBOSE: " << pCallbackData->pMessage << "\n";
		}
		else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT)
		{
			std::cout << "VULKAN INFO: " << pCallbackData->pMessage << "\n";
		}
		else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT)
		{
			std::cout << "VULKAN WARNING: " << pCallbackData->pMessage << "\n";
		}
		else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
		{
			std::cout << "VULKAN ERROR: " << pCallbackData->pMessage << "\n";
		}

		return VK_FALSE;
	}

	vk::Instance VkWindow::createInstance(
		SDL_Window* window,
		const std::string& appName,
		uint32_t appVersion)
	{
		vk::Instance instance;

		auto instanceLayers = std::vector<const char*>();

#if !defined(NDEBUG)
		instanceLayers.push_back("VK_LAYER_KHRONOS_validation");

		auto instanceLayerProperties = vk::enumerateInstanceLayerProperties();

		if (instanceLayerProperties.size() == 0)
			throw std::runtime_error("Failed to get Vulkan instance layer properties");

		for (auto layer : instanceLayers)
		{
			auto found = false;

			for (auto& properties : instanceLayerProperties)
			{
				if (std::strcmp(layer, properties.layerName) == 0)
				{
					found = true;
					break;
				}
			}

			if (!found)
				throw std::runtime_error(
					"Failed to get Vulkan instance layer: " + std::string(layer));
		}
#endif

		uint32_t extensionCount;
		SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, nullptr);

		auto instanceExtensions = std::vector<const char*>(extensionCount);
		SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, instanceExtensions.data());

		if (extensionCount == 0)
			throw std::runtime_error(
				"Failed to get Vulkan instance extensions: " + std::string(SDL_GetError()));

#if !defined(NDEBUG)
		instanceExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
#endif

		auto instanceExtensionProperties = vk::enumerateInstanceExtensionProperties();

		if (instanceExtensionProperties.size() == 0)
			throw std::runtime_error("Failed to get Vulkan instance extension properties");

		for (auto extension : instanceExtensions)
		{
			auto found = false;

			for (auto& properties : instanceExtensionProperties)
			{
				if (std::strcmp(extension, properties.extensionName) == 0)
				{
					found = true;
					break;
				}
			}

			if (!found)
				throw std::runtime_error(
					"Failed to get Vulkan instance extension: " + std::string(extension));
		}

		auto applicationInfo = vk::ApplicationInfo(
			appName.c_str(),
			appVersion,
			"Injector Engine",
			VK_MAKE_VERSION(
				INJECTOR_VERSION_MAJOR, 
				INJECTOR_VERSION_MINOR,
				INJECTOR_VERSION_PATCH),
			VK_API_VERSION_1_0);

		auto instanceCreateInfo = vk::InstanceCreateInfo({},
			&applicationInfo,
			instanceLayers.size(),
			instanceLayers.data(),
			instanceExtensions.size(),
			instanceExtensions.data());

#if !defined(NDEBUG)
		auto debugUtilsMessengerCreateInfo = vk::DebugUtilsMessengerCreateInfoEXT({},
			vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose |
			vk::DebugUtilsMessageSeverityFlagBitsEXT::eError |
			vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning,
			vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
			vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance |
			vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation,
			static_cast<PFN_vkDebugUtilsMessengerCallbackEXT>(debugMessengerCallback));

		instanceCreateInfo.pNext = &debugUtilsMessengerCreateInfo;
#endif
		auto reslut = vk::createInstance(&instanceCreateInfo, nullptr, &instance);

		if (reslut != vk::Result::eSuccess)
			throw std::runtime_error("Failed to create Vulkan instance");

		return instance;
	}
	vk::DebugUtilsMessengerEXT VkWindow::createDebugMessenger(
		const vk::Instance& instance,
		const vk::DispatchLoaderDynamic& dispatchDynamic)
	{
#if !defined(NDEBUG)
		vk::DebugUtilsMessengerEXT debugMessenger;

		auto debugUtilsMessengerCreateInfo = vk::DebugUtilsMessengerCreateInfoEXT({},
			vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose |
			vk::DebugUtilsMessageSeverityFlagBitsEXT::eError |
			vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning,
			vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
			vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance |
			vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation,
			static_cast<PFN_vkDebugUtilsMessengerCallbackEXT>(debugMessengerCallback));

		auto result = instance.createDebugUtilsMessengerEXT(
			&debugUtilsMessengerCreateInfo, nullptr, &debugMessenger, dispatchDynamic);

		if (result != vk::Result::eSuccess)
			throw std::runtime_error("Failed to create Vulkan debug report");

		return debugMessenger;
#else
		return nullptr;
#endif
	}
	vk::PhysicalDevice VkWindow::getBestPhysicalDevice(
		const vk::Instance& instance)
	{
		auto physicalDevices = instance.enumeratePhysicalDevices();

		if (physicalDevices.size() == 0)
			throw std::runtime_error("Failed to get Vulkan physical devices");

		auto targetPhysicalDevices = std::multimap<int, vk::PhysicalDevice>();

		for (auto& device : physicalDevices)
		{
			auto score = 0;
			auto properties = device.getProperties();

			if (properties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu)
				score += 1000;
			else if (properties.deviceType == vk::PhysicalDeviceType::eVirtualGpu)
				score += 750;
			else if (properties.deviceType == vk::PhysicalDeviceType::eIntegratedGpu)
				score += 500;
			else if (properties.deviceType == vk::PhysicalDeviceType::eCpu)
				score += 250;

			targetPhysicalDevices.emplace(score, device);
			// TODO: add other tests
		}

		return targetPhysicalDevices.rbegin()->second;
	}
	vk::SurfaceKHR VkWindow::createSurface(
		const vk::Instance& instance,
		SDL_Window* window)
	{
		VkSurfaceKHR surfaceHandle;

		auto result = SDL_Vulkan_CreateSurface(window,
			static_cast<VkInstance>(instance), &surfaceHandle);

		if (result == SDL_FALSE)
			throw std::runtime_error("Failed to create Vulkan surface: " +
				std::string(SDL_GetError()));

		return vk::SurfaceKHR(surfaceHandle);
	}
	void VkWindow::getQueueFamilyIndices(
		const vk::PhysicalDevice& physicalDevice,
		const vk::SurfaceKHR& surface,
		uint32_t& graphicsQueueFamilyIndex,
		uint32_t& presentQueueFamilyIndex)
	{
		auto queueFamilyProperties = physicalDevice.getQueueFamilyProperties();

		if (queueFamilyProperties.size() == 0)
			throw std::runtime_error("Failed to get Vulkan queue family properties");

		graphicsQueueFamilyIndex = UINT32_MAX;
		presentQueueFamilyIndex = UINT32_MAX;

		for (auto i = 0; i < queueFamilyProperties.size(); i++)
		{
			auto& properties = queueFamilyProperties[i];

			if (properties.queueFlags & vk::QueueFlagBits::eGraphics)
			{
				if (graphicsQueueFamilyIndex == UINT32_MAX)
					graphicsQueueFamilyIndex = i;
			}
			// TODO ONLY TEST: && graphicsQueueFamilyIndex != i
			if (physicalDevice.getSurfaceSupportKHR(i, surface))
			{
				if (presentQueueFamilyIndex == UINT32_MAX)
					presentQueueFamilyIndex = i;
			}

			if (graphicsQueueFamilyIndex != UINT32_MAX &&
				presentQueueFamilyIndex != UINT32_MAX)
				break;
		}

		if (graphicsQueueFamilyIndex == UINT32_MAX)
			throw std::runtime_error("Failed to find Vulkan graphics queue family");
		if (presentQueueFamilyIndex == UINT32_MAX)
			throw std::runtime_error("Failed to find Vulkan present queue family");
	}
	vk::Device VkWindow::createDevice(
		const vk::PhysicalDevice& physicalDevice,
		uint32_t graphicsQueueFamilyIndex,
		uint32_t presentQueueFamilyIndex)
	{
		vk::Device device;

		auto deviceExtensionProperties = physicalDevice.enumerateDeviceExtensionProperties();

		if (deviceExtensionProperties.size() == 0)
			throw std::runtime_error("Failed to get Vulkan device extension properties");

		// TODO: create extension request mechanism
		auto deviceExtensions = std::vector<const char*>() =
		{
			VK_KHR_SWAPCHAIN_EXTENSION_NAME,
		};

		for (auto extension : deviceExtensions)
		{
			auto found = false;

			for (auto& properties : deviceExtensionProperties)
			{
				if (std::strcmp(extension, properties.extensionName) == 0)
				{
					found = true;
					break;
				}
			}

			if (!found)
				throw std::runtime_error("Failed to find Vulkan device extension: " +
					std::string(extension));
		}

		auto priority = 1.0f;
		auto deviceQueueCreateInfo = vk::DeviceQueueCreateInfo(
			{}, graphicsQueueFamilyIndex, 1, &priority);

		auto deviceQueueCreateInfos = std::vector<vk::DeviceQueueCreateInfo>() =
		{
			deviceQueueCreateInfo,
		};

		if (graphicsQueueFamilyIndex != presentQueueFamilyIndex)
		{
			deviceQueueCreateInfo.queueFamilyIndex = presentQueueFamilyIndex;
			deviceQueueCreateInfos.push_back(deviceQueueCreateInfo);
		}

		// TODO: use device features

		auto deviceCreateInfo = vk::DeviceCreateInfo({},
			deviceQueueCreateInfos.size(), deviceQueueCreateInfos.data(),
			0, nullptr,
			deviceExtensions.size(), deviceExtensions.data(),
			nullptr);

		auto result = physicalDevice.createDevice(&deviceCreateInfo, nullptr, &device);

		if (result != vk::Result::eSuccess)
			throw std::runtime_error("Failed to create Vulkan logical device");

		return device;
	}
	vk::Fence VkWindow::createFence(
		vk::Device device,
		vk::FenceCreateFlags flags)
	{
		vk::Fence fence;

		auto fenceCreateInfo = vk::FenceCreateInfo(flags);
		auto result = device.createFence(&fenceCreateInfo, nullptr, &fence);

		if (result != vk::Result::eSuccess)
			throw std::runtime_error("Failed to create Vulkan fence");

		return fence;
	}
	vk::Semaphore VkWindow::createSemaphore(
		vk::Device device,
		vk::SemaphoreCreateFlags flags)
	{
		vk::Semaphore semaphore;

		auto fenceCreateInfo = vk::SemaphoreCreateInfo(flags);
		auto result = device.createSemaphore(&fenceCreateInfo, nullptr, &semaphore);

		if (result != vk::Result::eSuccess)
			throw std::runtime_error("Failed to create Vulkan fence");

		return semaphore;
	}
	vk::Queue VkWindow::getQueue(
		const vk::Device& device,
		uint32_t queueFamilyIndex,
		uint32_t queueIndex)
	{
		auto queue = device.getQueue(queueFamilyIndex, queueIndex);

		if (!queue)
			throw std::runtime_error("Failed to get Vulkan queue");

		return queue;
	}
	uint32_t VkWindow::getBestSurfaceImageCount(
		const vk::SurfaceCapabilitiesKHR& surfaceCapabilities)
	{
		auto imageCount = surfaceCapabilities.minImageCount + 1;

		if (surfaceCapabilities.maxImageCount > 0 &&
			imageCount > surfaceCapabilities.maxImageCount)
			imageCount = surfaceCapabilities.maxImageCount;

		return imageCount;
	}
	vk::SurfaceFormatKHR VkWindow::getBestSurfaceFormat(
		const vk::PhysicalDevice& physicalDevice,
		const vk::SurfaceKHR& surface)
	{
		auto surfaceFormats = physicalDevice.getSurfaceFormatsKHR(surface);

		if (surfaceFormats.size() == 0)
			throw std::runtime_error("Failed to get Vulkan surface formats");

		auto surfaceFormat = surfaceFormats[0];

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

		return surfaceFormat;
	}
	vk::PresentModeKHR VkWindow::getBestSurfacePresentMode(
		const vk::PhysicalDevice& physicalDevice,
		const vk::SurfaceKHR& surface)
	{
		auto surfacePresentModes = physicalDevice.getSurfacePresentModesKHR(surface);

		if (surfacePresentModes.size() == 0)
			throw std::runtime_error("Failed to get Vulkan surface present modes");

		auto presentMode = vk::PresentModeKHR::eFifo;

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

		return presentMode;
	}
	vk::Extent2D VkWindow::getBestSurfaceExtent(
		const vk::SurfaceCapabilitiesKHR& surfaceCapabilities,
		const IntVector2& size)
	{
		if (surfaceCapabilities.currentExtent.width == UINT32_MAX)
		{
			return vk::Extent2D(
				std::max(surfaceCapabilities.minImageExtent.width, std::min(
					surfaceCapabilities.maxImageExtent.width, static_cast<uint32_t>(size.x))),
				std::max(surfaceCapabilities.minImageExtent.height, std::min(
					surfaceCapabilities.maxImageExtent.height, static_cast<uint32_t>(size.y))));
		}
		else
		{
			return surfaceCapabilities.currentExtent;
		}
	}
	vk::SurfaceTransformFlagBitsKHR VkWindow::getBestSurfaceTransform(
		const vk::SurfaceCapabilitiesKHR& surfaceCapabilities)
	{
		if (surfaceCapabilities.supportedTransforms & 
			vk::SurfaceTransformFlagBitsKHR::eIdentity)
		{
			return vk::SurfaceTransformFlagBitsKHR::eIdentity;
		}
		else
		{
			return surfaceCapabilities.currentTransform;
		}
	}
	vk::CompositeAlphaFlagBitsKHR VkWindow::getBestSurfaceCompositeAlpha(
		const vk::SurfaceCapabilitiesKHR& surfaceCapabilities)
	{
		if (surfaceCapabilities.supportedCompositeAlpha &
			vk::CompositeAlphaFlagBitsKHR::eOpaque)
			return vk::CompositeAlphaFlagBitsKHR::eOpaque;
		else if (surfaceCapabilities.supportedCompositeAlpha &
			vk::CompositeAlphaFlagBitsKHR::ePreMultiplied)
			return vk::CompositeAlphaFlagBitsKHR::ePreMultiplied;
		else if (surfaceCapabilities.supportedCompositeAlpha &
			vk::CompositeAlphaFlagBitsKHR::ePostMultiplied)
			return vk::CompositeAlphaFlagBitsKHR::ePostMultiplied;
		else if (surfaceCapabilities.supportedCompositeAlpha &
			vk::CompositeAlphaFlagBitsKHR::eInherit)
			return vk::CompositeAlphaFlagBitsKHR::eInherit;
		else
			throw std::runtime_error("Failed to get Vulkan surface composite alpha");
	}
	vk::SwapchainKHR VkWindow::createSwapchain(
		const vk::Device& device,
		const vk::SurfaceKHR& surface,
		uint32_t surfaceImageCount,
		const vk::SurfaceFormatKHR& surfaceFormat,
		const vk::Extent2D& surfaceExtent,
		const vk::SurfaceTransformFlagBitsKHR& surfaceTransform,
		const vk::CompositeAlphaFlagBitsKHR& surfaceCompositeAlpha,
		const vk::PresentModeKHR& surfacePresentMode)
	{
		vk::SwapchainKHR swapchain;

		auto swapchainCreateInfo = vk::SwapchainCreateInfoKHR({},
			surface,
			surfaceImageCount,
			surfaceFormat.format,
			surfaceFormat.colorSpace,
			surfaceExtent,
			1, vk::ImageUsageFlagBits::eColorAttachment,
			vk::SharingMode::eExclusive,
			0, nullptr,
			surfaceTransform,
			surfaceCompositeAlpha,
			surfacePresentMode,
			true,
			nullptr);

		auto result = device.createSwapchainKHR(&swapchainCreateInfo, nullptr, &swapchain);

		if (result != vk::Result::eSuccess)
			throw std::runtime_error("Failed to create Vulkan swapchain");

		return swapchain;
	}
	vk::RenderPass VkWindow::createRenderPass(
		const vk::Device& device,
		const vk::Format& format)
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
			0, vk::ImageLayout::eColorAttachmentOptimal);


		auto subpassDescription = vk::SubpassDescription({},
			vk::PipelineBindPoint::eGraphics,
			0, nullptr,
			1, &colorAttachmentReference);

		// TODO: make good loking
		vk::SubpassDependency dependency {};
		dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
		dependency.dstSubpass = 0;
		dependency.srcStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
		dependency.srcAccessMask = {};
		dependency.dstStageMask = vk::PipelineStageFlagBits::eColorAttachmentOutput;
		dependency.dstAccessMask = vk::AccessFlagBits::eColorAttachmentWrite;

		auto renderPassCreateInfo = vk::RenderPassCreateInfo({},
			1, &colorAttachmentDescription,
			1, &subpassDescription, 
			1, &dependency);

		auto result = device.createRenderPass(&renderPassCreateInfo, nullptr, &renderPass);

		if (result != vk::Result::eSuccess)
			throw std::runtime_error("Failed to create Vulkan render pass");

		return renderPass;
	}
	vk::PipelineLayout VkWindow::createPipelineLayout(
		const vk::Device& device)
	{
		vk::PipelineLayout pipelineLayout;

		auto pipelineLayoutCreateInfo = vk::PipelineLayoutCreateInfo(
			{}, 0, nullptr, 0, nullptr);

		auto result = device.createPipelineLayout(
			&pipelineLayoutCreateInfo, nullptr, &pipelineLayout);

		if (result != vk::Result::eSuccess)
			throw std::runtime_error("Failed to create Vulkan pipeline layout");

		return pipelineLayout;
	}
	vk::Pipeline VkWindow::createPipeline(
		const vk::Device& device,
		const vk::Extent2D& extent,
		const vk::RenderPass& renderPass,
		const vk::PipelineLayout& pipelineLayout)
	{
		auto vertexShader = VkShader(ShaderStage::Vertex, device,
			"resources/shaders/vulkan/tutorial");
		auto fragmentShader = VkShader(ShaderStage::Fragment, device,
			"resources/shaders/vulkan/tutorial");

		auto pipelineShaderStageCreateInfos = std::vector<vk::PipelineShaderStageCreateInfo>
		{
			vk::PipelineShaderStageCreateInfo
			(
				{},
				vk::ShaderStageFlagBits::eVertex,
				vertexShader.getShaderModule(),
				"main",
				nullptr
			),
			vk::PipelineShaderStageCreateInfo
			(
				{},
				vk::ShaderStageFlagBits::eFragment,
				fragmentShader.getShaderModule(),
				"main",
				nullptr
			),
		};

		auto pipelineVertexInputStateCreateInfo = vk::PipelineVertexInputStateCreateInfo(
			{}, 0, nullptr, 0, nullptr);

		auto pipelineInputAssemblyStateCreateInfo =
			vk::PipelineInputAssemblyStateCreateInfo({}, vk::PrimitiveTopology::eTriangleList, false);

		auto viewport = vk::Viewport(
			0.0f, 0.0f,
			static_cast<float>(extent.width),
			static_cast<float>(extent.height),
			0.0f, 1.0f);

		auto scissor = vk::Rect2D();
		scissor.offset = vk::Offset2D(0, 0);
		scissor.extent = extent;

		auto pipelineViewportStateCreateInfo = vk::PipelineViewportStateCreateInfo(
			{}, 1, &viewport, 1, &scissor);

		auto pipelineRasterizationStateCreateInfo = vk::PipelineRasterizationStateCreateInfo(
			{},
			false,
			false,
			vk::PolygonMode::eFill,
			vk::CullModeFlagBits::eBack,
			vk::FrontFace::eClockwise,
			false,
			0.0f,
			0.0f,
			0.0f,
			1.0f);

		auto pipelineMultisampleStateCreateInfo = vk::PipelineMultisampleStateCreateInfo(
			{},
			vk::SampleCountFlagBits::e1,
			false,
			1.0f,
			nullptr,
			false,
			false);

		auto pielineColorBlendAttacmentStateCreateInfo = vk::PipelineColorBlendAttachmentState(
			false,
			vk::BlendFactor::eOne,
			vk::BlendFactor::eZero,
			vk::BlendOp::eAdd,
			vk::BlendFactor::eOne,
			vk::BlendFactor::eZero,
			vk::BlendOp::eAdd,
			vk::ColorComponentFlagBits::eR |
			vk::ColorComponentFlagBits::eG |
			vk::ColorComponentFlagBits::eB |
			vk::ColorComponentFlagBits::eA);

		// TODO: rewrite
		auto pipelineColorBlendStateCreateInfo = vk::PipelineColorBlendStateCreateInfo();
		pipelineColorBlendStateCreateInfo.logicOpEnable = VK_FALSE;
		pipelineColorBlendStateCreateInfo.logicOp = vk::LogicOp::eCopy;
		pipelineColorBlendStateCreateInfo.attachmentCount = 1;
		pipelineColorBlendStateCreateInfo.pAttachments =
			&pielineColorBlendAttacmentStateCreateInfo;
		pipelineColorBlendStateCreateInfo.blendConstants[0] = 0.0f; // Optional
		pipelineColorBlendStateCreateInfo.blendConstants[1] = 0.0f; // Optional
		pipelineColorBlendStateCreateInfo.blendConstants[2] = 0.0f; // Optional
		pipelineColorBlendStateCreateInfo.blendConstants[3] = 0.0f; // Optional

		auto graphicsPipelineCreateInfo = vk::GraphicsPipelineCreateInfo({},
			pipelineShaderStageCreateInfos.size(),
			pipelineShaderStageCreateInfos.data(),
			&pipelineVertexInputStateCreateInfo,
			&pipelineInputAssemblyStateCreateInfo,
			nullptr,
			&pipelineViewportStateCreateInfo,
			&pipelineRasterizationStateCreateInfo,
			&pipelineMultisampleStateCreateInfo,
			nullptr,
			&pipelineColorBlendStateCreateInfo,
			nullptr,
			pipelineLayout,
			renderPass,
			0,
			nullptr,
			-1);

		auto result = device.createGraphicsPipeline(
			nullptr, graphicsPipelineCreateInfo);

		if (result.result != vk::Result::eSuccess)
			throw std::runtime_error("Failed to create Vulkan graphics pipeline");

		return result.value;
	}
	vk::CommandPool VkWindow::createCommandPool(
		const vk::Device& device,
		uint32_t queueFamilyIndex)
	{
		vk::CommandPool commandPool;

		auto commandPoolCreateInfo = vk::CommandPoolCreateInfo(
			{}, queueFamilyIndex);
		auto result = device.createCommandPool(
			&commandPoolCreateInfo, nullptr, &commandPool);

		if (result != vk::Result::eSuccess)
			throw std::runtime_error("Failed to create Vulkan command pool");

		return commandPool;
	}
	std::vector<VkSwapchainData> VkWindow::createSwapchainDatas(
		const vk::Device& device,
		const vk::SwapchainKHR& swapchain,
		const vk::RenderPass& renderPass,
		const vk::CommandPool& graphicsCommandPool,
		const vk::CommandPool& presentCommandPool,
		const vk::Format& surfaceFormat,
		const vk::Extent2D& surfaceExtent)
	{
		auto images = device.getSwapchainImagesKHR(swapchain);

		if (images.size() == 0)
			throw std::runtime_error("Failed to get Vulkan swapchain images");

		auto swapchainDatas = std::vector<VkSwapchainData>(images.size());

		auto imageViewCreateInfo = vk::ImageViewCreateInfo({},
			nullptr, vk::ImageViewType::e2D, surfaceFormat,
			vk::ComponentMapping(
				vk::ComponentSwizzle::eIdentity,
				vk::ComponentSwizzle::eIdentity,
				vk::ComponentSwizzle::eIdentity,
				vk::ComponentSwizzle::eIdentity),
			vk::ImageSubresourceRange(
				vk::ImageAspectFlagBits::eColor,
				0, 1, 0, 1));

		auto framebufferCreateInfo = vk::FramebufferCreateInfo({},
			renderPass,
			1, nullptr,
			surfaceExtent.width,
			surfaceExtent.height,
			1);

		auto commandBufferAllocateInfo = vk::CommandBufferAllocateInfo(
			nullptr, vk::CommandBufferLevel::ePrimary, 1);

		for (size_t i = 0; i < images.size(); i++)
		{
			auto& swapchainData = swapchainDatas[i];

			auto image = images[i];
			swapchainData.image = image;

			vk::ImageView imageView;
			imageViewCreateInfo.image = image;
			
			auto result = device.createImageView(
				&imageViewCreateInfo, nullptr, &imageView);

			if (result != vk::Result::eSuccess)
				throw std::runtime_error("Failed to create Vulkan swapchain image view");

			swapchainData.imageView = imageView;

			vk::Framebuffer framebuffer;
			framebufferCreateInfo.pAttachments = &imageView;

			result = device.createFramebuffer(
				&framebufferCreateInfo, nullptr, &framebuffer);

			if (result != vk::Result::eSuccess)
				throw std::runtime_error("Failed to create Vulkan framebuffer");

			swapchainData.framebuffer = framebuffer;

			vk::CommandBuffer commandBuffer;
			commandBufferAllocateInfo.commandPool = graphicsCommandPool;

			result = device.allocateCommandBuffers(
				&commandBufferAllocateInfo, &commandBuffer);

			if (result != vk::Result::eSuccess)
				throw std::runtime_error("Failed to allocate Vulkan command buffers");

			swapchainData.graphicsCommandBuffer = commandBuffer;

			if (graphicsCommandPool != presentCommandPool)
			{
				commandBufferAllocateInfo.commandPool = presentCommandPool;

				result = device.allocateCommandBuffers(
					&commandBufferAllocateInfo, &commandBuffer);

				if (result != vk::Result::eSuccess)
					throw std::runtime_error("Failed to allocate Vulkan command buffers");

				swapchainData.presentCommandBuffer = commandBuffer;
			}
			else
			{
				swapchainData.presentCommandBuffer = commandBuffer;
			}
		}

		return swapchainDatas;
	}
	void VkWindow::destroySwapchainDatas(
		vk::Device device,
		vk::CommandPool graphicsCommandPool,
		vk::CommandPool presentCommandPool,
		const std::vector<VkSwapchainData>& swapchainDatas)
	{
		for (size_t i = 0; i < swapchainDatas.size(); i++)
		{
			auto& swapchainData = swapchainDatas[i];

			if (graphicsCommandPool != presentCommandPool)
			{
				device.freeCommandBuffers(
					graphicsCommandPool, swapchainData.graphicsCommandBuffer);
				device.freeCommandBuffers(
					presentCommandPool, swapchainData.presentCommandBuffer);
			}
			else
			{
				device.freeCommandBuffers(
					graphicsCommandPool, swapchainData.graphicsCommandBuffer);
			}

			device.destroyFramebuffer(swapchainData.framebuffer);
			device.destroyImageView(swapchainData.imageView);
		}
	}
	void VkWindow::recordCommandBuffers(
		const vk::RenderPass& renderPass,
		const vk::Pipeline& pipeline,
		const vk::Extent2D& surfaceExtent,
		uint32_t graphicsQueueFamilyIndex,
		uint32_t presentQueueFamilyIndex,
		const std::vector<VkSwapchainData>& swapchainDatas)
	{
		auto commandBufferBeginInfo = vk::CommandBufferBeginInfo(
			vk::CommandBufferUsageFlagBits::eSimultaneousUse, nullptr);
		auto clearValues = vk::ClearValue(vk::ClearColorValue(
			std::array<float, 4>{0.0f, 0.0f, 0.0f, 0.0f}));
		auto renderPassBeginInfo = vk::RenderPassBeginInfo(
			renderPass, nullptr,
			vk::Rect2D({ 0, 0 }, surfaceExtent),
			1, &clearValues);
		auto imageMemoryBarrier = vk::ImageMemoryBarrier({}, {},
			vk::ImageLayout::ePresentSrcKHR,
			vk::ImageLayout::ePresentSrcKHR,
			graphicsQueueFamilyIndex,
			presentQueueFamilyIndex,
			nullptr,
			vk::ImageSubresourceRange(
				vk::ImageAspectFlagBits::eColor,
				0, 1, 0, 1));

		for (size_t i = 0; i < swapchainDatas.size(); i++)
		{
			auto& swapchainData = swapchainDatas[i];
			auto& graphicsCommandBuffer = swapchainData.graphicsCommandBuffer;
			auto result = graphicsCommandBuffer.begin(&commandBufferBeginInfo);

			if (result != vk::Result::eSuccess)
				throw std::runtime_error("Failed to begin Vulkan command buffer");

			renderPassBeginInfo.framebuffer = swapchainData.framebuffer;

			graphicsCommandBuffer.beginRenderPass(
				&renderPassBeginInfo, vk::SubpassContents::eInline);
			graphicsCommandBuffer.bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline);
			graphicsCommandBuffer.draw(3, 1, 0, 0);
			graphicsCommandBuffer.endRenderPass();

			if (graphicsQueueFamilyIndex != presentQueueFamilyIndex)
			{
				imageMemoryBarrier.image = swapchainData.image;
				graphicsCommandBuffer.pipelineBarrier(
					vk::PipelineStageFlagBits::eBottomOfPipe, 
					vk::PipelineStageFlagBits::eBottomOfPipe,
					{}, 0, nullptr, 0, nullptr, 1, &imageMemoryBarrier);
			}

			graphicsCommandBuffer.end();

			if (graphicsQueueFamilyIndex != presentQueueFamilyIndex)
			{
				auto& presentCommandBuffer = swapchainData.presentCommandBuffer;
				result = presentCommandBuffer.begin(&commandBufferBeginInfo);

				if (result != vk::Result::eSuccess)
					throw std::runtime_error("Failed to begin Vulkan command buffer");

				presentCommandBuffer.pipelineBarrier(
					vk::PipelineStageFlagBits::eBottomOfPipe, 
					vk::PipelineStageFlagBits::eBottomOfPipe, 
					{}, 0, nullptr, 0, nullptr, 1, &imageMemoryBarrier);

				presentCommandBuffer.end();
			}
		}
	}

	VkWindow::VkWindow(
		const std::string& title,
		const IntVector2& position,
		const IntVector2& size,
		uint32_t flags) :
		Window(title, position, size, flags | SDL_WINDOW_VULKAN)
	{
		instance = createInstance(window, title.c_str(), 1);

		try
		{
			dispatchDynamic = vk::DispatchLoaderDynamic(
				static_cast<VkInstance>(instance), vkGetInstanceProcAddr);

			debugMessenger = createDebugMessenger(instance, dispatchDynamic);

			physicalDevice = getBestPhysicalDevice(instance);
			surface = createSurface(instance, window);

			getQueueFamilyIndices(physicalDevice, surface,
				graphicsQueueFamilyIndex, presentQueueFamilyIndex);

			device = createDevice(physicalDevice,
				graphicsQueueFamilyIndex, presentQueueFamilyIndex);

			fences = std::vector<vk::Fence>(FRAME_LAG);
			imageAcquiredSemaphores = std::vector<vk::Semaphore>(FRAME_LAG);
			drawCompleteSemaphores = std::vector<vk::Semaphore>(FRAME_LAG);
			imageOwnershipSemaphores = std::vector<vk::Semaphore>(FRAME_LAG);

			for (size_t i = 0; i < FRAME_LAG; i++)
			{
				fences[i] = createFence(device, vk::FenceCreateFlagBits::eSignaled);
				imageAcquiredSemaphores[i] = createSemaphore(device, {});
				drawCompleteSemaphores[i] = createSemaphore(device, {});
				imageOwnershipSemaphores[i] = createSemaphore(device, {});
			}

			graphicsQueue = getQueue(device, graphicsQueueFamilyIndex, 0);
			presentQueue = getQueue(device, presentQueueFamilyIndex, 0);

			if (graphicsQueueFamilyIndex != presentQueueFamilyIndex)
			{
				graphicsCommandPool = createCommandPool(device, graphicsQueueFamilyIndex);
				presentCommandPool = createCommandPool(device, presentQueueFamilyIndex);
			}
			else
			{
				graphicsCommandPool = presentCommandPool =
					createCommandPool(device, graphicsQueueFamilyIndex);
			}

			auto surfaceCapabilities = physicalDevice.getSurfaceCapabilitiesKHR(surface);
			auto surfaceImageCount = getBestSurfaceImageCount(surfaceCapabilities);
			auto surfaceFormat = getBestSurfaceFormat(physicalDevice, surface);
			auto surfaceExtent = getBestSurfaceExtent(surfaceCapabilities, size);
			auto surfaceTransform = getBestSurfaceTransform(surfaceCapabilities);
			auto surfaceCompositeAlpha = getBestSurfaceCompositeAlpha(surfaceCapabilities);
			auto surfacePresentMode = getBestSurfacePresentMode(physicalDevice, surface);
			
			swapchain = createSwapchain(
				device,
				surface,
				surfaceImageCount,
				surfaceFormat,
				surfaceExtent,
				surfaceTransform,
				surfaceCompositeAlpha,
				surfacePresentMode);

			renderPass = createRenderPass(device, surfaceFormat.format);
			pipelineLayout = createPipelineLayout(device);
			pipeline = createPipeline(device, surfaceExtent, renderPass, pipelineLayout);

			swapchainDatas = createSwapchainDatas(
				device,
				swapchain,
				renderPass,
				graphicsCommandPool,
				presentCommandPool,
				surfaceFormat.format,
				surfaceExtent);

			recordCommandBuffers(
				renderPass,
				pipeline,
				surfaceExtent,
				graphicsQueueFamilyIndex,
				presentQueueFamilyIndex,
				swapchainDatas);

			frameIndex = 0;
		}
		catch (const std::exception& exception)
		{
#if !defined(NDEBUG)
			instance.destroy(debugMessenger, nullptr, dispatchDynamic);
#else
			instance.destroy();
#endif
			throw exception;
		}
	}
	VkWindow::~VkWindow()
	{
		device.waitIdle();

		destroySwapchainDatas(
			device,
			graphicsCommandPool,
			presentCommandPool,
			swapchainDatas);

		device.destroyPipeline(pipeline);
		device.destroyPipelineLayout(pipelineLayout);
		device.destroyRenderPass(renderPass);
		device.destroySwapchainKHR(swapchain);

		if (graphicsQueueFamilyIndex != presentQueueFamilyIndex)
		{
			device.destroyCommandPool(graphicsCommandPool);
			device.destroyCommandPool(presentCommandPool);
		}
		else
		{
			device.destroyCommandPool(graphicsCommandPool);
		}

		for (uint32_t i = 0; i < FRAME_LAG; i++)
		{
			device.waitForFences(1, &fences[i], VK_TRUE, UINT64_MAX);
			device.destroyFence(fences[i]);
			device.destroySemaphore(imageAcquiredSemaphores[i]);
			device.destroySemaphore(drawCompleteSemaphores[i]);
			device.destroySemaphore(imageOwnershipSemaphores[i]);
		}

		device.waitIdle();
		device.destroy();

		instance.destroySurfaceKHR(surface);

#if !defined(NDEBUG)
		instance.destroy(debugMessenger, nullptr, dispatchDynamic);
#else
		instance.destroy();
#endif
	}

	void VkWindow::beginRender()
	{
		device.waitForFences(1, &fences[frameIndex], true, UINT64_MAX);
		device.resetFences({fences[frameIndex]});

		vk::Result result;
		uint32_t imageIndex;

		do
		{
			result = device.acquireNextImageKHR(swapchain, UINT64_MAX,
				imageAcquiredSemaphores[frameIndex], vk::Fence(), &imageIndex);

			if (result == vk::Result::eErrorOutOfDateKHR)
			{
				auto size = getSize();
				onResize(size);
			}
			else if (result == vk::Result::eErrorSurfaceLostKHR)
			{
				instance.destroySurfaceKHR(surface);
				surface = createSurface(instance, window);

				auto size = getSize();
				onResize(size);
			}
			else if(result != vk::Result::eSuccess && result != vk::Result::eSuboptimalKHR)
			{
				throw std::runtime_error("Failed to acquire next Vulkan image");
			}
		}
		while (result != vk::Result::eSuccess);

		vk::PipelineStageFlags waitDestinationStageMask =
			vk::PipelineStageFlagBits::eColorAttachmentOutput;

		auto submitInfo = vk::SubmitInfo(
			1, &imageAcquiredSemaphores[frameIndex],
			&waitDestinationStageMask,
			1, &swapchainDatas[imageIndex].graphicsCommandBuffer,
			1, &drawCompleteSemaphores[frameIndex]);

		result = graphicsQueue.submit(1, &submitInfo, fences[frameIndex]);

		if (result != vk::Result::eSuccess)
			throw std::runtime_error("Failed to submit Vulkan graphics queue");

		auto presentInfo = vk::PresentInfoKHR(
			1, &drawCompleteSemaphores[frameIndex],
			1, &swapchain,
			&imageIndex);

		if (graphicsQueueFamilyIndex != presentQueueFamilyIndex)
		{
			submitInfo.pWaitSemaphores = &drawCompleteSemaphores[frameIndex];
			submitInfo.pCommandBuffers = &swapchainDatas[imageIndex].presentCommandBuffer;
			submitInfo.pSignalSemaphores = &imageOwnershipSemaphores[frameIndex];

			result = presentQueue.submit(1, &submitInfo, vk::Fence());

			if (result != vk::Result::eSuccess)
				throw std::runtime_error("Failed to submit Vulkan graphics queue");

			presentInfo.pWaitSemaphores = &imageOwnershipSemaphores[frameIndex];
		}

		frameIndex += 1;
		frameIndex %= FRAME_LAG;

		result = presentQueue.presentKHR(&presentInfo);
		
		if (result == vk::Result::eErrorOutOfDateKHR)
		{
			auto size = getSize();
			onResize(size);
		}
		else if (result == vk::Result::eErrorSurfaceLostKHR)
		{
			instance.destroySurfaceKHR(surface);
			surface = createSurface(instance, window);

			auto size = getSize();
			onResize(size);
		}
		else if (result != vk::Result::eSuccess && result != vk::Result::eSuboptimalKHR)
		{
			throw std::runtime_error("Failed to present next Vulkan image");
		}
	}
	void VkWindow::endRender()
	{

	}
	void VkWindow::onResize(const IntVector2& size)
	{
		device.waitIdle();

		destroySwapchainDatas(
			device,
			graphicsCommandPool,
			presentCommandPool,
			swapchainDatas);

		device.destroyPipeline(pipeline);
		device.destroyPipelineLayout(pipelineLayout);
		device.destroyRenderPass(renderPass);
		device.destroySwapchainKHR(swapchain);

		auto surfaceCapabilities = physicalDevice.getSurfaceCapabilitiesKHR(surface);
		auto surfaceImageCount = getBestSurfaceImageCount(surfaceCapabilities);
		auto surfaceFormat = getBestSurfaceFormat(physicalDevice, surface);
		auto surfaceExtent = getBestSurfaceExtent(surfaceCapabilities, size);
		auto surfaceTransform = getBestSurfaceTransform(surfaceCapabilities);
		auto surfaceCompositeAlpha = getBestSurfaceCompositeAlpha(surfaceCapabilities);
		auto surfacePresentMode = getBestSurfacePresentMode(physicalDevice, surface);

		swapchain = createSwapchain(
			device,
			surface,
			surfaceImageCount,
			surfaceFormat,
			surfaceExtent,
			surfaceTransform,
			surfaceCompositeAlpha,
			surfacePresentMode);

		renderPass = createRenderPass(device, surfaceFormat.format);
		pipelineLayout = createPipelineLayout(device);
		pipeline = createPipeline(device, surfaceExtent, renderPass, pipelineLayout);

		swapchainDatas = createSwapchainDatas(
			device,
			swapchain,
			renderPass,
			graphicsCommandPool,
			presentCommandPool,
			surfaceFormat.format,
			surfaceExtent);

		recordCommandBuffers(
			renderPass,
			pipeline,
			surfaceExtent,
			graphicsQueueFamilyIndex,
			presentQueueFamilyIndex,
			swapchainDatas);

		frameIndex = 0;
	}
}
