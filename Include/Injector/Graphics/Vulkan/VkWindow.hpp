#pragma once
#define GLFW_INCLUDE_VULKAN

#include "Injector/Graphics/Window.hpp"
#include "Injector/Graphics/Vulkan/VkGpuBuffer.hpp"
#include "Injector/Graphics/Vulkan/VkSwapchainData.hpp"
#include "Injector/Graphics/Vulkan/VkGpuPipeline.hpp"

#include <set>

namespace Injector
{
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
		vk::CommandPool transferCommandPool;
		vk::Extent2D surfaceExtent;
		vk::SwapchainKHR swapchain;
		vk::RenderPass renderPass;
		uint32_t frameIndex;
		std::vector<std::shared_ptr<VkSwapchainData>> swapchainDatas;
		std::set<std::shared_ptr<VkGpuPipeline>> pipelines;

		static VkBool32 VKAPI_CALL debugMessengerCallback(
			VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
			VkDebugUtilsMessageTypeFlagsEXT messageTypes,
			const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData,
			void* pUserData);

		static GLFWwindow* createWindow(
			const std::string& title,
			const IntVector2& size);
		static vk::Instance createInstance(
			const std::string& appName,
			uint32_t appVersion);
		static vk::DebugUtilsMessengerEXT createDebugMessenger(
			vk::Instance instance,
			const vk::DispatchLoaderDynamic& dispatchDynamic);
		static vk::PhysicalDevice getBestPhysicalDevice(
			vk::Instance instance);
		static vk::SurfaceKHR createSurface(
			vk::Instance instance,
			GLFWwindow* window);
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
		static vk::CommandPool createCommandPool(
			vk::Device device,
			vk::CommandPoolCreateFlags flags,
			uint32_t queueFamilyIndex);
	 public:
		explicit VkWindow(
			const std::string& title = defaultTitle,
			const IntVector2& size = defaultSize);
		~VkWindow() override;

		vk::CommandBuffer getGraphicsCommandBuffer(
			uint32_t imageIndex) const;
		vk::CommandBuffer getPresentCommandBuffer(
			uint32_t imageIndex) const;

		void onFramebufferResize(
			const IntVector2& size) override;

		uint32_t beginImage();
		void endImage(uint32_t imageIndex);

		void beginRecord(uint32_t imageIndex);
		void endRecord(uint32_t imageIndex);

		std::shared_ptr<CameraSystem> createCameraSystem() override;
		std::shared_ptr<RenderSystem> createRenderSystem() override;

		std::shared_ptr<GpuBuffer> createBuffer(
			size_t size,
			GpuBufferType type,
			bool mappable,
			const void* data) override;
		std::shared_ptr<GpuMesh> createMesh(
			size_t indexCount,
			GpuBufferIndex indexType,
			const std::shared_ptr<GpuBuffer>& vertexBuffer,
			const std::shared_ptr<GpuBuffer>& indexBuffer) override;
		std::shared_ptr<ShaderData> readShaderData(
			const std::string& filePath) override;
		std::shared_ptr<GpuShader> createShader(
			GpuShaderStage stage,
			const std::shared_ptr<ShaderData>& data) override;
		std::shared_ptr<GpuImage> createImage(
			GpuImageType type,
			const IntVector3& size,
			GpuImageFormat format,
			GpuImageFilter minFilter,
			GpuImageFilter magFilter,
			GpuImageWrap wrapU,
			GpuImageWrap wrapV,
			GpuImageWrap wrapW,
			bool useMipmap,
			const std::shared_ptr<ImageData>& data) override;
		std::shared_ptr<GpuFramebuffer> createFramebuffer(
			const std::shared_ptr<GpuImage>& colorImage,
			const std::shared_ptr<GpuImage>& depthImage,
			const std::shared_ptr<GpuImage>& stencilImage) override;

		std::shared_ptr<ColorGpuPipeline> createColorPipeline(
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader) override;
		std::shared_ptr<ColorGpuPipeline> createColColorPipeline(
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader) override;
		std::shared_ptr<DiffuseGpuPipeline> createDiffusePipeline(
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader) override;
		std::shared_ptr<TextureDiffuseGpuPipeline> createTexDiffusePipeline(
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader,
			const std::shared_ptr<GpuImage>& texture) override;
		std::shared_ptr<SimulatedSkyGpuPipeline> createSkyPipeline(
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader) override;
	};
}
