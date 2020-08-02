#include <injector/graphics/vk_window.hpp>

#include <map>
#include <vector>
#include <iostream>
#include <stdexcept>

#include <vulkan/vulkan.h>

namespace INJECTOR_NAMESPACE
{
#define FRAME_LAG 2

	static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
		VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType,
		uint64_t srcObject, size_t location, int32_t msgCode, 
		const char* pLayerPrefix, const char* pMsg, void* pUserData)
	{
		if (flags & VK_DEBUG_REPORT_ERROR_BIT_EXT)
		{
			std::cerr << "VULKAN ERROR: [" << pLayerPrefix << "] Code " << 
				msgCode << " : " << pMsg << "\n";
		}
		else if (flags & VK_DEBUG_REPORT_WARNING_BIT_EXT)
		{
			std::cerr << "VULKAN WARNING: [" << pLayerPrefix << "] Code " << 
				msgCode << " : " << pMsg << "\n";
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

		std::cout << "\nVULKAN INSTANCE LAYER PROPERTIES:\n";
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
				throw std::runtime_error("Failed to find Vulkan instance layer: " +
					std::string(layer));
		}
#endif

		uint32_t extensionCount;
		SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, nullptr);

		auto instanceExtensions = std::vector<const char*>(extensionCount);
		SDL_Vulkan_GetInstanceExtensions(window, &extensionCount, instanceExtensions.data());

		auto applicationInfo = VkApplicationInfo();
		applicationInfo.pApplicationName = title.c_str();
		applicationInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
		applicationInfo.pEngineName = "Injector Engine";
		applicationInfo.engineVersion = VK_MAKE_VERSION(
			INJECTOR_VERSION_MAJOR, INJECTOR_VERSION_MINOR, INJECTOR_VERSION_PATCH);
		applicationInfo.apiVersion = VK_API_VERSION_1_0;

		auto instanceCreateInfo = VkInstanceCreateInfo();
		instanceCreateInfo.pApplicationInfo = &applicationInfo;
		instanceCreateInfo.enabledLayerCount = instanceLayers.size();
		instanceCreateInfo.ppEnabledLayerNames = instanceLayers.data();
		instanceCreateInfo.enabledExtensionCount = instanceExtensions.size();
		instanceCreateInfo.ppEnabledExtensionNames = instanceExtensions.data();

		VkInstance instanceHandle;

		if (vkCreateInstance(&instanceCreateInfo, nullptr, &instanceHandle) != VK_SUCCESS)
			throw std::runtime_error("Failed to create Vulkan instance");

		instance = vk::Instance(instanceHandle);

		auto debugReportCallbackCreateInfo = vk::DebugReportCallbackCreateInfoEXT();
		debugReportCallbackCreateInfo.pfnCallback = 
			(PFN_vkDebugReportCallbackEXT)debugCallback;
		debugReportCallbackCreateInfo.flags = 
			vk::DebugReportFlagBitsEXT::eError | vk::DebugReportFlagBitsEXT::eWarning;

		auto dispatchLoaderDynamic = std::make_unique<vk::DispatchLoaderDynamic>(
			instance, vkGetInstanceProcAddr);
		debugReport = instance.createDebugReportCallbackEXT(
			debugReportCallbackCreateInfo, nullptr, *dispatchLoaderDynamic);

		if (!debugReport)
		{
			instance.destroy();
			throw std::runtime_error("Failed to create Vulkan debug report");
		}

		VkSurfaceKHR surfaceHandle;

		if (!SDL_Vulkan_CreateSurface(window, instanceHandle, &surfaceHandle))
		{
			instance.destroy();
			throw std::runtime_error("Failed to create Vulkan surface");
		}

		surface = vk::SurfaceKHR(surfaceHandle);

		auto physicalDevices = instance.enumeratePhysicalDevices();

		if (physicalDevices.size() == 0)
		{
			instance.destroySurfaceKHR(surface);
			instance.destroy();
			throw std::runtime_error("Failed to get Vulkan physical devices");
		}

		auto targetPhysicalDevices = std::multimap<int, vk::PhysicalDevice>();

		std::cout << "\nVULKAN PHYSICAL DEVICES:\n";
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
			instance.destroy();
			throw std::runtime_error("Failed to get Vulkan device extension properties");
		}

		std::cout << "\nVULKAN PHYSICAL DEVICE EXTENSIONS:\n";
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

		auto queueFamilyProperties = physicalDevice.getQueueFamilyProperties();

		if (queueFamilyProperties.size() == 0)
		{
			instance.destroySurfaceKHR(surface);
			instance.destroy();
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
			instance.destroy();
			throw std::runtime_error("Failed to find Vulkan graphics queue family");
		}
		if (presentQueueFamilyIndex == UINT32_MAX)
		{
			instance.destroySurfaceKHR(surface);
			instance.destroy();
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

		auto surfaceFormats = physicalDevice.getSurfaceFormatsKHR(surface);

		if (surfaceFormats.size() == 0)
		{
			logicalDevice.destroy();
			instance.destroySurfaceKHR(surface);
			instance.destroy();
			throw std::runtime_error("Failed to get Vulkan surface formats");
		}

		std::cout << "\nVULKAN PHYSICAL DEVICE SURFACE FORMATS:\n";
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
			instance.destroy();
			throw std::runtime_error("Failed to get Vulkan surface present modes");
		}

		std::cout << "\nVULKAN PHYSICAL DEVICE SURFACE PRESENT MODES:\n";
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


	}
	VkWindow::~VkWindow()
	{
		logicalDevice.destroy();
		instance.destroySurfaceKHR(surface);

		auto dispatchLoaderDynamic = std::make_unique<vk::DispatchLoaderDynamic>(
			instance, vkGetInstanceProcAddr);
		instance.destroyDebugReportCallbackEXT(
			debugReport, nullptr, *dispatchLoaderDynamic);

		instance.destroy();
	}
}
