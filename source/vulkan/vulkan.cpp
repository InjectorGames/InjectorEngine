#include <injector_engine.hpp>

PFN_vkCreateDebugUtilsMessengerEXT pfnVkCreateDebugUtilsMessengerEXT;
PFN_vkDestroyDebugUtilsMessengerEXT pfnVkDestroyDebugUtilsMessengerEXT;

VKAPI_ATTR VkResult VKAPI_CALL vkCreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pMessenger)
{
	return pfnVkCreateDebugUtilsMessengerEXT(instance, pCreateInfo, pAllocator, pMessenger);
}
VKAPI_ATTR void VKAPI_CALL vkDestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT messenger, VkAllocationCallbacks const* pAllocator)
{
	return pfnVkDestroyDebugUtilsMessengerEXT(instance, messenger, pAllocator);
}
VKAPI_ATTR VkBool32 VKAPI_CALL debugMessageFunc(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, VkDebugUtilsMessengerCallbackDataEXT const* pCallbackData, void* pUserData)
{
	std::cout << pCallbackData->pMessage << std::endl;

	if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT)
		throw std::runtime_error("Coccured Vulkan error.");

	return VK_FALSE;
}

namespace Injector
{
	bool Vulkan::isInitialized = false;

	uint32_t Vulkan::apiVersion = VK_API_VERSION_1_0;
	uint32_t Vulkan::apiMajorVersion = 1;
	uint32_t Vulkan::apiMinorVersion = 0;

	vk::Instance Vulkan::instance = {};
	vk::DebugUtilsMessengerEXT Vulkan::debugMessenger = {};

	const std::string Vulkan::DefaultAppName = "Injector Engine - Editor";
	const uint32_t Vulkan::DefaultAppVersion = VK_MAKE_VERSION(0, 1, 0);
	const std::vector<const char*> Vulkan::DefaultInstanceLayers =
	{
		"VK_LAYER_KHRONOS_validation",
	};

	std::string Vulkan::VersionToString(uint32_t version)
	{
		return std::string(std::to_string(VK_VERSION_MAJOR(version)) + "." + std::to_string(VK_VERSION_MINOR(version)) + "." + std::to_string(VK_VERSION_PATCH(version)));
	}

	bool Vulkan::IsInitialized()
	{
		return isInitialized;
	}
	void Vulkan::Initialize(const std::string& appName, uint32_t appVersion, const std::vector<const char*>& _instanceLayers)
	{
		if (isInitialized)
			throw std::runtime_error("Failed to initialize Vulkan: Vulkan is not terminated.");
		if (!glfwVulkanSupported())
			throw std::runtime_error("Failed to initialize Vulkan: Vulkan is not supported.");

		auto debugLevel = Engine::GetDebugLevel();
		auto isDebugEnabled = Engine::IsDebugEnabled();

		apiVersion = vk::enumerateInstanceVersion();
		apiMajorVersion = VK_VERSION_MAJOR(apiVersion);
		apiMinorVersion = VK_VERSION_MINOR(apiVersion);

		if (debugLevel <= Engine::DebugLevelType::Info)
			std::cout << "Supported Vulkan version: " << VersionToString(apiVersion) << std::endl;

		vk::ApplicationInfo applicationInfo(appName.c_str(), appVersion, Engine::Name.c_str(), VK_MAKE_VERSION(INJECTOR_ENGINE_VERSION_MAJOR, INJECTOR_ENGINE_VERSION_MINOR, INJECTOR_ENGINE_VERSION_PATCH), VK_MAKE_VERSION(apiMajorVersion, apiMinorVersion, 0));

		auto instanceLayers = std::vector<const char*>();
		if (isDebugEnabled)
			instanceLayers = _instanceLayers;

		if (debugLevel <= Engine::DebugLevelType::Info)
		{
			std::cout << "\nRequired Vulkan instance layers:\n";
			for (const auto& layer : instanceLayers)
				std::cout << "Name = " << layer << std::endl;

			std::cout << "\nAvailable Vulkan instance layers:\n";
			auto layerProperties = vk::enumerateInstanceLayerProperties();
			for (const auto& layer : layerProperties)
				std::cout << "Name = " << layer.layerName << ", Spec version = " << VersionToString(layer.specVersion) << ", Impl version = " << VersionToString(layer.implementationVersion) << ", Description = " << layer.description << std::endl;
		}

		auto instanceExtensions = GetGlfwRequiredExtensions();
		if (isDebugEnabled)
			instanceExtensions.push_back(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);

		if (debugLevel <= Engine::DebugLevelType::Info)
		{
			std::cout << "\nRequired Vulkan instance extensions:\n";
			for (const auto& extension : instanceExtensions)
				std::cout << "Name = " << extension << std::endl;

			std::cout << "\nAvailable Vulkan instance extensions:\n";
			auto extensionProperties = vk::enumerateInstanceExtensionProperties();
			for (const auto& extension : extensionProperties)
				std::cout << "Name = " << extension.extensionName << ", Version = " << VersionToString(extension.specVersion) << std::endl;
		}

		vk::InstanceCreateInfo instanceCreateInfo({}, &applicationInfo, (uint32_t)instanceLayers.size(), instanceLayers.data(), (uint32_t)instanceExtensions.size(), instanceExtensions.data());
		instance = vk::createInstance(instanceCreateInfo);

		if (isDebugEnabled)
		{
			pfnVkCreateDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(instance.getProcAddr("vkCreateDebugUtilsMessengerEXT"));
			if (!pfnVkCreateDebugUtilsMessengerEXT)
				throw std::runtime_error("Failed to find Vulkan function pfnVkCreateDebugUtilsMessengerEXT.");

			pfnVkDestroyDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(instance.getProcAddr("vkDestroyDebugUtilsMessengerEXT"));
			if (!pfnVkDestroyDebugUtilsMessengerEXT)
				throw std::runtime_error("Failed to find Vulkan function pfnVkDestroyDebugUtilsMessengerEXT.");

			vk::DebugUtilsMessageSeverityFlagsEXT severityFlags;

			switch (Engine::GetDebugLevel())
			{
			case Engine::DebugLevelType::Full:
			case Engine::DebugLevelType::Trace:
				severityFlags = vk::DebugUtilsMessageSeverityFlagsEXT(vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose | vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning | vk::DebugUtilsMessageSeverityFlagBitsEXT::eError);
				break;
			case Engine::DebugLevelType::Info:
				severityFlags = vk::DebugUtilsMessageSeverityFlagsEXT(vk::DebugUtilsMessageSeverityFlagBitsEXT::eInfo | vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning | vk::DebugUtilsMessageSeverityFlagBitsEXT::eError);
				break;
			case Engine::DebugLevelType::Warn:
				severityFlags = vk::DebugUtilsMessageSeverityFlagsEXT(vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning | vk::DebugUtilsMessageSeverityFlagBitsEXT::eError);
				break;
			case Engine::DebugLevelType::Error:
			case Engine::DebugLevelType::Fatal:
				severityFlags = vk::DebugUtilsMessageSeverityFlagsEXT(vk::DebugUtilsMessageSeverityFlagBitsEXT::eError);
				break;
			}

			vk::DebugUtilsMessageTypeFlagsEXT messageTypeFlags(vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral | vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance | vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation);
			vk::DebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCreateInfo({}, severityFlags, messageTypeFlags, debugMessageFunc);
			debugMessenger = instance.createDebugUtilsMessengerEXT(debugUtilsMessengerCreateInfo);
		}

		isInitialized = true;
	}
	void Vulkan::Terminate()
	{
		if (!isInitialized)
			throw std::runtime_error("Failed to terminate Vulkan: Vulkan is not initialized.");

		instance.destroyDebugUtilsMessengerEXT(debugMessenger);
		instance.destroy();

		isInitialized = false;
	}

	vk::Instance Vulkan::GetInstance()
	{
		return instance;
	}
	vk::DebugUtilsMessengerEXT Vulkan::GetDebugMessenger()
	{
		return debugMessenger;
	}

	std::vector<const char*> Vulkan::GetGlfwRequiredExtensions()
	{
		uint32_t glfwExtensionCount = 0;
		auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
		return std::vector<const char*>(glfwExtensions, glfwExtensions + glfwExtensionCount);
	}

	vk::PhysicalDevice Vulkan::GetBestPhysicalDevice(const std::vector<vk::PhysicalDevice>& physicalDevices)
	{
		std::multimap<int, vk::PhysicalDevice> candidates;

		for (auto physicalDevice : physicalDevices)
		{
			auto score = 0;
			auto properties = physicalDevice.getProperties();

			if (properties.apiVersion < apiVersion)
				continue;

			if (properties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu)
				score += 1000;

			score += properties.limits.maxImageDimension2D;
			candidates.emplace(score, physicalDevice);
		}

		if (candidates.size() == 0)
			throw std::runtime_error("Failed to find Vulkan suitable GPU.");

		return candidates.rbegin()->second;
	}
	vk::PhysicalDevice Vulkan::GetBestPhysicalDevice()
	{
		auto devices = instance.enumeratePhysicalDevices();
		return GetBestPhysicalDevice(devices);
	}

	vk::SurfaceFormatKHR Vulkan::GetBestSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& surfaceFormats)
	{
		for (auto surfaceFormat : surfaceFormats)
		{
			if (surfaceFormat.format == vk::Format::eB8G8R8A8Srgb && surfaceFormat.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear)
				return surfaceFormat;
		}

		return surfaceFormats[0];
	}
	vk::SurfaceFormatKHR Vulkan::GetBestSurfaceFormat(vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface)
	{
		auto surfaceFormats = physicalDevice.getSurfaceFormatsKHR(surface);
		return GetBestSurfaceFormat(surfaceFormats);
	}

	vk::PresentModeKHR Vulkan::GetBestPresentMode(const std::vector<vk::PresentModeKHR>& presentModes)
	{
		for (const auto& presentMode : presentModes)
		{
			if (presentMode == vk::PresentModeKHR::eMailbox)
				return vk::PresentModeKHR::eMailbox;
		}
		for (const auto& presentMode : presentModes)
		{
			if (presentMode == vk::PresentModeKHR::eImmediate)
				return vk::PresentModeKHR::eImmediate;
		}
		for (const auto& presentMode : presentModes)
		{
			if (presentMode == vk::PresentModeKHR::eFifoRelaxed)
				return vk::PresentModeKHR::eFifoRelaxed;
		}

		return vk::PresentModeKHR::eFifo;
	}
	vk::PresentModeKHR Vulkan::GetBestPresentMode(vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface)
	{
		auto presentModes = physicalDevice.getSurfacePresentModesKHR(surface);
		return GetBestPresentMode(presentModes);
	}

	vk::Extent2D Vulkan::GetBestSurfaceImageExtent(const vk::SurfaceCapabilitiesKHR& capabilities, GLFWwindow* window)
	{
		if (capabilities.currentExtent.width == UINT32_MAX)
		{
			int width, height;
			glfwGetFramebufferSize(window, &width, &height);

			return vk::Extent2D(
				std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, static_cast<uint32_t>(width))),
				std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, static_cast<uint32_t>(height))));
		}
		else
		{
			return capabilities.currentExtent;
		}
	}
	vk::Extent2D Vulkan::GetBestSurfaceImageExtent(vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface, GLFWwindow* window)
	{
		auto surfaceCapabilities = physicalDevice.getSurfaceCapabilitiesKHR(surface);
		return GetBestSurfaceImageExtent(surfaceCapabilities, window);
	}

	uint32_t Vulkan::GetBestSurfaceImageCount(const vk::SurfaceCapabilitiesKHR& capabilities)
	{
		auto imageCount = capabilities.minImageCount + 1;
		if (capabilities.maxImageCount > 0 && imageCount > capabilities.maxImageCount)
			imageCount = capabilities.maxImageCount;
		return imageCount;
	}
	uint32_t Vulkan::GetBestSurfaceImageCount(vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface)
	{
		auto surfaceCapabilities = physicalDevice.getSurfaceCapabilitiesKHR(surface);
		return GetBestSurfaceImageCount(surfaceCapabilities);
	}

	void Vulkan::GetSurfaceQueueFamilyIndices(vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface, uint32_t& graphicsQueueIndex, uint32_t& presentQueueIndex)
	{
		graphicsQueueIndex = UINT32_MAX;
		presentQueueIndex = UINT32_MAX;

		auto queueFamilyProperties = physicalDevice.getQueueFamilyProperties();

		for (size_t i = 0; i < queueFamilyProperties.size(); i++)
		{
			if (queueFamilyProperties[i].queueFlags & vk::QueueFlagBits::eGraphics)
			{
				graphicsQueueIndex = static_cast<uint32_t>(i);
				if (physicalDevice.getSurfaceSupportKHR(static_cast<uint32_t>(i), surface))
					presentQueueIndex = (uint32_t)i;
				break;
			}
		}

		if (presentQueueIndex == UINT32_MAX)
		{
			for (size_t i = 0; i < queueFamilyProperties.size(); i++)
			{
				if (physicalDevice.getSurfaceSupportKHR(static_cast<uint32_t>(i), surface))
				{
					presentQueueIndex = static_cast<uint32_t>(i);
					break;
				}
			}
		}

		if (graphicsQueueIndex == UINT32_MAX || presentQueueIndex == UINT32_MAX)
			throw std::runtime_error("Failed to find Vulkan graphics or present queue family.");
	}

	vk::SurfaceKHR Vulkan::CreateSurface(GLFWwindow* window, const VkAllocationCallbacks* allocator)
	{
		VkSurfaceKHR surface = VK_NULL_HANDLE;
		if (glfwCreateWindowSurface(instance, window, allocator, &surface) != VK_SUCCESS)
			throw std::runtime_error("Failed to create Vulkan window surface.");
		return vk::SurfaceKHR(surface);
	}
	void Vulkan::DestroySurface(vk::SurfaceKHR surface)
	{
		instance.destroySurfaceKHR(surface);
	}

	vk::Device Vulkan::CreateSurfaceDevice(vk::PhysicalDevice physicalDevice, uint32_t graphicsQueueIndex, uint32_t presentQueueIndex, const std::vector<const char*>& deviceLayers, const std::vector<const char*>& deviceExtensions, const std::vector<vk::PhysicalDeviceFeatures>& features)
	{
		uint32_t queueCount = graphicsQueueIndex == presentQueueIndex ? 1 : 2;

		const float queuePriority = 1.0f;
		vk::DeviceQueueCreateInfo deviceQueueCreateInfos[] =
		{
			vk::DeviceQueueCreateInfo({}, graphicsQueueIndex, 1, &queuePriority),
			vk::DeviceQueueCreateInfo({}, presentQueueIndex, 1, &queuePriority),
		};

		vk::DeviceCreateInfo deviceCreateInfo({}, queueCount, deviceQueueCreateInfos, static_cast<uint32_t>(deviceLayers.size()), deviceLayers.data(), static_cast<uint32_t>(deviceExtensions.size()), deviceExtensions.data(), features.size() == 0 ? VK_NULL_HANDLE : features.data());
		return physicalDevice.createDevice(deviceCreateInfo);
	}

	std::vector<vk::Fence> Vulkan::CreateFences(vk::Device device, size_t count, vk::FenceCreateFlags flags)
	{
		std::vector<vk::Fence> fences(count);
		vk::FenceCreateInfo fenceCreateInfo(flags);

		for (size_t i = 0; i < count; i++)
			fences[i] = device.createFence(fenceCreateInfo);

		return fences;
	}
	void Vulkan::DestroyFences(vk::Device device, const std::vector<vk::Fence>& fences)
	{
		for (size_t i = 0; i < fences.size(); i++)
			device.destroyFence(fences[i]);
	}

	std::vector<vk::Semaphore> Vulkan::CreateSemaphores(vk::Device device, size_t count, vk::SemaphoreCreateFlags flags)
	{
		std::vector<vk::Semaphore> semaphores(count);
		vk::SemaphoreCreateInfo semaphoreCreateInfo(flags);
		
		for (size_t i = 0; i < count; i++)
			semaphores[i] = device.createSemaphore(semaphoreCreateInfo);

		return semaphores;
	}
	void Vulkan::DestroySemaphores(vk::Device device, const std::vector<vk::Semaphore>& semaphores)
	{
		for (size_t i = 0; i < semaphores.size(); i++)
			device.destroySemaphore(semaphores[i]);
	}
}
