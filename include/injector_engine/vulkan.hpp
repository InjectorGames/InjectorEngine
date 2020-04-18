#pragma once
#include <injector_engine/engine.hpp>

#ifdef VULKAN_FOUND
namespace InjectorEngine
{
	class VkShader
	{
	protected:
		vk::Device device;
		vk::ShaderModule instance;
	public:
		static const std::string DefaultMainName;

		VkShader(vk::Device device, const std::vector<uint32_t>& shaderCode);
		VkShader(vk::Device device, const std::vector<uint8_t>& shaderCode);
		VkShader(vk::Device device, const std::string& filePath);

		~VkShader();

		vk::Device GetDevice() const;
		vk::ShaderModule GetInstance() const;

		vk::PipelineShaderStageCreateInfo CreatePipelineStageCreateInfo(vk::ShaderStageFlagBits stage, const std::string& name = DefaultMainName, const vk::SpecializationInfo* info = VK_NULL_HANDLE) const;
	};

	class VkWindow : public Window
	{
	protected:
		vk::PhysicalDevice physicalDevice;
		vk::SurfaceKHR surface;
		uint32_t graphicsQueueIndex;
		uint32_t presentQueueIndex;
		bool separatePresentQueue;
		vk::Device device;
		vk::Queue graphicsQueue;
		vk::Queue presentQueue;
		size_t frameLag;
		size_t currentFrame;
		std::vector<vk::Fence> fences;
		std::vector<vk::Semaphore> imageAcquiredSemaphores;
		std::vector<vk::Semaphore> drawCompleteSemaphores;
		std::vector<vk::Semaphore> imageOwnershipSemaphores;

		vk::CommandPool graphicsCommandPool;
		vk::CommandPool presentCommandPool;

		vk::SwapchainKHR swapchain;
		vk::RenderPass renderPass;
		vk::PipelineLayout pipelineLayout;
		vk::Pipeline pipeline;

		std::vector<vk::ImageView> imageViews;
		std::vector<vk::Framebuffer> framebuffers;
		std::vector<vk::CommandBuffer> commandBuffers;

		//void CleanupSwapchain();
		//void RecreateSwapchain();
	public:
		static const std::vector<const char*> DefaultDeviceLayers;
		static const std::vector<const char*> DefaultDeviceExtensions;
		static const size_t DefaultFrameLag;

		VkWindow(const std::vector<const char*>& deviceLayers = DefaultDeviceLayers, const std::vector<const char*>& deviceExtensions = DefaultDeviceExtensions, size_t frameLag = DefaultFrameLag, std::string title = "Injector Engine - Editor (Vulkan)", glm::ivec2 size = glm::ivec2(800, 600), GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
		~VkWindow();

		//void OnFramebufferResize(glm::ivec2 value) override;
	};

	class Vulkan
	{
	private:
		static bool isInitialized;

		static uint32_t apiVersion;
		static uint32_t apiMajorVersion;
		static uint32_t apiMinorVersion;

		static vk::Instance instance;
		static vk::DebugUtilsMessengerEXT debugMessenger;
	public:
		static const std::string DefaultAppName;
		static const uint32_t DefaultAppVersion;
		static const std::vector<const char*> DefaultInstanceLayers;

		static std::string VersionToString(uint32_t version);

		static bool IsInitialized();
		static void Initialize(const std::string& appName = DefaultAppName, uint32_t appVersion = DefaultAppVersion, const std::vector<const char*>& instanceLayers = DefaultInstanceLayers);
		static void Terminate();

		static vk::Instance GetInstance();
		static vk::DebugUtilsMessengerEXT GetDebugMessenger();

		static std::vector<const char*> GetGlfwRequiredExtensions();

		static vk::PhysicalDevice GetBestPhysicalDevice(const std::vector<vk::PhysicalDevice>& physicalDevices);
		static vk::PhysicalDevice GetBestPhysicalDevice();

		static vk::SurfaceFormatKHR GetBestSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& surfaceFormats);
		static vk::SurfaceFormatKHR GetBestSurfaceFormat(vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface);

		static vk::PresentModeKHR GetBestPresentMode(const std::vector<vk::PresentModeKHR>& presentModes);
		static vk::PresentModeKHR GetBestPresentMode(vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface);

		static vk::Extent2D GetBestSurfaceImageExtent(const vk::SurfaceCapabilitiesKHR& capabilities, GLFWwindow* window);
		static vk::Extent2D GetBestSurfaceImageExtent(vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface, GLFWwindow* window);

		static uint32_t GetBestSurfaceImageCount(const vk::SurfaceCapabilitiesKHR& capabilities);
		static uint32_t GetBestSurfaceImageCount(vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface);

		static void GetSurfaceQueueFamilyIndices(vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface, uint32_t& graphicsQueueIndex, uint32_t& presentQueueIndex);

		static vk::SurfaceKHR CreateSurface(GLFWwindow* window, const VkAllocationCallbacks* allocator = nullptr);
		static void DestroySurface(vk::SurfaceKHR surface);

		static vk::Device CreateSurfaceDevice(vk::PhysicalDevice physicalDevice, uint32_t graphicsQueueIndex, uint32_t presentQueueIndex, const std::vector<const char*>& deviceLayers, const std::vector<const char*>& deviceExtensions, const std::vector<vk::PhysicalDeviceFeatures>& features);

		static std::vector<vk::Fence> CreateFences(vk::Device device, size_t count, vk::FenceCreateFlags flags = {});
		static void DestroyFences(vk::Device device, const std::vector<vk::Fence>& fences);

		static std::vector<vk::Semaphore> CreateSemaphores(vk::Device device, size_t count, vk::SemaphoreCreateFlags flags = {});
		static void DestroySemaphores(vk::Device device, const std::vector<vk::Semaphore>& semaphores);
	};
}
#endif // VULKAN_FOUND
