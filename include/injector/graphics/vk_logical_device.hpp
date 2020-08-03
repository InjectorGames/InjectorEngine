#pragma once
#include <injector/defines.hpp>

#include <vulkan/vulkan.hpp>
#include <SDL_vulkan.h>

namespace INJECTOR_NAMESPACE
{
	class VkLogicalDevice
	{
	protected:
		vk::Device device;
		uint32_t graphicsQueueFamilyIndex;
		uint32_t presentQueueFamilyIndex;
		vk::Queue graphicsQueue;
		vk::Queue presentQueue;
	public:
		VkLogicalDevice(
			const vk::PhysicalDevice& physicalDevice, const vk::SurfaceKHR& surface);
		virtual ~VkLogicalDevice();

		const vk::Device& getDevice() const noexcept;

		uint32_t getGraphicsQueueFamilyIndex() const noexcept;
		uint32_t getPresentQueueFamilyIndex() const noexcept;

		const vk::Queue& getGraphicsQueue() const noexcept;
		const vk::Queue& getPresentQueue() const noexcept;
	};
}
