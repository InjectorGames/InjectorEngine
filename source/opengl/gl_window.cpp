#include <injector_engine/opengl.hpp>

namespace InjectorEngine
{
	GlWindow::GlWindow(bool _isES, std::string _title, glm::ivec2 _size, GLFWmonitor* monitor, GLFWwindow* share) : Window(_title + (_isES ? " (OpenGL ES)" : " (OpenGL)"), _size)
	{
		if (_isES)
		{
			window = nullptr;
		}
		else
		{
			glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

			window = glfwCreateWindow(size.x, size.y, title.c_str(), monitor, share);
		}
		
		if (!window)
		{
			glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

			window = glfwCreateWindow(size.x, size.y, title.c_str(), monitor, share);

			if (!window)
				throw std::runtime_error("Failed to create OpenGL/ES window.");

			_isES = true;
		}

		isES = _isES;

		glfwMakeContextCurrent(window);
		glbinding::initialize(glfwGetProcAddress);
	}

	bool GlWindow::IsES() const
	{
		return isES;
	}

	void GlWindow::OnFramebufferResize(glm::ivec2 size)
	{
		gl::glViewport(0, 0, size.x, size.y);
	}
}
