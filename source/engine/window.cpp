#include <injector_engine/engine.hpp>

namespace InjectorEngine
{
	Window::Window(std::string _title, glm::ivec2 _size)
	{
		title = _title;
		size = _size;

		window = nullptr;
		framebufferSize = glm::ivec2(0);
		systems = {};
		//registry = {};
	}
	Window::~Window()
	{
		if (window)
		{
			glfwDestroyWindow(window);
			window = nullptr;
		}
	}
	 
	GLFWwindow* Window::GetWindow() const
	{
		return window;
	}
	//entt::registry& Window::GetRegistry()
	//{
	//	return registry;
	//}

	const std::string& Window::GetTitle() const
	{
		return title;
	}
	void Window::SetTitle(std::string _title)
	{
		glfwSetWindowTitle(window, _title.c_str());
		title = _title;
	}

	const glm::ivec2& Window::GetSize() const
	{
		return size;
	}
	void Window::SetSize(glm::ivec2 _size)
	{
		glfwSetWindowSize(window, _size.x, _size.y);
		size = _size;
	}
	void Window::OnWindowResize(glm::ivec2 _size)
	{
		size = _size;
	}

	const glm::ivec2& Window::GetFramebufferSize() const
	{
		return framebufferSize;
	}
	void Window::OnFramebufferResize(glm::ivec2 size)
	{
		framebufferSize = size;
	}

	void Window::AddSystem(System* system)
	{
		if (!systems.emplace(system).second)
			throw std::runtime_error("Failed to add window system.");
	}
	void Window::RemoveSystem(System* system)
	{
		if (!systems.erase(system))
			throw std::runtime_error("Failed to remove window system.");
	}

	void Window::OnUpdateBegin()
	{
		for (const auto& system : systems)
			system->OnUpdateBegin(this);
	}
	void Window::OnUpdate()
	{
		for (const auto& system : systems)
			system->OnUpdate(this);
	}
	void Window::OnUpdateEnd()
	{
		for (const auto& system : systems)
			system->OnUpdateEnd(this);
	}
}