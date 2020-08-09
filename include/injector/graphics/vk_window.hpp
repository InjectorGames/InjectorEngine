#pragma once
#include <injector/graphics/window.hpp>

#include <vulkan/vulkan.hpp>
#include <SDL_vulkan.h>

namespace INJECTOR_NAMESPACE
{
	struct VkSwapchainData
	{
		vk::Image image;
		vk::ImageView imageView;
		vk::Framebuffer framebuffer;
		vk::CommandBuffer graphicsCommandBuffer;
		vk::CommandBuffer presentCommandBuffer;
	};

	class VkWindow : public Window
	{
	protected:
		vk::Instance instance;
		vk::DispatchLoaderDynamic dispatchDynamic;
		vk::DebugUtilsMessengerEXT debugMessenger;
		vk::PhysicalDevice physicalDevice;
		vk::SurfaceKHR surface;
		uint32_t graphicsQueueFamilyIndex;
		uint32_t presentQueueFamilyIndex;
		vk::Device device;
		std::vector<vk::Fence> fences;
		std::vector<vk::Semaphore> imageAcquiredSemaphores;
		std::vector<vk::Semaphore> drawCompleteSemaphores;
		std::vector<vk::Semaphore> imageOwnershipSemaphores;
		vk::Queue graphicsQueue;
		vk::Queue presentQueue;
		vk::CommandPool graphicsCommandPool;
		vk::CommandPool presentCommandPool;
		vk::SwapchainKHR swapchain;
		vk::RenderPass renderPass;
		vk::PipelineLayout pipelineLayout;
		vk::Pipeline pipeline;
		std::vector<VkSwapchainData> swapchainDatas;
		uint32_t frameIndex;

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
		static vk::Fence createFence(
			vk::Device device,
			vk::FenceCreateFlags flags);
		static vk::Semaphore createSemaphore(
			vk::Device device,
			vk::SemaphoreCreateFlags flags);
		static vk::Queue getQueue(
			const vk::Device& device,
			uint32_t queueFamilyIndex,
			uint32_t queueIndex);
		static uint32_t getBestSurfaceImageCount(
			const vk::SurfaceCapabilitiesKHR& surfaceCapabilities);
		static vk::SurfaceFormatKHR getBestSurfaceFormat(
			const vk::PhysicalDevice& physicalDevice,
			const vk::SurfaceKHR& surface);
		static vk::PresentModeKHR getBestSurfacePresentMode(
			const vk::PhysicalDevice& physicalDevice,
			const vk::SurfaceKHR& surface);
		static vk::Extent2D getBestSurfaceExtent(
			const vk::SurfaceCapabilitiesKHR& surfaceCapabilities,
			const IntVector2& size);
		static vk::SurfaceTransformFlagBitsKHR getBestSurfaceTransform(
			const vk::SurfaceCapabilitiesKHR& surfaceCapabilities);
		static vk::CompositeAlphaFlagBitsKHR getBestSurfaceCompositeAlpha(
			const vk::SurfaceCapabilitiesKHR& surfaceCapabilities);
		static vk::SwapchainKHR createSwapchain(
			const vk::Device& device,
			const vk::SurfaceKHR& surface,
			uint32_t surfaceImageCount,
			const vk::SurfaceFormatKHR& surfaceFormat,
			const vk::Extent2D& surfaceExtent,
			const vk::SurfaceTransformFlagBitsKHR& surfaceTransform,
			const vk::CompositeAlphaFlagBitsKHR& surfaceCompositeAlpha,
			const vk::PresentModeKHR& surfacePresentMode);
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
		static vk::CommandPool createCommandPool(
			const vk::Device& device,
			uint32_t queueFamilyIndex);
		static std::vector<VkSwapchainData> createSwapchainDatas(
			const vk::Device& device,
			const vk::SwapchainKHR& swapchain,
			const vk::RenderPass& renderPass,
			const vk::CommandPool& graphicsCommandPool,
			const vk::CommandPool& presentCommandPool,
			const vk::Format& surfaceFormat,
			const vk::Extent2D& surfaceExtent);
		static void destroySwapchainDatas(
			vk::Device device,
			vk::CommandPool graphicsCommandPool,
			vk::CommandPool presentCommandPool,
			const std::vector<VkSwapchainData>& swapchainDatas);
		static void recordCommandBuffers(
			const vk::RenderPass& renderPass,
			const vk::Pipeline& pipeline,
			const vk::Extent2D& surfaceExtent,
			uint32_t graphicsQueueFamilyIndex,
			uint32_t presentQueueFamilyIndex,
			const std::vector<VkSwapchainData>& swapchainDatas);
	public:
		VkWindow(const std::string& title = defaultTitle,
			const IntVector2& position = defaultPosition,
			const IntVector2& size = defaultSize,
			uint32_t flags = defaultFlags);
		virtual ~VkWindow();

		void beginRender() override;
		void endRender() override;
		void onResize(const IntVector2& size) override;
	};
}
