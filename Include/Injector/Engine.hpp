#pragma once
#include "Injector/Manager.hpp"
#include "Injector/Graphics/GraphicsApi.hpp"

#include <chrono>

namespace Injector
{
	class Engine final
	{
	 public:
		using tick_t = std::chrono::steady_clock::time_point;
	 private:
		static bool engineInitialized;
		static bool videoInitialized;

		static GraphicsApi graphicsApi;

		static bool capUpdateRate;
		static int targetUpdateRate;

		static bool updateRunning;
		static tick_t updateStartTick;
		static double updateDeltaTime;

		static std::vector<std::shared_ptr<Manager>> managers;
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

		static void videoErrorCallback(
			int error, const char* description);
		static void initializeVideo(
			GraphicsApi graphicsApi = GraphicsApi::OpenGL);
		static void terminateVideo();
		static bool getVideoInitialized() noexcept;
		static GraphicsApi getGraphicsApi() noexcept;

		static void startUpdateLoop();
		static void stopUpdateLoop();
		static bool getUpdateRunning() noexcept;

		static tick_t getTickNow() noexcept;
		static double getTimeNow() noexcept;

		static bool addManager(
			const std::shared_ptr<Manager>& manager) noexcept;
		static bool removeManager(
			const std::shared_ptr<Manager>& manager) noexcept;
		static bool containsManager(
			const std::shared_ptr<Manager>& manager) noexcept;
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
