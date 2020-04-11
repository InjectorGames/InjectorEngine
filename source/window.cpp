#include <injector_engine.hpp>

namespace Injector
{
	Window::Window(std::string _title, glm::ivec2 _size)
	{
		instance = nullptr;
		title = _title;
		windowSize = _size;
		framebufferSize = glm::ivec2(0);
	}
	Window::~Window()
	{
		if (instance)
		{
			glfwDestroyWindow(instance);
			instance = nullptr;
		}
	}

	GLFWwindow* Window::GetInstance() const
	{
		return instance;
	}

	const std::string& Window::GetTitle() const
	{
		return title;
	}
	void Window::SetTitle(std::string _title)
	{
		title = _title;
		glfwSetWindowTitle(instance, _title.c_str());
	}

	const glm::ivec2& Window::GetWindowSize() const
	{
		return windowSize;
	}
	void Window::SetWindowSize(glm::ivec2 size)
	{
		windowSize = size;
		glfwSetWindowSize(instance, size.x, size.y);
	}
	void Window::OnWindowResize(glm::ivec2 size)
	{
		windowSize = size;
	}

	const glm::ivec2& Window::GetFramebufferSize() const
	{
		return framebufferSize;
	}
	void Window::OnFramebufferResize(glm::ivec2 size)
	{
		framebufferSize = size;
	}
}