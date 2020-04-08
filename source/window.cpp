#include <injector_engine.hpp>

namespace Injector
{
	const std::string Window::DefaultName = "Injector Engine - Editor";
	const glm::ivec2 Window::DefaultSize = glm::ivec2(800, 600);

	Window::Window(const std::function<void()>& setupWindow, std::string _title, glm::ivec2 _size, GLFWmonitor* monitor, GLFWwindow* share)
	{
		if(!Engine::IsInitialized())
			throw std::runtime_error("Failed to create GLFW window: Engine is not initialized.");

		size = _size;
		title = _title;

		if(setupWindow)
			setupWindow();

		instance = glfwCreateWindow(_size.x, _size.y, _title.c_str(), monitor, share);

		if (!instance)
			throw std::runtime_error("Failed to create GLFW window instance.");
	}
	Window::~Window()
	{
		glfwDestroyWindow(instance);
	}

	GLFWwindow* Window::GetInstance()
	{
		return instance;
	}

	const std::string& Window::GetTitle()
	{
		return title;
	}
	void Window::SetTitle(std::string value)
	{
		title = value;
		glfwSetWindowTitle(instance, value.c_str());
	}

	const glm::ivec2& Window::GetSize()
	{
		return size;
	}
	void Window::SetSize(glm::ivec2 value)
	{
		size = value;
		glfwSetWindowSize(instance, value.x, value.y);
	}
	void Window::OnResize(glm::ivec2 value)
	{
		size = value;
	}
}