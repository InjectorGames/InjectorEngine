#pragma once
#include <injector/graphics/window.hpp>

#include <vulkan/vulkan.hpp>
#include <SDL_vulkan.h>

namespace INJECTOR_NAMESPACE
{
	class VkWindow : public Window
	{
	protected:
		vk::Instance instance;
		vk::DispatchLoaderDynamic dispatchDynamic;
		vk::DebugUtilsMessengerEXT debugMessenger;
		vk::PhysicalDevice physicalDevice;
		vk::SurfaceKHR surface;
		vk::Device device;
		uint32_t graphicsQueueFamilyIndex;
		uint32_t presentQueueFamilyIndex;
		vk::Queue graphicsQueue;
		vk::Queue presentQueue;
		vk::SurfaceFormatKHR surfaceFormat;
		vk::PresentModeKHR presentMode;
		vk::Extent2D extent;
		uint32_t imageCount;
		vk::SwapchainKHR swapchain;
		std::vector<vk::Image> images;
		std::vector<vk::ImageView> imageViews;
		vk::RenderPass renderPass;
		vk::PipelineLayout pipelineLayout;
		vk::Pipeline pipeline;
		std::vector<vk::Framebuffer> framebuffers;
		vk::CommandPool commandPool;
		std::vector<vk::CommandBuffer> commandBuffers;
		vk::Semaphore imageAvailableSemaphore;
		vk::Semaphore renderFinishedSemaphore;

		std::vector<vk::Semaphore> imageAcquiredSemaphores;
		std::vector<vk::Semaphore> drawCompleteSemaphores;
		std::vector<vk::Semaphore> imageOwnershipSemaphores;

		static VkBool32 VKAPI_CALL debugMessengerCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageTypes,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData);

		static vk::Instance createInstance(
			SDL_Window* window,
			const std::string& appName,
			uint32_t appVersion);
		static vk::DebugUtilsMessengerEXT createDebugMessenger(
			const vk::Instance& instance,
			const vk::DispatchLoaderDynamic& dispatchDynamic);
		static vk::PhysicalDevice getBestPhysicalDevice(
			const vk::Instance& instance);
		static vk::SurfaceKHR createSurface(
			const vk::Instance& instance,
			SDL_Window* window);
		static void getQueueFamilyIndices(
			const vk::PhysicalDevice& physicalDevice,
			const vk::SurfaceKHR& surface,
			uint32_t& graphicsQueueFamilyIndex,
			uint32_t& presentQueueFamilyIndex);
		static vk::Device createDevice(
			const vk::PhysicalDevice& physicalDevice,
			uint32_t graphicsQueueFamilyIndex,
			uint32_t presentQueueFamilyIndex);
		static vk::Queue getQueue(
			const vk::Device& device,
			uint32_t queueFamilyIndex,
			uint32_t queueIndex);
		static vk::SurfaceFormatKHR getBestSurfaceFormat(
			const vk::PhysicalDevice& physicalDevice,
			const vk::SurfaceKHR& surface);
		static vk::PresentModeKHR getBestPresentMode(
			const vk::PhysicalDevice& physicalDevice,
			const vk::SurfaceKHR& surface);
		static vk::Extent2D getBestExtent(
			const vk::SurfaceCapabilitiesKHR& surfaceCapabilities,
			const IntVector2& size);
		static uint32_t getBestImageCount(
			const vk::SurfaceCapabilitiesKHR& surfaceCapabilities);
		static vk::SwapchainKHR createSwapchain(
			const vk::Device& device,
			const vk::SurfaceKHR& surface,
			const vk::SurfaceCapabilitiesKHR& surfaceCapabilities,
			uint32_t graphicsQueueFamilyIndex,
			uint32_t presentQueueFamilyIndex,
			const vk::SurfaceFormatKHR& surfaceFormat,
			const vk::PresentModeKHR& presentMode,
			const vk::Extent2D& extent,
			uint32_t imageCount);
		static std::vector<vk::Image> getImages(
			const vk::Device& device,
			const vk::SwapchainKHR& swapchain);
		static std::vector<vk::ImageView> createImageViews(
			const vk::Device& device,
			const vk::Format& format,
			const std::vector<vk::Image>& images);
		static vk::RenderPass createRenderPass(
			const vk::Device& device,
			const vk::Format& format);
		static vk::PipelineLayout createPipelineLayout(
			const vk::Device& device);
		static vk::Pipeline createPipeline(
			const vk::Device& device,
			const vk::Extent2D& extent,
			const vk::RenderPass& renderPass,
			const vk::PipelineLayout& pipelineLayout);
		static std::vector<vk::Framebuffer> createFramebuffers(
			const vk::Device& device,
			const vk::RenderPass renderPass,
			const std::vector<vk::ImageView>& imageViews,
			const vk::Extent2D& extent);
		static vk::CommandPool createCommandPool(
			const vk::Device& device,
			uint32_t graphicsQueueFamilyIndex);
		static std::vector<vk::CommandBuffer> allocateCommandBuffers(
			const vk::Device& device,
			const vk::Extent2D& extent,
			const vk::CommandPool& commandPool,
			const vk::RenderPass& renderPass,
			const vk::Pipeline& pipeline,
			const std::vector<vk::Framebuffer>& framebuffers);
	public:
		VkWindow(const std::string& title = defaultTitle,
			const IntVector2& position = defaultPosition,
			const IntVector2& size = defaultSize,
			uint32_t flags = defaultFlags);
		virtual ~VkWindow();

		void beginRender() override;
		void endRender() override;
	};
}
