#include <injector_engine/engine.hpp>

namespace InjectorEngine
{
	bool Engine::isInitialized = false;
	Engine::DebugLevelType Engine::debugLevel = Engine::DebugLevelType::Full;
	std::set<Window*> Engine::windows = {};

	const std::string Engine::Name = "Injector Engine";

	void Engine::ErrorCallback(int error, const char* description)
	{
		std::cerr << "GLFW error: Code = " << error << ", Description = " << description << ".\n";
	}
	void Engine::WindowSizeCallback(GLFWwindow* window, int width, int height)
	{
		auto size = glm::ivec2(width, height);
		for (const auto& window : windows)
			window->OnWindowResize(size);
	}
	void Engine::FramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		auto size = glm::ivec2(width, height);
		for (const auto& window : windows)
			window->OnFramebufferResize(size);
	}

	bool Engine::IsInitialized()
	{
		return isInitialized;
	}
	void Engine::Initialize(DebugLevelType _debugLevel)
	{
		if (isInitialized)
			throw std::runtime_error("Failed to initialize engine: Engine is not terminated.");

		debugLevel = _debugLevel;

		std::cout << "Injector Engine version: " << INJECTOR_ENGINE_VERSION_MAJOR << "." << INJECTOR_ENGINE_VERSION_MINOR << "." << INJECTOR_ENGINE_VERSION_PATCH << std::endl;

		glfwSetErrorCallback(ErrorCallback);

		if (!glfwInit())
			throw std::runtime_error("Failed to intialize GLFW.");

		isInitialized = true;
	}
	void Engine::Terminate()
	{
		if(!isInitialized)
			throw std::runtime_error("Failed to terminate engine: Engine is not initialized.");

		glfwTerminate();
		isInitialized = false;
	}
	void Engine::Update()
	{
		for (const auto& window : windows)
			window->OnUpdateBegin();

		int endUpdate = 0;

		while (endUpdate != windows.size())
		{
			for (const auto& window : windows)
			{
				endUpdate += glfwWindowShouldClose(window->GetWindow());
				window->OnUpdate();
			}

			glfwPollEvents();
		}

		for (const auto& window : windows)
			window->OnUpdateEnd();
	}

	Engine::DebugLevelType Engine::GetDebugLevel()
	{
		return debugLevel;
	}
	bool Engine::IsDebugEnabled()
	{
		return debugLevel != DebugLevelType::Off;
	}

	void Engine::AddWindow(Window* window)
	{
		if (!windows.emplace(window).second)
			throw std::runtime_error("Failed to add engine window.");

		auto _window = window->GetWindow();
		glfwSetWindowSizeCallback(_window, WindowSizeCallback);
		glfwSetFramebufferSizeCallback(_window, FramebufferSizeCallback);
	}
	void Engine::RemoveWindow(Window* window)
	{
		if (!windows.erase(window))
			throw std::runtime_error("Failed to remove engine window.");
	}

	std::string Engine::ReadTextFromFile(const std::string& filePath)
	{
		std::ifstream ifs(filePath, std::ios::ate);

		if (!ifs)
			throw std::runtime_error("Failed to open text file.");

		size_t size = ifs.tellg();
		std::string buffer(size, ' ');

		ifs.seekg(0, std::ios::beg);
		ifs.read(&buffer[0], size);
		return buffer;
	}
	std::vector<uint8_t> Engine::ReadBytesFromFile(const std::string& filePath)
	{
		std::ifstream ifs(filePath, std::ios::ate | std::ios::binary);

		if (!ifs)
			throw std::runtime_error("Failed to open binary file.");

		auto pos = ifs.tellg();
		std::vector<uint8_t> buffer(pos);

		ifs.seekg(0, std::ios::beg);
		ifs.read((char*)&buffer[0], pos);
		return buffer;
	}
}
