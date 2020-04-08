#pragma once
#define VULKAN_HPP_TYPESAFE_CONVERSION 1
#include <vulkan/vulkan.hpp>
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

	class VulkanShader : public Shader
	{
	protected:
		static vk::ShaderModule CreateInstance(const vk::Device& device, const std::vector<uint32_t>& shaderCode);
		static vk::ShaderModule CreateInstance(const vk::Device& device, const std::vector<uint8_t>& shaderCode);
		static vk::ShaderModule CreateInstance(const vk::Device& device, const std::string& binaryFilePath);
	public:
		static const std::string DefaultMainName;

		const vk::Device device;
		const vk::ShaderModule instance;

		VulkanShader(vk::Device device, const std::vector<uint32_t>& shaderCode, Type type);
		VulkanShader(vk::Device device, const std::vector<uint8_t>& shaderCode, Type type);
		VulkanShader(vk::Device device, const std::string& filePath, Type type);

		~VulkanShader();

		vk::PipelineShaderStageCreateInfo GetPipelineStageCreateInfo(vk::ShaderStageFlagBits stage, const std::string& name = DefaultMainName, const vk::SpecializationInfo* info = VK_NULL_HANDLE);
	};

	class Window
	{
	protected:
		GLFWwindow* instance;

		std::string title;
		glm::ivec2 size;
	public:
		static const std::string DefaultName;
		static const glm::ivec2 DefaultSize;

		Window(const std::function<void()>& setupWindow = {}, std::string title = DefaultName, glm::ivec2 size = DefaultSize, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
		~Window();

		GLFWwindow* GetInstance();

		const std::string& GetTitle();
		virtual void SetTitle(std::string value);

		const glm::ivec2& GetSize();
		virtual void SetSize(glm::ivec2 value);
		virtual void OnResize(glm::ivec2 value);

		virtual void OnDraw() = 0;
	};

	class VulkanWindow : public Window
	{
	protected:
		uint32_t graphicsQueueFamilyIndex;
		uint32_t presentQueueFamilyIndex;

		size_t frameCount;
		size_t currentFrame;

		vk::SurfaceKHR surface;
		vk::PhysicalDevice physicalDevice;
		vk::Device device;
		vk::Queue graphicsQueue;
		vk::Queue presentQueue;
		vk::SwapchainKHR swapchain;
		vk::RenderPass renderPass;
		vk::PipelineLayout pipelineLayout;
		vk::Pipeline pipeline;
		vk::CommandPool commandPool;
		
		std::vector<vk::ImageView> imageViews;
		std::vector<vk::Framebuffer> framebuffers;
		std::vector<vk::CommandBuffer> commandBuffers;
		std::vector<vk::Semaphore> imageAvailableSemaphores;
		std::vector<vk::Semaphore> renderFinishedSemaphores;
		std::vector<vk::Fence> inFlightFences;
		std::vector<vk::Fence> imagesInFlight;
	
		static void SetupVulkanWindow();
	public:
		static const std::string DefaultVulkanName;
		static const vk::Extent2D DefaultVulkanExtent;
		static const std::vector<const char*> DefaultDeviceLayers;
		static const std::vector<const char*> DefaultDeviceExtensions;

		VulkanWindow(const std::vector<const char*>& deviceLayers = DefaultDeviceLayers, const std::vector<const char*>& deviceExtensions = DefaultDeviceExtensions, std::string title = DefaultVulkanName, glm::ivec2 size = DefaultSize, GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
		~VulkanWindow();

		void OnDraw() override;
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

		static bool CompareSystem(const std::shared_ptr<System>& a, const std::shared_ptr<System>& b);
	public:
		static const int MajorVersion;
		static const int MinorVersion;
		static const int PatchVersion;
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

	class Vulkan
	{
	private:
		static bool isInitialized;

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
		static vk::PhysicalDevice GetBestPhysicalDevice(const std::vector<vk::PhysicalDevice>& devices);
		static vk::SurfaceFormatKHR GetBestSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& formats);
		static vk::PresentModeKHR GetBestPresentMode(const std::vector<vk::PresentModeKHR>& presentModes);
		static vk::Extent2D GetBestSurfaceImageExtent(const vk::SurfaceCapabilitiesKHR& capabilities, const vk::Extent2D& customExtent = VulkanWindow::DefaultVulkanExtent);
		static uint32_t GetBestSurfaceImageCount(const vk::SurfaceCapabilitiesKHR& capabilities);
	};
}
