#include <injector_engine.hpp>

namespace Injector
{
	OpenGLWindow::OpenGLWindow(std::string title, glm::ivec2 size, GLFWmonitor* monitor, GLFWwindow* share) : Window(title, size)
	{
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

		instance = glfwCreateWindow(size.x, size.y, title.c_str(), monitor, share);

		if (!instance)
			throw std::runtime_error("Failed to create OpenGL window instance.");

		glfwMakeContextCurrent(instance);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			throw std::runtime_error("Failed to load OpenGL.");
	}

	void OpenGLWindow::OnFramebufferResize(glm::ivec2 size)
	{
		glViewport(0, 0, size.x, size.y);
	}
	void OpenGLWindow::OnDraw()
	{
		glfwMakeContextCurrent(instance);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw

		glfwSwapBuffers(instance);
	}
}
