#include <injector/engine.hpp>

#include <SDL.h>
#include <SDL_vulkan.h>

#include <map>
#include <thread>

namespace INJECTOR_NAMESPACE
{
	static bool initializedEngine = false;
	static bool initializedVideo = false;

	static GraphicsAPI graphicsAPI = GraphicsAPI::Unknown;

	static uint64_t targetUPS = 60;
	static bool handleEvents = true;
	static bool capUpdateRate = true;

	static std::map<size_t, Manager*> managers = {};
	static std::chrono::steady_clock::time_point updateStartTicks = {};

	void Engine::initializeEngine()
	{
		if (initializedEngine)
			throw std::runtime_error("Engine is already initialized");

		initializedEngine = true;

		logInfo("Initialized engine (v%d.%d.%d)",
			INJECTOR_VERSION_MAJOR, INJECTOR_VERSION_MINOR, INJECTOR_VERSION_PATCH);
	}
	void Engine::terminateEngine()
	{
		if (!initializedEngine)
			throw std::runtime_error("Engine is already terminated");

		managers.clear();
		SDL_Quit();
		
		initializedEngine = false;

		logInfo("Terminated engine");
	}
	bool Engine::getInitializedEngine() noexcept
	{
		return initializedEngine;
	}

	void Engine::initializeVideo(GraphicsAPI api)
	{
		if (initializedEngine)
			throw std::runtime_error("Engine is already initialized");
		if (initializedVideo)
			throw std::runtime_error("Video subsystem is already initialized");

		if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0)
			throw std::runtime_error("Failed to intialize Video subsystem. Error: " +
				std::string(SDL_GetError()));

		if (api == GraphicsAPI::Vulkan)
		{
			if (SDL_Vulkan_LoadLibrary(nullptr) != 0)
			{
				SDL_QuitSubSystem(SDL_INIT_VIDEO);
				throw std::runtime_error("Failed to load Vulkan library. Error: " +
					std::string(SDL_GetError()));
			}
		}
		
		graphicsAPI = api;
		initializedVideo = true;

		logInfo("Initialized Video subsytem");
	}
	void Engine::terminateVideo()
	{
		if (!initializedEngine)
			throw std::runtime_error("Engine is already terminated");
		if (!initializedVideo)
			throw std::runtime_error("Video subsystem is already terminated");

		if (graphicsAPI == GraphicsAPI::Vulkan)
			SDL_Vulkan_UnloadLibrary();

		SDL_QuitSubSystem(SDL_INIT_VIDEO);

		graphicsAPI = GraphicsAPI::Unknown;
		initializedVideo = false;

		logInfo("Terminated Video subsystem");
	}
	bool Engine::getInitializedVideo() noexcept
	{
		return initializedVideo;
	}
	GraphicsAPI Engine::getGraphicsAPI() noexcept
	{
		return graphicsAPI;
	}

	void Engine::startUpdateLoop()
	{
		bool quit = false;
		SDL_Event event = {};

		while (!quit)
		{
			if (handleEvents)
			{
				while (SDL_PollEvent(&event) != 0)
				{
					for (const auto& pair : managers)
					{
						const auto window = std::dynamic_pointer_cast<Window>(pair.second);

						if (window)
							window->handleEvent(event);
					}
				}
			}

			auto ticks = std::chrono::high_resolution_clock::now();
			auto deltaTime = std::chrono::duration_cast<
				std::chrono::duration<double>>(ticks - updateStartTicks).count();
			updateStartTicks = ticks;

			for (const auto& pair : managers)
			{
				const auto& manager = pair.second;
				manager->update(deltaTime);
			}

			auto allNotActive = true;
			for (const auto& pair : managers)
			{
				const auto& manager = pair.second;
				if (manager->getActive())
				{
					allNotActive = false;
					break;
				}
			}

			if (allNotActive)
				quit = true;

			if (capUpdateRate)
			{
				ticks = std::chrono::high_resolution_clock::now();
				deltaTime = std::chrono::duration_cast<
					std::chrono::duration<double>>(ticks - updateStartTicks).count();
				const auto delayTime = (1.0 / targetUpdateRate - deltaTime) * 1000 - 1.0;

				if (delayTime > 0)
					std::this_thread::sleep_for(
						std::chrono::milliseconds(static_cast<uint64_t>(delayTime)));
			}
		}
	}

	Engine::tick_t Engine::getTickNow() noexcept
	{
		return std::chrono::high_resolution_clock::now();
	}
	double Engine::getTimeNow() noexcept
	{
		return std::chrono::duration_cast<std::chrono::duration<double>>(
			std::chrono::high_resolution_clock::now().time_since_epoch()).count();
	}
}
