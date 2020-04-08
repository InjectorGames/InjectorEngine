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
		if (!Engine::IsInitialized())
			throw std::runtime_error("Failed to initialize Vulkan: Engine is not initialized.");
		if (isInitialized)
			throw std::runtime_error("Failed to initialize Vulkan: Vulkan is not terminated.");
		if (!glfwVulkanSupported())
			throw std::runtime_error("Failed to initialize Vulkan: Vulkan is not supported.");

		auto debugLevel = Engine::GetDebugLevel();
		auto isDebugEnabled = Engine::IsDebugEnabled();
		auto apiVersion = vk::enumerateInstanceVersion();

		if (debugLevel <= Engine::DebugLevelType::Info)
			std::cout << "Supported Vulkan version: " << VersionToString(apiVersion) << std::endl;

		vk::ApplicationInfo applicationInfo(appName.c_str(), appVersion, Engine::Name.c_str(), VK_MAKE_VERSION(Engine::MajorVersion, Engine::MinorVersion, Engine::PatchVersion), VK_MAKE_VERSION(VK_VERSION_MAJOR(apiVersion), VK_VERSION_MINOR(apiVersion), 0));

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
		if (!Engine::IsInitialized())
			throw std::runtime_error("Failed to terminate Vulkan: Engine is not initialized.");
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
	vk::PhysicalDevice Vulkan::GetBestPhysicalDevice(const std::vector<vk::PhysicalDevice>& devices)
	{
		std::multimap<int, vk::PhysicalDevice> candidates;

		for (auto device : devices)
		{
			auto score = 0;
			auto properties = device.getProperties();

			if (properties.deviceType == vk::PhysicalDeviceType::eDiscreteGpu)
				score += 1000;

			score += properties.limits.maxImageDimension2D;
			candidates.emplace(score, device);
		}

		return candidates.rbegin()->second;
	}
	vk::SurfaceFormatKHR Vulkan::GetBestSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& formats)
	{
		for (auto format : formats)
		{
			if (format.format == vk::Format::eB8G8R8A8Srgb && format.colorSpace == vk::ColorSpaceKHR::eSrgbNonlinear)
				return format;
		}

		return formats[0];
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
	vk::Extent2D Vulkan::GetBestSurfaceImageExtent(const vk::SurfaceCapabilitiesKHR& capabilities, const vk::Extent2D& customExtent)
	{
		if (capabilities.currentExtent.width == UINT32_MAX) {

			auto actualExtent = vk::Extent2D();

			actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
			actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

			return actualExtent;
		}
		else
		{
			return capabilities.currentExtent;
		}
	}
	uint32_t Vulkan::GetBestSurfaceImageCount(const vk::SurfaceCapabilitiesKHR& capabilities)
	{
		auto imageCount = capabilities.minImageCount + 1;
		if (capabilities.maxImageCount > 0 && imageCount > capabilities.maxImageCount)
			imageCount = capabilities.maxImageCount;
		return imageCount;
	}
}
