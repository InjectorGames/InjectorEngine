#pragma once
#include <inject/window.hpp>

#include <SDL.h>

namespace inject
{
	class Engine final
	{
	private:
		inline static bool isInitialized = false;
		inline static bool capUpdateRate = true;
		inline static uint32_t targetUpdateRate = 60;
		inline static uint32_t updateRateDelay = 1000 / targetUpdateRate;
		inline static std::map<uint32_t, std::shared_ptr<Window>> windows = {};
	public:
		inline static bool getIsInitialized() noexcept
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
				"Initialized engine (v%d.%d.%d)",
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
				"Terminated engine");

			isInitialized = false;
		}

		inline static void update()
		{
			bool quit = false;
			SDL_Event event = {};
			uint64_t lastTicks = 0;

			auto frequency = static_cast<uint64_t>(SDL_GetPerformanceFrequency());
			auto milliFrequence = static_cast<uint64_t>(frequency / 1000);

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
				auto deltaTicks = static_cast<uint64_t>(newTicks - lastTicks);
				auto deltaTime = static_cast<float>(deltaTicks / float(frequency));
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

				if (capUpdateRate)
				{
					newTicks = static_cast<uint64_t>(SDL_GetPerformanceCounter());
					deltaTicks = static_cast<uint64_t>(newTicks - lastTicks);
					auto delay = static_cast<int32_t>(updateRateDelay - deltaTicks / milliFrequence) - 1;

					if (delay > 0)
						SDL_Delay(static_cast<Uint32>(delay));
				}
			}
		}

		inline static uint32_t getTargetUpdateRate()
		{
			return targetUpdateRate;
		}
		inline static uint32_t getUpdateRateDelay()
		{
			return updateRateDelay;
		}
		inline static void setTargetUpdateRate(const uint32_t frameRate)
		{
			targetUpdateRate = frameRate;
			updateRateDelay = 1000 / frameRate;
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
