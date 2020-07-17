#pragma once
#include <injector/manager.hpp>

#include <chrono>

namespace INJECTOR_NAMESPACE
{
	//constexpr bool isBigEndian = SDL_BYTEORDER == SDL_BIG_ENDIAN;

	enum class GraphicsAPI
	{
		Unknown,
		OpenGL,
		Vulkan,
	};

	class Engine final
	{
	public:
		using tick_t = std::chrono::steady_clock::time_point;

		static void initializeEngine();
		static void terminateEngine();
		static bool getInitializedEngine() noexcept;

		static void initializeVideo(GraphicsAPI graphicsAPI);
		static void terminateVideo();
		static bool getInitializedVideo() noexcept;
		static GraphicsAPI getGraphicsAPI() noexcept;

		static void startUpdateLoop();

		/*static std::chrono::steady_clock::time_point
			getUpdateStartTicks() noexcept
		{
			return updateStartTicks;
		}
		inline static const double getUpdateStartTime() noexcept
		{
			return std::chrono::duration_cast<std::chrono::duration<double>>(
				updateStartTicks.time_since_epoch()).count();
		}*/

		static tick_t getTickNow() noexcept;
		static double getTimeNow() noexcept;

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
