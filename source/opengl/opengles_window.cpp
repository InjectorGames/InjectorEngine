#include <injector_engine.hpp>

namespace Injector
{
	OpenGLESWindow::OpenGLESWindow(std::string title, glm::ivec2 size, GLFWmonitor* monitor, GLFWwindow* share) : Window(title, size)
	{
		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

		instance = glfwCreateWindow(size.x, size.y, title.c_str(), monitor, share);

		if (!instance)
			throw std::runtime_error("Failed to create OpenGL ES window instance.");

		glfwMakeContextCurrent(instance);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			throw std::runtime_error("Failed to load OpenGL ES loader.");
	}

	void OpenGLESWindow::OnFramebufferResize(glm::ivec2 size)
	{
		glViewport(0, 0, size.x, size.y);
	}
	void OpenGLESWindow::OnDraw()
	{
		glfwMakeContextCurrent(instance);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw

		glfwSwapBuffers(instance);
	}
}
