#include <injector/graphics/vk_surface.hpp>

#include <map>
#include <iostream>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	VkSurface::VkSurface(SDL_Window* window, const vk::Instance& _instance) :
		instance(_instance)
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

		physicalDevice = targetPhysicalDevices.rbegin()->second;

		VkSurfaceKHR surfaceHandle;

		if (!SDL_Vulkan_CreateSurface(
			window, static_cast<VkInstance>(_instance), &surfaceHandle))
			throw std::runtime_error(
				"Failed to create Vulkan surface: " + std::string(SDL_GetError()));

		surface = vk::SurfaceKHR(surfaceHandle);
	}
	VkSurface::~VkSurface()
	{
		instance.destroySurfaceKHR(surface);
	}

	const vk::Instance& VkSurface::getInstance() const noexcept
	{
		return instance;
	}
	const vk::PhysicalDevice& VkSurface::getPhysicalDevice() const noexcept
	{
		return physicalDevice;
	}
	const vk::SurfaceKHR& VkSurface::getSurface() const noexcept
	{
		return surface;
	}
}
