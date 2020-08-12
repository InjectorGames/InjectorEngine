#pragma once
#include <injector/manager.hpp>
#include <injector/graphics/graphics_api.hpp>

#include <chrono>

namespace INJECTOR_NAMESPACE
{
	class Engine final
	{
	public:
		using tick_t = std::chrono::steady_clock::time_point;
	private:
		static bool engineInitialized;
		static bool videoInitialized;
		static bool eventsInitialized;

		static GraphicsAPI graphicsAPI;

		static bool capUpdateRate;
		static int targetUpdateRate;

		static bool updateRunning;
		static tick_t updateStartTick;
		static double updateDeltaTime;

		static std::vector<ManagerHandle> managers;
	public:
		static bool getCapUpdateRate() noexcept;
		static void setCapUpdateRate(bool cap = true) noexcept;

		static int getTargetUpdateRate() noexcept;
		static void setTargetUpdateRate(int ups = 60) noexcept;

		static tick_t getUpdateStartTick() noexcept;
		static double getUpdateDeltaTime() noexcept;

		static void initializeEngine();
		static void terminateEngine();
		static bool getEngineInitialized() noexcept;

		static void initializeVideo(GraphicsAPI graphicsAPI = GraphicsAPI::OpenGL);
		static void terminateVideo();
		static bool getVideoInitialized() noexcept;
		static GraphicsAPI getGraphicsAPI() noexcept;

		static void initializeEvents();
		static void terminateEvents();
		static bool getEventsInitialized() noexcept;

		static void startUpdateLoop();
		static void stopUpdateLoop();
		static bool getUpdateRunning() noexcept;

		static tick_t getTickNow() noexcept;
		static double getTimeNow() noexcept;

		static bool addManager(const ManagerHandle& manager) noexcept;
		static bool removeManager(const ManagerHandle& manager) noexcept;
		static bool containsManager(const ManagerHandle& manager) noexcept;
		static void removeManagers() noexcept;
		static size_t getManagerCount() noexcept;

		template<class T, class ...Args>
		static std::shared_ptr<T> createManager(Args... args) noexcept
		{
			auto manager = std::make_shared<T>(args...);
			managers.push_back(manager);
			return manager;
		}
	};
}
