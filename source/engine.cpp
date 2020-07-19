#include <injector/engine.hpp>

#include <SDL.h>
#include <SDL_vulkan.h>

#include <thread>
#include <iostream>

namespace INJECTOR_NAMESPACE
{
	bool Engine::engineInitialized = false;
	bool Engine::videoInitialized = false;
	bool Engine::eventsInitialized = false;

	GraphicsAPI Engine::graphicsAPI = GraphicsAPI::Unknown;

	bool Engine::capUpdateRate = true;
	int Engine::targetUpdateRate = 60;

	bool Engine::updateRunning = false;
	Engine::tick_t Engine::updateStartTick = {};
	double Engine::updateDeltaTime = 0.0;
	size_t Engine::freeManagerID = 1;

	std::map<size_t, Manager*> Engine::managers = {};

	bool Engine::getCapUpdateRate() noexcept
	{
		return capUpdateRate;
	}
	void Engine::setCapUpdateRate(bool cap) noexcept
	{
		capUpdateRate = cap;
	}

	int Engine::getTargetUpdateRate() noexcept
	{
		return targetUpdateRate;
	}
	void Engine::setTargetUpdateRate(int ups) noexcept
	{
		targetUpdateRate = ups;
	}

	Engine::tick_t Engine::getUpdateStartTick() noexcept
	{
		return updateStartTick;
	}
	double Engine::getUpdateDeltaTime() noexcept
	{
		return updateDeltaTime;
	}

	size_t Engine::getFreeManagerID() noexcept
	{
		return freeManagerID;
	}

	void Engine::initializeEngine()
	{
		if (engineInitialized)
			throw std::runtime_error("Engine is already initialized");

		engineInitialized = true;

		std::cout << "Initialized engine (" <<
			INJECTOR_VERSION_MAJOR << "." <<
			INJECTOR_VERSION_MINOR << "." <<
			INJECTOR_VERSION_PATCH << ")\n";
	}
	void Engine::terminateEngine()
	{
		if (!engineInitialized)
			throw std::runtime_error("Engine is already terminated");

		destroyManagers();

		if (videoInitialized)
			terminateVideo();
		if (eventsInitialized)
			terminateEvents();

		SDL_Quit();
		
		engineInitialized = false;

		std::cout << "Terminated engine\n";
	}
	bool Engine::getEngineInitialized() noexcept
	{
		return engineInitialized;
	}

	void Engine::initializeVideo(GraphicsAPI api)
	{
		if (engineInitialized)
			throw std::runtime_error("Engine is already initialized");
		if (videoInitialized)
			throw std::runtime_error("Video subsystem is already initialized");

		if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0)
			throw std::runtime_error("Failed to intialize video subsystem. Error: " +
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
		videoInitialized = true;

		std::cout << "Initialized video subsytem\n";
	}
	void Engine::terminateVideo()
	{
		if (!engineInitialized)
			throw std::runtime_error("Engine is already terminated");
		if (!videoInitialized)
			throw std::runtime_error("Video subsystem is already terminated");

		if (graphicsAPI == GraphicsAPI::Vulkan)
			SDL_Vulkan_UnloadLibrary();

		SDL_QuitSubSystem(SDL_INIT_VIDEO);

		graphicsAPI = GraphicsAPI::Unknown;
		videoInitialized = false;

		std::cout << "Terminated video subsystem\n";
	}
	bool Engine::getVideoInitialized() noexcept
	{
		return videoInitialized;
	}
	GraphicsAPI Engine::getGraphicsAPI() noexcept
	{
		return graphicsAPI;
	}

	void Engine::initializeEvents()
	{
		if (engineInitialized)
			throw std::runtime_error("Engine is already initialized");
		if (eventsInitialized)
			throw std::runtime_error("Events subsystem is already initialized");

		if (SDL_InitSubSystem(SDL_INIT_EVENTS) != 0)
			throw std::runtime_error("Failed to intialize events subsystem. Error: " +
				std::string(SDL_GetError()));

		eventsInitialized = true;

		std::cout << "Initialized events subsytem\n";
	}
	void Engine::terminateEvents()
	{
		if (!engineInitialized)
			throw std::runtime_error("Engine is already terminated");
		if (!eventsInitialized)
			throw std::runtime_error("Events subsystem is already terminated");

		SDL_QuitSubSystem(SDL_INIT_EVENTS);
		eventsInitialized = false;

		std::cout << "Terminated events subsystem\n";
	}
	bool Engine::getEventsInitialized() noexcept
	{
		return eventsInitialized;
	}

	void Engine::startUpdateLoop()
	{
		if (updateRunning)
			throw std::runtime_error("Update is already started");

		updateRunning = true;

		while (updateRunning)
		{
			auto tick = std::chrono::high_resolution_clock::now();
			updateDeltaTime = std::chrono::duration_cast<
				std::chrono::duration<double>>(tick - updateStartTick).count();
			updateStartTick = tick;

			for (const auto& pair : managers)
				pair.second->update();

			if (capUpdateRate)
			{
				tick = std::chrono::high_resolution_clock::now();
				updateDeltaTime = std::chrono::duration_cast<
					std::chrono::duration<double>>(tick - updateStartTick).count();
				auto delayTime = (1.0 / targetUpdateRate - updateDeltaTime) * 1000 - 1.0;

				if (delayTime > 0)
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(
						static_cast<uint64_t>(delayTime)));
				}
			}
		}
	}
	void Engine::stopUpdateLoop()
	{
		if (!updateRunning)
			throw std::runtime_error("Update is already stopped");

		updateRunning = false;
	}
	bool Engine::getUpdateRunning() noexcept
	{
		return updateRunning;
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

	size_t Engine::getManagerCount() noexcept
	{
		return managers.size();
	}
	bool Engine::destroyManager(size_t id) noexcept
	{
		if (id == 0)
			return false;

		auto iterator = managers.find(id);

		if (iterator == managers.end())
			return false;

		delete iterator->second;
		managers.erase(iterator);
		return true;
	}
	void Engine::destroyManagers() noexcept
	{
		for (const auto& pair : managers)
			delete pair.second;

		managers.clear();
	}
	
}
