#pragma once
#include <inject/window.hpp>
#include <SDL.h>
#include <SDL_vulkan.h>

#include <map>
#include <chrono>
#include <thread>

namespace INJECT_NAMESPACE
{
	constexpr bool isBigEndian = SDL_BYTEORDER == SDL_BIG_ENDIAN;

	class Engine final
	{
	private:
		inline static bool isInitialized = false;
		inline static bool isVulkan = false;
		inline static std::chrono::steady_clock::time_point updateStartTicks = {};
		inline static std::map<uint32_t, std::shared_ptr<Manager>> managers = {};
	public:
		inline static uint64_t targetUpdateRate = 60;
		inline static bool handleEvents = true;
		inline static bool capUpdateRate = true;

		inline static void initialize(
			const uint32_t flags = SDL_INIT_EVERYTHING,
			const bool useVulkan = true)
		{
			if (isInitialized)
				throw std::runtime_error("Engine is already initialized");

			if (SDL_Init(static_cast<Uint32>(flags)) == -1)
				throw std::runtime_error("Failed to intialize SDL. Error: " +
					std::string(SDL_GetError()));

			if (useVulkan)
			{
				if (SDL_Vulkan_LoadLibrary(nullptr) == -1)
				{
					SDL_Quit();

					throw std::runtime_error("Failed to load Vulkan library. Error: " +
						std::string(SDL_GetError()));
				}

				//SDL_Vulkan

				isVulkan = true;
			}
			else
			{
				isVulkan = false;
			}

			logInfo("Initialized engine. (v%d.%d.%d)",
				INJECT_VERSION_MAJOR, INJECT_VERSION_MINOR, INJECT_VERSION_PATCH);
			isInitialized = true;
		}
		inline static void terminate()
		{
			if (!isInitialized)
				throw std::runtime_error("Engine is not initialized");

			managers.clear();

			if (isVulkan)
				SDL_Vulkan_UnloadLibrary();

			SDL_Quit();

			logInfo("Terminated engine.");
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

		inline static const bool getIsInitialized() noexcept
		{
			return isInitialized;
		}
		inline static const bool getIsVulkan() noexcept
		{
			return isVulkan;
		}
		inline static const std::chrono::steady_clock::time_point
			getUpdateStartTicks() noexcept
		{
			return updateStartTicks;
		}
		inline static const double getUpdateStartTime() noexcept
		{
			return std::chrono::duration_cast<std::chrono::duration<double>>(
				updateStartTicks.time_since_epoch()).count();
		}

		inline static const std::chrono::steady_clock::time_point getTicksNow() noexcept
		{
			return std::chrono::high_resolution_clock::now();
		}
		inline static const double getTimeNow() noexcept
		{
			return std::chrono::duration_cast<std::chrono::duration<double>>(
				std::chrono::high_resolution_clock::now().time_since_epoch()).count();
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
