#include <window.hpp>

namespace Injector
{
	void Window::SetWindowHints(){}

	Window::Window(int width, int height, const std::string& title, GLFWmonitor* monitor, GLFWwindow* share)
	{
		if(!Engine::Initialized())
			throw std::runtime_error("Failed to create GLFW window: Injector engine is not initialized.");

		SetWindowHints();

		instance = glfwCreateWindow(width, height, title.c_str(), monitor, share);

		if (!instance)
			throw std::runtime_error("Failed to create GLFW window instance.");
	}
	Window::~Window()
	{
		if (!Engine::Initialized())
			throw std::runtime_error("Failed to destroy GLFW window: Injector engine is not initialized.");

		glfwDestroyWindow(instance);
		instance = nullptr;
	}

	void Window::BeginUpdate()
	{
		while (!glfwWindowShouldClose(instance))
			glfwPollEvents();
	}
}