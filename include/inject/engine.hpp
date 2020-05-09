#pragma once
#include <inject/window.hpp>

#include <SDL.h>

namespace inject
{
	class Engine final
	{
	private:
		inline static bool initialized = false;
		inline static std::map<uint32_t, std::shared_ptr<Window>> windows = {};

		inline static void initializeSDL(uint32_t flags)
		{
			if (SDL_Init(static_cast<Uint32>(flags)) == -1)
				throw std::runtime_error("Failed to intialize SDL. Error: " + std::string(SDL_GetError()));
		}
		inline static void terminateSDL()
		{
			SDL_Quit();
		}
	public:
		inline static bool isInitialized() noexcept
		{
			return initialized;
		}
		inline static void initialize(uint32_t flags = SDL_INIT_EVERYTHING)
		{
			if (initialized)
				throw std::runtime_error("Engine is already initialized");

			initializeSDL(flags);

			initialized = true;
		}
		inline static void terminate()
		{
			if (!initialized)
				throw std::runtime_error("Engine is not initialized");

			windows.clear();

			terminateSDL();

			initialized = false;
		}

		inline static void update()
		{
			bool quit = false;
			SDL_Event event = {};
			uint64_t newTicks = 0;
			uint64_t lastTicks = 0;
			uint64_t deltaTicks = 0;
			double deltaTime = 0.0f;

			auto frequency = static_cast<double>(SDL_GetPerformanceFrequency());

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

				newTicks = static_cast<uint64_t>(SDL_GetPerformanceCounter());
				deltaTicks = newTicks - lastTicks;
				lastTicks = newTicks;

				deltaTime = deltaTicks / frequency;

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
