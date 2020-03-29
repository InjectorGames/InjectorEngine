#pragma once
#include <window.hpp>
#include <stdexcept>

namespace Injector
{
	class VulkanWindow : public Window
	{
	protected:
		VkInstance vulkanInstance;

		void SetWindowHints() override;
	public:
		VulkanWindow(int width = 800, int height = 600, const std::string& title = "Injector Engine - Editor (Vulkan)", GLFWmonitor* monitor = nullptr, GLFWwindow* share = nullptr);
		~VulkanWindow();

		void BeginUpdate() override;
	};
}
