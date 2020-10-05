#pragma once
#include "Injector/Defines.hpp"
#include "Injector/Manager.hpp"
#include "Injector/Mathematics/Matrix4.hpp"
#include "Injector/Graphics/GraphicsAPI.hpp"

#include <chrono>

namespace Injector
{
	class Engine final
	{
	 private:
		static bool engineInitialized;
		static bool videoInitialized;
		static bool vrInitialized;

		static bool updateRunning;
		static bool capUpdateRate;
		static int targetUpdateRate;

		static std::chrono::steady_clock::
			time_point updateStartTick;
		static double updateStartTime;
		static double updateDeltaTime;

		static GraphicsAPI graphicsApi;
		static Matrix4 hmdModelMatrix;
		static Matrix4 leftEyeModelMatrix;
		static Matrix4 rightEyeModelMatrix;
		static Matrix4 leftEyeProjMatrix;
		static Matrix4 rightEyeProjMatrix;

		static std::vector<std::shared_ptr<Manager>> managers;
	 public:
		static bool getCapUpdateRate() noexcept;
		static void setCapUpdateRate(bool cap = true) noexcept;

		static int getTargetUpdateRate() noexcept;
		static void setTargetUpdateRate(int ups = 60) noexcept;

		static std::chrono::steady_clock::
			time_point getUpdateStartTick() noexcept;
		static double getUpdateStartTime() noexcept;
		static double getUpdateDeltaTime() noexcept;

		static void initializeEngine();
		static void terminateEngine();
		static bool getEngineInitialized() noexcept;

		static void videoErrorCallback(
			int error, const char* description);
		static void initializeVideo(
			GraphicsAPI graphicsApi = GraphicsAPI::OpenGL);
		static void terminateVideo();
		static bool getVideoInitialized() noexcept;

		static void initializeVr();
		static void terminateVr();
		static bool getVrInitialized() noexcept;

		static void startUpdateLoop();
		static void stopUpdateLoop();
		static bool getUpdateRunning() noexcept;

		static std::chrono::steady_clock::
			time_point getTickNow() noexcept;
		static double getTimeNow() noexcept;

		static GraphicsAPI getGraphicsApi() noexcept;
		static const Matrix4& getHmdModelMatrix() noexcept;
		static const Matrix4& getLeftEyeModelMatrix() noexcept;
		static const Matrix4& getRightEyeModelMatrix() noexcept;
		static const Matrix4& getLeftEyeProjMatrix() noexcept;
		static const Matrix4& getRightEyeProjMatrix() noexcept;

		static bool addManager(
			const std::shared_ptr<Manager>& manager) noexcept;
		static bool removeManager(
			const std::shared_ptr<Manager>& manager) noexcept;
		static bool containsManager(
			const std::shared_ptr<Manager>& manager) noexcept;
		static void removeManagers() noexcept;
		static size_t getManagerCount() noexcept;

		template<class T = Manager, class ...Args>
		static std::shared_ptr<T> createManager(Args... args) noexcept
		{
			auto manager = std::make_shared<T>(args...);
			managers.push_back(manager);
			return manager;
		}
	};
}
