#include <engine.hpp>

namespace Injector
{
	bool Engine::initialized = false;

	void Engine::ErrorCallback(int error, const char* description)
	{
		std::cerr << "GLFW Error: " << error << ", " << description << std::endl;
	}

	void Engine::Initialize()
	{
		if(initialized)
			throw std::runtime_error("Failed to initialize injector engine: Not terminated.");

		glfwSetErrorCallback(ErrorCallback);

		if (!glfwInit())
			throw std::runtime_error("Failed to intialize GLFW.");

		initialized = true;
	}
	void Engine::Terminate()
	{
		if(!initialized)
			throw std::runtime_error("Failed to terminate injector engine: Not initialized.");

		glfwTerminate();
		initialized = false;
	}

	bool Engine::Initialized()
	{
		return initialized;
	}
}
