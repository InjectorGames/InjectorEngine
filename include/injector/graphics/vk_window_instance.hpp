#pragma once
#include <injector/defines.hpp>

#include <vulkan/vulkan.hpp>
#include <SDL_vulkan.h>

namespace INJECTOR_NAMESPACE
{
	class VkWindowInstance
	{
	protected:
		vk::Instance instance;
		vk::DispatchLoaderDynamic dispatchDynamic;
		vk::DebugUtilsMessengerEXT debugMessenger;

		static VkBool32 VKAPI_CALL debugMessengerCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageTypes,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData);
	public:
		VkWindowInstance(SDL_Window* window,
			const std::string& appName, uint32_t appVersion);
		virtual ~VkWindowInstance();

		const vk::Instance& getInstance() const noexcept;
		const vk::DispatchLoaderDynamic& getDispatchDynamic() const noexcept;
		const vk::DebugUtilsMessengerEXT& getDebugMessenger() const noexcept;
	};
}
