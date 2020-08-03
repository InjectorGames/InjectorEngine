#include <injector/graphics/vk_logical_device.hpp>

#include <vector>
#include <iostream>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	VkLogicalDevice::VkLogicalDevice(
		const vk::PhysicalDevice& physicalDevice, const vk::SurfaceKHR& surface)
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

		device = physicalDevice.createDevice(deviceCreateInfo);

		if (!device)
			throw std::runtime_error("Failed to create Vulkan logical device");

		graphicsQueue = device.getQueue(graphicsQueueFamilyIndex, 0);
		presentQueue = device.getQueue(presentQueueFamilyIndex, 0);
	}
	VkLogicalDevice::~VkLogicalDevice()
	{
		device.destroy();
	}

	const vk::Device& VkLogicalDevice::getDevice() const noexcept
	{
		return device;
	}

	uint32_t VkLogicalDevice::getGraphicsQueueFamilyIndex() const noexcept
	{
		return graphicsQueueFamilyIndex;
	}
	uint32_t VkLogicalDevice::getPresentQueueFamilyIndex() const noexcept
	{
		return presentQueueFamilyIndex;
	}

	const vk::Queue& VkLogicalDevice::getGraphicsQueue() const noexcept
	{
		return graphicsQueue;
	}
	const vk::Queue& VkLogicalDevice::getPresentQueue() const noexcept
	{
		return presentQueue;
	}
}
