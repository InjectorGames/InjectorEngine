#include <injector/graphics/vk_window.hpp>

#include <map>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>

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

	VkWindow::VkWindow(
		const std::string& title,
		const IntVector2& position,
		const IntVector2& size,
		uint32_t flags) :
		Window(title, position, size, flags | SDL_WINDOW_VULKAN)
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

		auto applicationInfo = vk::ApplicationInfo();
		applicationInfo.pApplicationName = title.c_str();
		applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		applicationInfo.pEngineName = "Injector Engine";
		applicationInfo.engineVersion = VK_MAKE_VERSION(
			INJECTOR_VERSION_MAJOR, INJECTOR_VERSION_MINOR, INJECTOR_VERSION_PATCH);
		applicationInfo.apiVersion = VK_API_VERSION_1_0;

		auto instanceCreateInfo = vk::InstanceCreateInfo();
		instanceCreateInfo.pApplicationInfo = &applicationInfo;
		instanceCreateInfo.enabledLayerCount = instanceLayers.size();
		instanceCreateInfo.ppEnabledLayerNames = instanceLayers.data();
		instanceCreateInfo.enabledExtensionCount = instanceExtensions.size();
		instanceCreateInfo.ppEnabledExtensionNames = instanceExtensions.data();

#if !defined(NDEBUG)
		auto debugUtilsMessengerCreateInfo = vk::DebugUtilsMessengerCreateInfoEXT();
		debugUtilsMessengerCreateInfo.messageSeverity =
			//vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo | // TMP
			vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose |
			vk::DebugUtilsMessageSeverityFlagBitsEXT::eError |
			vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning;
		debugUtilsMessengerCreateInfo.messageType =
			vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral |
			vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance |
			vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation;
		debugUtilsMessengerCreateInfo.pfnUserCallback =
			static_cast<PFN_vkDebugUtilsMessengerCallbackEXT>(debugMessengerCallback);
		instanceCreateInfo.pNext = &debugUtilsMessengerCreateInfo;
#endif

		instance = vk::createInstance(instanceCreateInfo);

		if (!instance)
			throw std::runtime_error("Failed to create Vulkan instance");

		dispatchDynamic = vk::DispatchLoaderDynamic(
			static_cast<VkInstance>(instance), vkGetInstanceProcAddr);

#if !defined(NDEBUG)
		debugMessenger = instance.createDebugUtilsMessengerEXT(
			debugUtilsMessengerCreateInfo, nullptr, dispatchDynamic);

		if (!debugMessenger)
		{
			instance.destroy(debugMessenger, nullptr, dispatchDynamic);
			throw std::runtime_error("Failed to create Vulkan debug report");
		}
#else
		debugMessenger = nullptr;
#endif

		VkSurfaceKHR surfaceHandle;

		if (!SDL_Vulkan_CreateSurface(
			window, static_cast<VkInstance>(instance), &surfaceHandle))
		{
			instance.destroy();
			throw std::runtime_error(
				"Failed to create Vulkan surface: " + std::string(SDL_GetError()));
		}

		surface = vk::SurfaceKHR(surfaceHandle);

		auto physicalDevices = instance.enumeratePhysicalDevices();

		if (physicalDevices.size() == 0)
		{
			instance.destroySurfaceKHR(surface);
			
#if !defined(NDEBUG)
			instance.destroy(debugMessenger, nullptr, dispatchDynamic);
#else
			instance.destroy();
#endif

			throw std::runtime_error("Failed to get Vulkan physical devices");
		}

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

		physicalDevice = targetPhysicalDevices.rbegin()->second;

		auto deviceExtensionProperties = physicalDevice.enumerateDeviceExtensionProperties();

		if (deviceExtensionProperties.size() == 0)
		{
			instance.destroySurfaceKHR(surface);
			
#if !defined(NDEBUG)
			instance.destroy(debugMessenger, nullptr, dispatchDynamic);
#else
			instance.destroy();
#endif

			throw std::runtime_error("Failed to get Vulkan device extension properties");
		}

		std::cout << "VULKAN PHYSICAL DEVICE EXTENSIONS:\n";
		for (auto& properties : deviceExtensionProperties)
			std::cout << "   name: " << properties.extensionName  << "\n";

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

		auto queueFamilyProperties = physicalDevice.getQueueFamilyProperties();

		if (queueFamilyProperties.size() == 0)
		{
			instance.destroySurfaceKHR(surface);
			
#if !defined(NDEBUG)
			instance.destroy(debugMessenger, nullptr, dispatchDynamic);
#else
			instance.destroy();
#endif

			throw std::runtime_error("Failed to get Vulkan queue family properties");
		}

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
		{
			instance.destroySurfaceKHR(surface);
			
#if !defined(NDEBUG)
			instance.destroy(debugMessenger, nullptr, dispatchDynamic);
#else
			instance.destroy();
#endif

			throw std::runtime_error("Failed to find Vulkan graphics queue family");
		}
		if (presentQueueFamilyIndex == UINT32_MAX)
		{
			instance.destroySurfaceKHR(surface);
			
#if !defined(NDEBUG)
			instance.destroy(debugMessenger, nullptr, dispatchDynamic);
#else
			instance.destroy();
#endif

			throw std::runtime_error("Failed to find Vulkan present queue family");
		}

		auto priority = 1.0f;
		auto deviceQueueCreateInfo = vk::DeviceQueueCreateInfo();
		deviceQueueCreateInfo.queueFamilyIndex = graphicsQueueFamilyIndex;
		deviceQueueCreateInfo.queueCount = 1;
		deviceQueueCreateInfo.pQueuePriorities = &priority;

		auto deviceQueueCreateInfos = std::vector<vk::DeviceQueueCreateInfo>() =
		{
			deviceQueueCreateInfo,
		};

		if (graphicsQueueFamilyIndex != presentQueueFamilyIndex)
		{
			deviceQueueCreateInfo.queueFamilyIndex = presentQueueFamilyIndex;
			deviceQueueCreateInfos.push_back(deviceQueueCreateInfo);
		}

		auto deviceCreateInfo = vk::DeviceCreateInfo();
		deviceCreateInfo.queueCreateInfoCount = deviceQueueCreateInfos.size();
		deviceCreateInfo.pQueueCreateInfos = deviceQueueCreateInfos.data();
		deviceCreateInfo.enabledLayerCount = 0;
		deviceCreateInfo.ppEnabledLayerNames = nullptr;
		deviceCreateInfo.enabledExtensionCount = deviceExtensions.size();
		deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.data();
		deviceCreateInfo.pEnabledFeatures = nullptr;

		logicalDevice = physicalDevice.createDevice(deviceCreateInfo);

		if (!logicalDevice)
			throw std::runtime_error("Failed to create Vulkan logical device");

		graphicsQueue = logicalDevice.getQueue(graphicsQueueFamilyIndex, 0);
		presentQueue = logicalDevice.getQueue(presentQueueFamilyIndex, 0);

		auto surfaceFormats = physicalDevice.getSurfaceFormatsKHR(surface);

		if (surfaceFormats.size() == 0)
		{
			logicalDevice.destroy();
			instance.destroySurfaceKHR(surface);
			
#if !defined(NDEBUG)
			instance.destroy(debugMessenger, nullptr, dispatchDynamic);
#else
			instance.destroy();
#endif

			throw std::runtime_error("Failed to get Vulkan surface formats");
		}

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
		{
			logicalDevice.destroy();
			instance.destroySurfaceKHR(surface);
			
#if !defined(NDEBUG)
			instance.destroy(debugMessenger, nullptr, dispatchDynamic);
#else
			instance.destroy();
#endif

			throw std::runtime_error("Failed to get Vulkan surface present modes");
		}

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

		auto queueFamilyIndices = std::vector<uint32_t>
		{
			graphicsQueueFamilyIndex, presentQueueFamilyIndex,
		};

		if (graphicsQueueFamilyIndex == presentQueueFamilyIndex)
		{
			swapchainCreateInfo.imageSharingMode = vk::SharingMode::eExclusive;
			swapchainCreateInfo.queueFamilyIndexCount = 0;
			swapchainCreateInfo.pQueueFamilyIndices = nullptr;
		}
		else
		{
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

		swapchain = logicalDevice.createSwapchainKHR(swapchainCreateInfo);

		if (!swapchain)
		{
			logicalDevice.destroy();
			instance.destroySurfaceKHR(surface);

#if !defined(NDEBUG)
			instance.destroy(debugMessenger, nullptr, dispatchDynamic);
#else
			instance.destroy();
#endif

			throw std::runtime_error("Failed to create Vulkan swapchain");
		}
		
		images = logicalDevice.getSwapchainImagesKHR(swapchain);

		if (images.size() == 0)
		{
			logicalDevice.destroy();
			instance.destroySurfaceKHR(surface);

#if !defined(NDEBUG)
			instance.destroy(debugMessenger, nullptr, dispatchDynamic);
#else
			instance.destroy();
#endif

			throw std::runtime_error("Failed to get Vulkan swapchain images");
		}

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
			auto newImageView = logicalDevice.createImageView(imageViewCreateInfo);

			if (!newImageView)
			{
				for (auto& imageView : imageViews)
					logicalDevice.destroyImageView(imageView);

				logicalDevice.destroy();
				instance.destroySurfaceKHR(surface);

#if !defined(NDEBUG)
				instance.destroy(debugMessenger, nullptr, dispatchDynamic);
#else
				instance.destroy();
#endif

				throw std::runtime_error("Failed to get Vulkan swapchain image view");
			}

			imageViews[i] = newImageView;
		}
	}
	VkWindow::~VkWindow()
	{
		for (auto& imageView : imageViews)
			logicalDevice.destroyImageView(imageView);

		logicalDevice.destroySwapchainKHR(swapchain);
		logicalDevice.destroy();
		instance.destroySurfaceKHR(surface);

#if !defined(NDEBUG)
		instance.destroy(debugMessenger, nullptr, dispatchDynamic);
#else
		instance.destroy();
#endif
	}
}
