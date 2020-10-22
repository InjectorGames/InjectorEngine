#pragma once
#define GLFW_INCLUDE_VULKAN

#include "Injector/Graphics/Window.hpp"
#include "Injector/Graphics/Vulkan/VkGpuBuffer.hpp"
#include "Injector/Graphics/Vulkan/VkGpuSwapchain.hpp"

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
		vk::Queue graphicsQueue;
		vk::Queue presentQueue;
		vk::CommandPool graphicsCommandPool;
		vk::CommandPool presentCommandPool;
		vk::CommandPool transferCommandPool;
		VkGpuSwapchain swapchain;
		std::vector<vk::Fence> fences;
		std::vector<vk::Semaphore> imageAcquiredSemaphores;
		std::vector<vk::Semaphore> drawCompleteSemaphores;
		std::vector<vk::Semaphore> imageOwnershipSemaphores;
		std::set<std::shared_ptr<VkGpuPipeline>> pipelines;
		uint32_t frameIndex;

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
		static vk::Queue getQueue(
			vk::Device device,
			uint32_t queueFamilyIndex,
			uint32_t queueIndex);
		static vk::CommandPool createCommandPool(
			vk::Device device,
			const vk::CommandPoolCreateFlags& flags,
			uint32_t queueFamilyIndex);
		static vk::Fence createFence(
			vk::Device device,
			const vk::FenceCreateFlags& flags);
		static vk::Semaphore createSemaphore(
			vk::Device device,
			const vk::SemaphoreCreateFlags& flags);
	 public:
		explicit VkWindow(
			const std::string& title = defaultTitle,
			const IntVector2& size = defaultSize);
		~VkWindow() override;

		void onFramebufferResize(
			const IntVector2& size) override;

		vk::CommandBuffer getGraphicsCommandBuffer(
			uint32_t imageIndex) const;

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
			const std::shared_ptr<GpuBuffer>& vertexBuffer,
			const std::shared_ptr<GpuBuffer>& indexBuffer) override;
		std::shared_ptr<ShaderData> readShaderData(
			const std::string& filePath) override;
		std::shared_ptr<GpuShader> createShader(
			GpuShaderStage stage,
			const std::shared_ptr<ShaderData>& data) override;
		std::shared_ptr<GpuImage> createImage(
			GpuImageType type,
			GpuImageFormat format,
			const IntVector3& size,
			bool useMipmap,
			const std::shared_ptr<ImageData>& data) override;
		std::shared_ptr<GpuFramebuffer> createFramebuffer(
			const std::shared_ptr<GpuImage>& colorImage,
			const std::shared_ptr<GpuImage>& depthImage,
			const std::shared_ptr<GpuImage>& stencilImage) override;

		std::shared_ptr<GpuPipeline> createColorPipeline(
			GpuDrawMode drawMode,
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader,
			const Vector4& color) override;
		std::shared_ptr<GpuPipeline> createColorColorPipeline(
			GpuDrawMode drawMode,
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader,
			const Vector4& color) override;
		std::shared_ptr<GpuPipeline> createDiffusePipeline(
			GpuDrawMode drawMode,
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader,
			const Vector4& objectColor,
			const Vector4& ambientColor,
			const Vector4& lightColor,
			const Vector3& lightDirection) override;
		std::shared_ptr<GpuPipeline> createImageDiffusePipeline(
			GpuDrawMode drawMode,
			GpuImageFilter imageMinFilter,
			GpuImageFilter imageMagFilter,
			GpuImageFilter mipmapFilter,
			GpuImageWrap imageWrapU,
			GpuImageWrap imageWrapV,
			GpuImageWrap imageWrapW,
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader,
			const std::shared_ptr<GpuImage>& image,
			const Vector4& objectColor,
			const Vector4& ambientColor,
			const Vector4& lightColor,
			const Vector3& lightDirection,
			const Vector2& imageScale,
			const Vector2& imageOffset) override;
		std::shared_ptr<GpuPipeline> createSkyPipeline(
			GpuDrawMode drawMode,
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader) override;
	};
}
