#include <injector/graphics/vk_window_instance.hpp>

#include <vector>
#include <iostream>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	VkBool32 VKAPI_CALL VkWindowInstance::debugMessengerCallback(
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

	VkWindowInstance::VkWindowInstance(SDL_Window* window, 
		const std::string& appName, uint32_t appVersion)
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
		applicationInfo.pApplicationName = appName.c_str();
		applicationInfo.applicationVersion = appVersion;
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
			instance.destroy();
			throw std::runtime_error("Failed to create Vulkan debug report");
		}
#else
		debugMessenger = nullptr;
#endif
	}
	VkWindowInstance::~VkWindowInstance()
	{
#if !defined(NDEBUG)
		instance.destroy(debugMessenger, nullptr, dispatchDynamic);
#else
		instance.destroy();
#endif
	}

	const vk::Instance& VkWindowInstance::getInstance() const noexcept
	{
		return instance;
	}
	const vk::DispatchLoaderDynamic& VkWindowInstance::getDispatchDynamic() const noexcept
	{
		return dispatchDynamic;
	}
	const vk::DebugUtilsMessengerEXT& VkWindowInstance::getDebugMessenger() const noexcept
	{
		return debugMessenger;
	}
}
