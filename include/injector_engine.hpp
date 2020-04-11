#pragma once
#include <injector_engine_config.hpp>

#ifdef GLAD_DEBUG
#include <glad/glad_debug.h>
#else
#include <glad/glad_release.h>
#endif // GLAD_DEBUG

#ifdef VULKAN_FOUND
#define VULKAN_HPP_TYPESAFE_CONVERSION 1
#include <vulkan/vulkan.hpp>
#endif // VULKAN_FOUND

#include <GLFW/glfw3.h>
#include <entt/entt.hpp>
#include <glm/glm.hpp>

#include <set>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <functional>

namespace Injector
{
	class System
	{
	public:
		const int updateQueue;
		System(int updateQueue);

		virtual void OnUpdate() = 0;
	};

	class Shader
	{
	public:
		enum class Type
		{
			Vertex,
			TessellationControl,
			TessellationEvaluation,
			Geometry,
			Fragment,
			Compute,

			Raygen,
			AnyHit,
			ClosestHit,
			Miss,
			Intersection,
			Callable,
		};

		const Type type;
		Shader(Type type);
	};

	class Window
	{
	protected:
		GLFWwindow* instance;

		std::string title;
		glm::ivec2 windowSize;
		glm::ivec2 framebufferSize;
	public:
		Window(std::string title = "Injector Engine - Editor", glm::ivec2 size = glm::ivec2(800, 600));
		~Window();

		GLFWwindow* GetInstance() const;

		const std::string& GetTitle() const;
		virtual void SetTitle(std::string title);

		const glm::ivec2& GetWindowSize() const;
		virtual void SetWindowSize(glm::ivec2 size);
		virtual void OnWindowResize(glm::ivec2 size);

		const glm::ivec2& GetFramebufferSize() const;
		virtual void OnFramebufferResize(glm::ivec2 size);

		virtual void OnDraw() = 0;
	};

	class Engine final
	{
	public:
		enum class DebugLevelType
		{
			Full,
			Trace,
			Info,
			Warn,
			Error,
			Fatal,
			Off,
		};
	private:
		static bool isInitialized;
		static DebugLevelType debugLevel;

		static std::set<std::shared_ptr<System>> systems;
		static std::set<std::shared_ptr<Window>> windows;

		static void ErrorCallback(int error, const char* description);
		static void WindowSizeCallback(GLFWwindow* window, int width, int height);
		static void FramebufferSizeCallback(GLFWwindow* window, int width, int height);

		static bool CompareSystem(const std::shared_ptr<System>& a, const std::shared_ptr<System>& b);
	public:
		static const std::string Name;

		static bool IsInitialized();
		static void Initialize(DebugLevelType debugLevel = DebugLevelType::Warn);
		static void Terminate();
		static void BeginUpdate();
		static void EndUpdate();

		static DebugLevelType GetDebugLevel();
		static bool IsDebugEnabled();

		static void AddSystem(std::shared_ptr<System> system);
		static void RemoveSystem(const std::shared_ptr<System>& system);
		static const std::set<std::shared_ptr<System>>& GetSystems();

		static void AddWindow(std::shared_ptr<Window> window);
		static void RemoveWindow(const std::shared_ptr<Window>& window);
		static const std::set<std::shared_ptr<Window>>& GetWindows();

		static std::string ReadTextFromFile(const std::string& filePath);
		static std::vector<uint8_t> ReadBytesFromFile(const std::string& filePath);
	};

	class OpenGLWindow : public Window
	{
	protected:
		static GLFWwindow* CreateWindowInstance(const glm::ivec2& size, const std::string& title, GLFWmonitor* monitor, GLFWwindow* share);
	public:
		static const std::string DefaultOpenGLName;

		OpenGLWindow(std::string title = "Injector Engine - Editor (OpenGL)", glm::ivec2 size = glm::ivec2(800, 600), GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);

		void OnFramebufferResize(glm::ivec2 size) override;
		void OnDraw() override;
	};

#ifdef VULKAN_FOUND
	class VulkanShader : public Shader
	{
	protected:
		vk::Device device;
		vk::ShaderModule instance;
	public:
		static const std::string DefaultMainName;

		VulkanShader(vk::Device device, const std::vector<uint32_t>& shaderCode, Type type);
		VulkanShader(vk::Device device, const std::vector<uint8_t>& shaderCode, Type type);
		VulkanShader(vk::Device device, const std::string& filePath, Type type);

		~VulkanShader();

		vk::Device GetDevice() const;
		vk::ShaderModule GetInstance() const;

		vk::PipelineShaderStageCreateInfo CreatePipelineStageCreateInfo(vk::ShaderStageFlagBits stage, const std::string& name = DefaultMainName, const vk::SpecializationInfo* info = VK_NULL_HANDLE) const;
	};

	class VulkanWindow : public Window
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

		VulkanWindow(const std::vector<const char*>& deviceLayers = DefaultDeviceLayers, const std::vector<const char*>& deviceExtensions = DefaultDeviceExtensions, size_t frameLag = DefaultFrameLag, std::string title = "Injector Engine - Editor (Vulkan)", glm::ivec2 size = glm::ivec2(800, 600), GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
		~VulkanWindow();

		//void OnFramebufferResize(glm::ivec2 value) override;

		void OnDraw() override;
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
#endif // VULKAN_FOUND
}
