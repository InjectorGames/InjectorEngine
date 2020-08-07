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
		auto instanceLayers = std::vector<const char*>();

#if !defined(NDEBUG)
		instanceLayers.push_back("VK_LAYER_KHRONOS_validation");

		auto instanceLayerProperties = vk::enumerateInstanceLayerProperties();

		if (instanceLayerProperties.size() == 0)
			throw std::runtime_error("Failed to get Vulkan instance layer properties");

		std::cout << "VULKAN INSTANCE LAYER PROPERTIES:\n";
		for (auto& properties : instanceLayerProperties)
			std::cout << "   name: " << properties.layerName <<
			", description: " << properties.description << "\n";

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

		std::cout << "VULKAN INSTANCE EXTENSION PROPERTIES:\n";
		for (auto& properties : instanceExtensionProperties)
			std::cout << "   name: " << properties.extensionName << "\n";

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

		auto instance = vk::createInstance(instanceCreateInfo);

		if (!instance)
			throw std::runtime_error("Failed to create Vulkan instance");

		return instance;
	}
	vk::DebugUtilsMessengerEXT VkWindow::createDebugMessenger(
		const vk::Instance& instance,
		const vk::DispatchLoaderDynamic& dispatchDynamic)
	{
#if !defined(NDEBUG)
		auto debugUtilsMessengerCreateInfo = vk::DebugUtilsMessengerCreateInfoEXT({},
			vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose |
			vk::DebugUtilsMessageSeverityFlagBitsEXT::eError |
			vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning,
			vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
			vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance |
			vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation,
			static_cast<PFN_vkDebugUtilsMessengerCallbackEXT>(debugMessengerCallback));

		auto debugMessenger = instance.createDebugUtilsMessengerEXT(
			debugUtilsMessengerCreateInfo, nullptr, dispatchDynamic);

		if (!debugMessenger)
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

		std::cout << "VULKAN PHYSICAL DEVICES:\n";
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

			// TODO: add other tests

			targetPhysicalDevices.emplace(score, device);
			std::cout << "   name: " << properties.deviceName <<
				", type: " << vk::to_string(properties.deviceType) <<
				", score: " << score << "\n";
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

		if (!result)
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
		auto deviceExtensionProperties = physicalDevice.enumerateDeviceExtensionProperties();

		if (deviceExtensionProperties.size() == 0)
			throw std::runtime_error("Failed to get Vulkan device extension properties");

		std::cout << "VULKAN PHYSICAL DEVICE EXTENSIONS:\n";
		for (auto& properties : deviceExtensionProperties)
			std::cout << "   name: " << properties.extensionName << "\n";

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

		auto deviceCreateInfo = vk::DeviceCreateInfo({},
			deviceQueueCreateInfos.size(), deviceQueueCreateInfos.data(),
			0, nullptr,
			deviceExtensions.size(), deviceExtensions.data(),
			nullptr);

		auto device = physicalDevice.createDevice(deviceCreateInfo);

		if (!device)
			throw std::runtime_error("Failed to create Vulkan logical device");

		return device;
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
	vk::SurfaceFormatKHR VkWindow::getBestSurfaceFormat(
		const vk::PhysicalDevice& physicalDevice,
		const vk::SurfaceKHR& surface)
	{
		auto surfaceFormats = physicalDevice.getSurfaceFormatsKHR(surface);

		if (surfaceFormats.size() == 0)
			throw std::runtime_error("Failed to get Vulkan surface formats");

		std::cout << "VULKAN PHYSICAL DEVICE SURFACE FORMATS:\n";
		for (auto& foramt : surfaceFormats)
			std::cout << "   format: " << vk::to_string(foramt.format) <<
			", color_space: " << vk::to_string(foramt.colorSpace) << "\n";

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
	vk::PresentModeKHR VkWindow::getBestPresentMode(
		const vk::PhysicalDevice& physicalDevice,
		const vk::SurfaceKHR& surface)
	{
		auto surfacePresentModes = physicalDevice.getSurfacePresentModesKHR(surface);

		if (surfacePresentModes.size() == 0)
			throw std::runtime_error("Failed to get Vulkan surface present modes");

		std::cout << "VULKAN PHYSICAL DEVICE SURFACE PRESENT MODES:\n";
		for (auto mode : surfacePresentModes)
			std::cout << "   mode: " << vk::to_string(mode) << "\n";

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
	vk::Extent2D VkWindow::getBestExtent(
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
	uint32_t VkWindow::getBestImageCount(
		const vk::SurfaceCapabilitiesKHR& surfaceCapabilities)
	{
		auto imageCount = surfaceCapabilities.minImageCount + 1;

		if (surfaceCapabilities.maxImageCount > 0 &&
			imageCount > surfaceCapabilities.maxImageCount)
			imageCount = surfaceCapabilities.maxImageCount;

		return imageCount;
	}
	vk::SwapchainKHR VkWindow::createSwapchain(
		const vk::Device& device,
		const vk::SurfaceKHR& surface,
		const vk::SurfaceCapabilitiesKHR& surfaceCapabilities,
		uint32_t graphicsQueueFamilyIndex,
		uint32_t presentQueueFamilyIndex,
		const vk::SurfaceFormatKHR& surfaceFormat,
		const vk::PresentModeKHR& presentMode,
		const vk::Extent2D& extent,
		uint32_t imageCount)
	{
		vk::SharingMode sharingMode;

		auto queueFamilyIndices = std::vector<uint32_t>
		{
			graphicsQueueFamilyIndex, presentQueueFamilyIndex,
		};

		if (graphicsQueueFamilyIndex == presentQueueFamilyIndex)
		{
			sharingMode = vk::SharingMode::eExclusive;
		}
		else
		{
			sharingMode = vk::SharingMode::eConcurrent;
			queueFamilyIndices.push_back(graphicsQueueFamilyIndex);
			queueFamilyIndices.push_back(presentQueueFamilyIndex);
		}

		auto swapchainCreateInfo = vk::SwapchainCreateInfoKHR({},
			surface,
			imageCount,
			surfaceFormat.format,
			surfaceFormat.colorSpace,
			extent,
			1,
			vk::ImageUsageFlagBits::eColorAttachment,
			sharingMode,
			queueFamilyIndices.size(),
			queueFamilyIndices.data(),
			surfaceCapabilities.currentTransform,
			vk::CompositeAlphaFlagBitsKHR::eOpaque,
			presentMode,
			true,
			nullptr);

		auto swapchain = device.createSwapchainKHR(swapchainCreateInfo);

		if (!swapchain)
			throw std::runtime_error("Failed to create Vulkan swapchain");

		return swapchain;
	}
	std::vector<vk::Image> VkWindow::getImages(
		const vk::Device& device,
		const vk::SwapchainKHR& swapchain)
	{
		auto images = device.getSwapchainImagesKHR(swapchain);

		if (images.size() == 0)
			throw std::runtime_error("Failed to get Vulkan swapchain images");

		return images;
	}
	std::vector<vk::ImageView> VkWindow::createImageViews(
		const vk::Device& device,
		const vk::Format& format,
		const std::vector<vk::Image>& images)
	{
		auto imageViewCreateInfo = vk::ImageViewCreateInfo({},
			nullptr, vk::ImageViewType::e2D, format,
			vk::ComponentMapping(
				vk::ComponentSwizzle::eIdentity,
				vk::ComponentSwizzle::eIdentity,
				vk::ComponentSwizzle::eIdentity,
				vk::ComponentSwizzle::eIdentity),
			vk::ImageSubresourceRange(
				vk::ImageAspectFlagBits::eColor,
				0, 1, 0, 1)
			);

		auto imageViews = std::vector<vk::ImageView>(images.size());

		for (size_t i = 0; i < images.size(); i++)
		{
			imageViewCreateInfo.image = images[i];
			auto newImageView = device.createImageView(imageViewCreateInfo);

			if (!newImageView)
				throw std::runtime_error("Failed to get Vulkan swapchain image view");

			imageViews[i] = newImageView;
		}

		return imageViews;
	}
	vk::RenderPass VkWindow::createRenderPass(
		const vk::Device& device,
		const vk::Format& format)
	{
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

		auto renderPass = device.createRenderPass(renderPassCreateInfo);

		if (!renderPass)
			throw std::runtime_error("Failed to create Vulkan render pass");

		return renderPass;
	}
	vk::PipelineLayout VkWindow::createPipelineLayout(
		const vk::Device& device)
	{
		auto pipelineLayoutCreateInfo = vk::PipelineLayoutCreateInfo(
			{}, 0, nullptr, 0, nullptr);

		auto pipelineLayout = device.createPipelineLayout(pipelineLayoutCreateInfo);

		if (!pipelineLayout)
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

		auto pipeline = device.createGraphicsPipeline(
			nullptr, graphicsPipelineCreateInfo).value;

		if (!pipeline)
			throw std::runtime_error("Failed to create Vulkan graphics pipeline");

		return pipeline;
	}
	std::vector<vk::Framebuffer> VkWindow::createFramebuffers(
		const vk::Device& device,
		const vk::RenderPass renderPass,
		const std::vector<vk::ImageView>& imageViews,
		const vk::Extent2D& extent)
	{
		auto framebuffers = std::vector<vk::Framebuffer>(imageViews.size());

		auto framebufferCreateInfo = vk::FramebufferCreateInfo({},
			renderPass,
			1,
			nullptr,
			extent.width,
			extent.height,
			1);

		for (size_t i = 0; i < imageViews.size(); i++)
		{
			framebufferCreateInfo.pAttachments = &imageViews[i];
			auto framebuffer = device.createFramebuffer(framebufferCreateInfo);

			if(!framebuffer)
				throw std::runtime_error("Failed to create Vulkan framebuffer");

			framebuffers[i] = framebuffer;
		}

		return framebuffers;
	}
	vk::CommandPool VkWindow::createCommandPool(
		const vk::Device& device,
		uint32_t graphicsQueueFamilyIndex)
	{
		auto commandPoolCreateInfo = vk::CommandPoolCreateInfo(
			{}, graphicsQueueFamilyIndex);
		auto commandPool = device.createCommandPool(commandPoolCreateInfo);

		if (!commandPool)
			throw std::runtime_error("failed to create command pool!");

		return commandPool;
	}
	std::vector<vk::CommandBuffer> VkWindow::allocateCommandBuffers(
		const vk::Device& device,
		const vk::Extent2D& extent,
		const vk::CommandPool& commandPool,
		const vk::RenderPass& renderPass,
		const vk::Pipeline& pipeline,
		const std::vector<vk::Framebuffer>& framebuffers)
	{
		auto commandBufferAllocateInfo = vk::CommandBufferAllocateInfo(
			commandPool, vk::CommandBufferLevel::ePrimary, framebuffers.size());

		auto commandBuffers = device.allocateCommandBuffers(commandBufferAllocateInfo);

		if (commandBuffers.size() == 0)
			throw std::runtime_error("Failed to allocate Vulkan command buffers");

		auto clearValue = vk::ClearValue(vk::ClearColorValue(
			std::array<float, 4>{0.0f, 0.0f, 0.0f, 0.0f}));
		auto renderPassBeginInfo = vk::RenderPassBeginInfo(
			renderPass, nullptr,
			vk::Rect2D({0, 0}, extent),
			1, &clearValue);

		for (size_t i = 0; i < framebuffers.size(); i++)
		{
			auto commandBuffer = commandBuffers[i];
			auto commandBufferBeginInfo = vk::CommandBufferBeginInfo({}, nullptr);
			commandBuffer.begin(commandBufferBeginInfo);

			renderPassBeginInfo.framebuffer = framebuffers[i];
			commandBuffer.beginRenderPass(renderPassBeginInfo, vk::SubpassContents::eInline);
			commandBuffer.bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline);
			commandBuffer.draw(3, 1, 0, 0);
			commandBuffer.endRenderPass();
			commandBuffer.end();
		}

		return commandBuffers;
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

			graphicsQueue = getQueue(device, graphicsQueueFamilyIndex, 0);
			presentQueue = getQueue(device, presentQueueFamilyIndex, 0);

			surfaceFormat = getBestSurfaceFormat(physicalDevice, surface);
			presentMode = getBestPresentMode(physicalDevice, surface);

			auto surfaceCapabilities = physicalDevice.getSurfaceCapabilitiesKHR(surface);
			extent = getBestExtent(surfaceCapabilities, size);
			imageCount = getBestImageCount(surfaceCapabilities);

			swapchain = createSwapchain(
				device,
				surface,
				surfaceCapabilities,
				graphicsQueueFamilyIndex,
				presentQueueFamilyIndex,
				surfaceFormat,
				presentMode,
				extent,
				imageCount);

			images = getImages(device, swapchain);
			imageViews = createImageViews(device, surfaceFormat.format, images);
			renderPass = createRenderPass(device, surfaceFormat.format);
			pipelineLayout = createPipelineLayout(device);
			pipeline = createPipeline(device, extent, renderPass, pipelineLayout);
			framebuffers = createFramebuffers(device, renderPass, imageViews, extent);
			commandPool = createCommandPool(device, graphicsQueueFamilyIndex);
			commandBuffers = allocateCommandBuffers(
				device, extent, commandPool, renderPass, pipeline, framebuffers);

			auto semaphoreCreateInfo = vk::SemaphoreCreateInfo();
			imageAvailableSemaphore = device.createSemaphore(semaphoreCreateInfo);
			renderFinishedSemaphore = device.createSemaphore(semaphoreCreateInfo);
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
		device.freeCommandBuffers(commandPool, commandBuffers.size(), commandBuffers.data());
		device.destroyCommandPool(commandPool);

		for (auto& framebuffer : framebuffers)
			device.destroyFramebuffer(framebuffer);

		device.destroyPipeline(pipeline);
		device.destroyPipelineLayout(pipelineLayout);
		device.destroyRenderPass(renderPass);

		for (auto& imageView : imageViews)
			device.destroyImageView(imageView);

		device.destroySwapchainKHR(swapchain);
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
		auto imageIndex = device.acquireNextImageKHR(
			swapchain, UINT64_MAX, imageAvailableSemaphore, nullptr).value;

		vk::SubmitInfo submitInfo {};
		vk::Semaphore waitSemaphores[] = { imageAvailableSemaphore };
		vk::PipelineStageFlags waitStages[] = { vk::PipelineStageFlagBits::eColorAttachmentOutput };
		submitInfo.waitSemaphoreCount = 1;
		submitInfo.pWaitSemaphores = waitSemaphores;
		submitInfo.pWaitDstStageMask = waitStages;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffers[imageIndex];

		vk::Semaphore signalSemaphores[] = { renderFinishedSemaphore };
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = signalSemaphores;
		graphicsQueue.submit(1, &submitInfo, nullptr);

		vk::PresentInfoKHR presentInfo {};
		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = signalSemaphores;

		vk::SwapchainKHR swapChains[] = { swapchain };
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = swapChains;
		presentInfo.pImageIndices = &imageIndex;
		presentInfo.pResults = nullptr; // Optional
		presentQueue.presentKHR(&presentInfo);
	}
	void VkWindow::endRender()
	{

	}
}
