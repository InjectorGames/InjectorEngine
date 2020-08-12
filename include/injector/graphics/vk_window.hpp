#pragma once
#include <injector/graphics/window.hpp>

#include <vulkan/vulkan.hpp>
#include <vk_mem_alloc.h>
#include <SDL_vulkan.h>

namespace INJECTOR_NAMESPACE
{
	// TODO: move to separate file
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
		VmaAllocator memoryAllocator;
		std::vector<vk::Fence> fences;
		std::vector<vk::Semaphore> imageAcquiredSemaphores;
		std::vector<vk::Semaphore> drawCompleteSemaphores;
		std::vector<vk::Semaphore> imageOwnershipSemaphores;
		vk::Queue graphicsQueue;
		vk::Queue presentQueue;
		vk::CommandPool graphicsCommandPool;
		vk::CommandPool presentCommandPool;
		vk::Extent2D surfaceExtent;
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
			vk::Instance instance,
			const vk::DispatchLoaderDynamic& dispatchDynamic);
		static vk::PhysicalDevice getBestPhysicalDevice(
			vk::Instance instance);
		static vk::SurfaceKHR createSurface(
			vk::Instance instance,
			SDL_Window* window);
		static void getQueueFamilyIndices(
			vk::PhysicalDevice physicalDevice,
			vk::SurfaceKHR surface,
			uint32_t& graphicsQueueFamilyIndex,
			uint32_t& presentQueueFamilyIndex);
		static vk::Device createDevice(
			vk::PhysicalDevice physicalDevice,
			uint32_t graphicsQueueFamilyIndex,
			uint32_t presentQueueFamilyIndex);
		static VmaAllocator createMemoryAllocator(
			vk::Instance instance,
			vk::PhysicalDevice physicalDevice,
			vk::Device device);
		static vk::Fence createFence(
			vk::Device device,
			vk::FenceCreateFlags flags);
		static vk::Semaphore createSemaphore(
			vk::Device device,
			vk::SemaphoreCreateFlags flags);
		static vk::Queue getQueue(
			vk::Device device,
			uint32_t queueFamilyIndex,
			uint32_t queueIndex);
		static uint32_t getBestSurfaceImageCount(
			const vk::SurfaceCapabilitiesKHR& surfaceCapabilities);
		static vk::SurfaceFormatKHR getBestSurfaceFormat(
			vk::PhysicalDevice physicalDevice,
			vk::SurfaceKHR surface);
		static vk::PresentModeKHR getBestSurfacePresentMode(
			vk::PhysicalDevice physicalDevice,
			vk::SurfaceKHR surface);
		static vk::SurfaceTransformFlagBitsKHR getBestSurfaceTransform(
			const vk::SurfaceCapabilitiesKHR& surfaceCapabilities);
		static vk::CompositeAlphaFlagBitsKHR getBestSurfaceCompositeAlpha(
			const vk::SurfaceCapabilitiesKHR& surfaceCapabilities);
		static vk::Extent2D getBestSurfaceExtent(
			const vk::SurfaceCapabilitiesKHR& surfaceCapabilities,
			IntVector2 surfaceSize);
		static vk::SwapchainKHR createSwapchain(
			vk::Device device,
			vk::SurfaceKHR surface,
			uint32_t surfaceImageCount,
			vk::SurfaceFormatKHR surfaceFormat,
			vk::Extent2D surfaceExtent,
			vk::SurfaceTransformFlagBitsKHR surfaceTransform,
			vk::CompositeAlphaFlagBitsKHR surfaceCompositeAlpha,
			vk::PresentModeKHR surfacePresentMode);
		static vk::RenderPass createRenderPass(
			vk::Device device,
			vk::Format format);
		static vk::PipelineLayout createPipelineLayout(
			vk::Device device);
		static vk::Pipeline createPipeline(
			vk::Device device,
			vk::Extent2D extent,
			vk::RenderPass renderPass,
			vk::PipelineLayout pipelineLayout);
		static vk::CommandPool createCommandPool(
			vk::Device device,
			uint32_t queueFamilyIndex);
		static std::vector<VkSwapchainData> createSwapchainDatas(
			vk::Device device,
			vk::SwapchainKHR swapchain,
			vk::RenderPass renderPass,
			vk::CommandPool graphicsCommandPool,
			vk::CommandPool presentCommandPool,
			vk::Format surfaceFormat,
			vk::Extent2D surfaceExtent);
		static void destroySwapchainDatas(
			vk::Device device,
			vk::CommandPool graphicsCommandPool,
			vk::CommandPool presentCommandPool,
			const std::vector<VkSwapchainData>& swapchainDatas);
	public:
		VkWindow(const std::string& title = defaultTitle,
			IntVector2 position = defaultPosition,
			IntVector2 size = defaultSize,
			uint32_t flags = defaultFlags);
		virtual ~VkWindow();

		void onResize(IntVector2 size) override;

		uint32_t beginImage();
		void endImage(uint32_t imageIndex);

		void beginRecord(uint32_t imageIndex);
		void endRecord(uint32_t imageIndex);

		vk::CommandBuffer getGraphicsCommandBuffer(uint32_t imageIndex) const;
		vk::CommandBuffer getPresentCommandBuffer(uint32_t imageIndex) const;

		ShaderHandle createShader(ShaderStage stage, const std::string& path) override;
		MeshHandle createCubeMesh() override;
	};

	using VkWindowHandle = std::shared_ptr<VkWindow>;
}
