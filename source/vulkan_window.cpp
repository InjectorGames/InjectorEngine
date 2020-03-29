#include <vulkan_window.hpp>

namespace Injector
{
	void VulkanWindow::SetWindowHints()
	{
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	}

	VulkanWindow::VulkanWindow(int width, int height, const std::string& title, GLFWmonitor* monitor, GLFWwindow* share) : Window(width, height, title, monitor, share)
	{
		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "Injector Engine - Editor";
		appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
		appInfo.pEngineName = "Injector Engine";
		appInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;

		uint32_t glfwExtensionCount = 0;
		auto glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

		createInfo.enabledExtensionCount = glfwExtensionCount;
		createInfo.ppEnabledExtensionNames = glfwExtensions;

		if(vkCreateInstance(&createInfo, nullptr, &vulkanInstance) != VK_SUCCESS)
			throw std::runtime_error("Failed to create vulkan instance.");
	}
	VulkanWindow::~VulkanWindow()
	{
		vkDestroyInstance(vulkanInstance, nullptr);
	}

	void VulkanWindow::BeginUpdate()
	{
		while (!glfwWindowShouldClose(instance))
		{
			glfwPollEvents();
		}
	}
}