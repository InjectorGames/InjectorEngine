#include <injector_engine.hpp>

namespace Injector
{
	bool Engine::isInitialized = false;
	Engine::DebugLevelType Engine::debugLevel = Engine::DebugLevelType::Full;

	std::set<std::shared_ptr<System>> Engine::systems = {};
	std::set<std::shared_ptr<Window>> Engine::windows = {};

	const int Engine::MajorVersion = 0;
	const int Engine::MinorVersion = 1;
	const int Engine::PatchVersion = 0;
	const std::string Engine::Name = "Injector Engine";

	void Engine::ErrorCallback(int error, const char* description)
	{
		std::cerr << "Engine GLFW error: " << error << ", " << description << std::endl;
	}
	void Engine::WindowSizeCallback(GLFWwindow* window, int width, int height)
	{
		auto size = glm::ivec2(width, height);

		for (const auto& window : windows)
			window->OnResize(size);
	}

	bool Engine::CompareSystem(const std::shared_ptr<System>& a, const std::shared_ptr<System>& b)
	{
		return a->updateQueue < b->updateQueue;
	}

	bool Engine::IsInitialized()
	{
		return isInitialized;
	}
	void Engine::Initialize(DebugLevelType _debugLevel)
	{
		if(isInitialized)
			throw std::runtime_error("Failed to initialize engine: Engine is not terminated.");

		debugLevel = _debugLevel;

		if (_debugLevel <= DebugLevelType::Info)
			std::cout << "Injector Engine version: " << MajorVersion << "." << MinorVersion << "." << PatchVersion << std::endl;

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
	void Engine::BeginUpdate()
	{
		int endUpdate = 0;

		while (!endUpdate)
		{
			for (const auto& window : windows)
			{
				auto windowInstance = window->GetInstance();
				endUpdate |= glfwWindowShouldClose(windowInstance);

				for (const auto& system : systems)
					system->OnUpdate();

				window->OnDraw();
			}

			glfwPollEvents();
		}
	}
	void Engine::EndUpdate()
	{
		windows = {};
		systems = {};
	}

	Engine::DebugLevelType Engine::GetDebugLevel()
	{
		return debugLevel;
	}
	bool Engine::IsDebugEnabled()
	{
		return debugLevel != DebugLevelType::Off;
	}

	void Engine::AddSystem(std::shared_ptr<System> system)
	{
		if (!systems.emplace(system).second)
			throw std::runtime_error("Failed to add engine system.");
	}
	void Engine::RemoveSystem(const std::shared_ptr<System>& system)
	{
		if (!systems.erase(system))
			throw std::runtime_error("Failed to remove engine system.");
	}
	const std::set<std::shared_ptr<System>>& Engine::GetSystems()
	{
		return systems;
	}

	void Engine::AddWindow(std::shared_ptr<Window> window)
	{
		if (!windows.emplace(window).second)
			throw std::runtime_error("Failed to add engine window.");

		auto windowInstance = window->GetInstance();
		glfwSetWindowSizeCallback(windowInstance, WindowSizeCallback);
	}
	void Engine::RemoveWindow(const std::shared_ptr<Window>& window)
	{
		if (!windows.erase(window))
			throw std::runtime_error("Failed to remove engine window.");
	}
	const std::set<std::shared_ptr<Window>>& Engine::GetWindows()
	{
		return windows;
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
