#pragma once
#include <injector/defines.hpp>

#include <vulkan/vulkan.hpp>
#include <SDL_vulkan.h>

namespace INJECTOR_NAMESPACE
{
	class VkSurface
	{
	protected:
		vk::Instance instance;
		vk::PhysicalDevice physicalDevice;
		vk::SurfaceKHR surface;
		
	public:
		VkSurface(SDL_Window* window, const vk::Instance& instance);
		virtual ~VkSurface();

		const vk::Instance& getInstance() const noexcept;
		const vk::PhysicalDevice& getPhysicalDevice() const noexcept;
		const vk::SurfaceKHR& getSurface() const noexcept;
	};
}
