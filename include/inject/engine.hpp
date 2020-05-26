#pragma once
#include <inject/config.hpp>
#include <inject/manager.hpp>

#include <SDL.h>
#include <map>

namespace inject
{
	constexpr bool isBigEndian = SDL_BYTEORDER == SDL_BIG_ENDIAN;

	class Engine final
	{
	private:
		inline static bool isInitialized = false;
		inline static uint64_t ticksFrequency = 0;
		inline static uint64_t targetUpdateRate = 0;
		inline static uint64_t updateTicksRate = 0;
		inline static uint64_t updateStartTicks = 0;
		inline static std::map<uint32_t, std::shared_ptr<Manager>> managers = {};
	public:
		inline static bool handleEvents = true;
		inline static bool capUpdateRate = true;

		inline static const bool getIsInitialized() noexcept
		{
			return isInitialized;
		}
		inline static void initialize(uint32_t flags = SDL_INIT_EVERYTHING)
		{
			if (isInitialized)
				throw std::runtime_error("Engine is already initialized");

			if (SDL_Init(static_cast<Uint32>(flags)) == -1)
				throw std::runtime_error("Failed to intialize SDL. Error: " + std::string(SDL_GetError()));

			ticksFrequency = static_cast<uint64_t>(SDL_GetPerformanceFrequency());
			setTargetUpdateRate(60);

			logInfo("Initialized engine (v%d.%d.%d)",
				INJECT_VERSION_MAJOR, INJECT_VERSION_MINOR, INJECT_VERSION_PATCH);
			isInitialized = true;
		}
		inline static void terminate()
		{
			if (!isInitialized)
				throw std::runtime_error("Engine is not initialized");

			managers.clear();

			SDL_Quit();

			logInfo("Terminated engine");
			isInitialized = false;
		}

		inline static void update()
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
							const auto& manager = pair.second;
							manager->handleEvent(event);
						}
					}
				}

				auto newTicks = getElapsedTicks();
				auto deltaTicks = newTicks - updateStartTicks;
				auto deltaTime = static_cast<double>(deltaTicks / double(ticksFrequency));
				updateStartTicks = newTicks;

				for (const auto& pair : managers)
				{
					const auto& manager = pair.second;
					manager->update(deltaTime);
				}

				auto allNotActive = true;
				for (const auto& pair : managers)
				{
					const auto& window = pair.second;
					if (window->getActive())
					{
						allNotActive = false;
						break;
					}
				}

				if (allNotActive)
					quit = true;

				if (capUpdateRate)
				{
					newTicks = getElapsedTicks();;
					deltaTicks = newTicks - updateStartTicks;
					auto delayTime = static_cast<int32_t>((updateTicksRate - deltaTicks) / (ticksFrequency / 1000)) - 1;

					if (delayTime > 0)
						delay(delayTime);
				}
			}
		}

		inline static const uint64_t getTicksFrequency() noexcept
		{
			return ticksFrequency;
		}
		inline static const uint64_t getTargetUpdateRate() noexcept
		{
			return targetUpdateRate;
		}

		inline static const uint64_t getUpdateTicksRate() noexcept
		{
			return updateTicksRate;
		}
		inline static const double getUpdateTimeRate() noexcept
		{
			return updateTicksRate / double(ticksFrequency);
		}

		inline static const uint64_t getUpdateStartTicks() noexcept
		{
			return updateStartTicks;
		}
		inline static const double getUpdateStartTime() noexcept
		{
			return updateStartTicks / double(ticksFrequency);
		}

		inline static void setTargetUpdateRate(const uint32_t frameRate)
		{
			targetUpdateRate = frameRate;
			updateTicksRate = ticksFrequency / frameRate;
		}

		inline static const uint64_t getElapsedTicks() noexcept
		{
			return static_cast<uint64_t>(SDL_GetPerformanceCounter());
		}
		inline static const double getElapsedTime() noexcept
		{
			return static_cast<double>(SDL_GetPerformanceCounter() / double(ticksFrequency));
		}

		inline static void delay(uint32_t milliseconds) noexcept
		{
			SDL_Delay(static_cast<Uint32>(milliseconds));
		}

		inline static void addManager(const std::shared_ptr<Manager> manager)
		{
			if (!managers.emplace(manager->getID(), manager).second)
				throw std::exception("Failed to add engine manager");
		}
		inline static void removeManager(const uint32_t id)
		{
			if (managers.erase(id) == 0)
				throw std::exception("Failed to remove engine manager");
		}
		inline static void removeManagers() noexcept
		{
			managers.clear();
		}

		template<class... Args>
		inline static void log(const std::string& fmt, Args... args) noexcept
		{
			SDL_Log(fmt.c_str(), args...);
		}
		template<class... Args>
		inline static void logVerbose(const std::string& fmt, Args... args) noexcept
		{
			SDL_LogVerbose(SDL_LOG_CATEGORY_APPLICATION, fmt.c_str(), args...);
		}
		template<class... Args>
		inline static void logDebug(const std::string& fmt, Args... args) noexcept
		{
			SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, fmt.c_str(), args...);
		}
		template<class... Args>
		inline static void logInfo(const std::string& fmt, Args... args) noexcept
		{
			SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, fmt.c_str(), args...);
		}
		template<class... Args>
		inline static void logWarning(const std::string& fmt, Args... args) noexcept
		{
			SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, fmt.c_str(), args...);
		}
		template<class... Args>
		inline static void logError(const std::string& fmt, Args... args) noexcept
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, fmt.c_str(), args...);
		}
		template<class... Args>
		inline static void logCritical(const std::string& fmt, Args... args) noexcept
		{
			SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, fmt.c_str(), args...);
		}
	};
}
