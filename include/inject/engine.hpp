#pragma once
#include <inject/window.hpp>

#include <SDL.h>
#include <SDL_net.h>

namespace inject
{
	class Engine final
	{
	private:
		inline static bool isInitialized = false;
		inline static std::map<uint32_t, std::shared_ptr<Window>> windows = {};
	public:
		inline static bool initialized() noexcept
		{
			return isInitialized;
		}
		inline static void initialize(uint32_t flags = SDL_INIT_EVERYTHING)
		{
			if (isInitialized)
				throw std::runtime_error("Engine is already initialized");

			if (SDL_Init(static_cast<Uint32>(flags)) == -1)
				throw std::runtime_error("Failed to intialize SDL. Error: " + std::string(SDL_GetError()));

			SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
				"Initialized Inject Engine (v%d.%d.%d)",
				INJECT_VERSION_MAJOR, INJECT_VERSION_MINOR, INJECT_VERSION_PATCH);

			isInitialized = true;
		}
		inline static void terminate()
		{
			if (!isInitialized)
				throw std::runtime_error("Engine is not initialized");

			windows.clear();

			SDL_Quit();

			SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION,
				"Terminated Inject Engine");

			isInitialized = false;
		}

		inline static void initializeNet()
		{
			if(!isInitialized)
				throw std::runtime_error("Engine is not initialized");
			if(SDLNet_Init() == -1)
				throw std::runtime_error("Failed to intialize SDL Net. Error: " + std::string(SDLNet_GetError()));
		}
		inline static void terminateNet()
		{
			SDLNet_Quit();
		}

		inline static void update()
		{
			bool quit = false;
			SDL_Event event = {};
			uint64_t lastTicks = 0;

			auto frequency = static_cast<float>(SDL_GetPerformanceFrequency());

			while (!quit)
			{
				while (SDL_PollEvent(&event) != 0)
				{
					for (const auto& pair : windows)
					{
						const auto& window = pair.second;
						window->handleEvent(event);
					}
				}

				auto newTicks = static_cast<uint64_t>(SDL_GetPerformanceCounter());
				auto deltaTicks = newTicks - lastTicks;
				auto deltaTime = deltaTicks / frequency;
				lastTicks = newTicks;

				for (const auto& pair : windows)
				{
					const auto& window = pair.second;
					window->update(deltaTime);
				}

				auto allWindowsClosed = true;
				for (const auto& pair : windows)
				{
					const auto& window = pair.second;
					if (window->isShown())
					{
						allWindowsClosed = false;
						break;
					}
				}

				if (allWindowsClosed)
					quit = true;
			}
		}

		inline static void addWindow(const std::shared_ptr<Window> window)
		{
			if (!windows.emplace(window->getId(), window).second)
				throw std::exception("Failed to add level");
		}
		inline static void removeWindow(const uint32_t id)
		{
			if (windows.erase(id) == 0)
				throw std::exception("Failed to remove level");
		}
		inline static void removeWindows() noexcept
		{
			windows.clear();
		}
	};
}
