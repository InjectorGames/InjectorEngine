#pragma once
#include "Injector/Defines.hpp"
#include "Injector/ECS/EcsManager.hpp"
#include "Injector/Mathematics/Matrix4.hpp"
#include "Injector/Graphics/GraphicsAPI.hpp"

#include <chrono>

namespace Injector
{
	class Engine final
	{
	 private:
		static bool engineInitialized;
		static bool networkInitialized;
		static bool graphicsInitialized;
		static bool virtualRealityInitialized;

		static bool updateRunning;
		static bool capUpdateRate;
		static int targetUpdateRate;

		static std::chrono::steady_clock::
			time_point updateStartTick;
		static double updateStartTime;
		static double updateDeltaTime;

		static GraphicsAPI graphicsAPI;
		static FloatMatrix4 hmdModelMatrix;
		static FloatMatrix4 leftEyeModelMatrix;
		static FloatMatrix4 rightEyeModelMatrix;
		static FloatMatrix4 leftEyeProjMatrix;
		static FloatMatrix4 rightEyeProjMatrix;

		static std::vector<std::shared_ptr<EcsManager>> managers;
	 public:
		static bool getCapUpdateRate() noexcept;
		static void setCapUpdateRate(bool cap = true) noexcept;

		static int getTargetUpdateRate() noexcept;
		static void setTargetUpdateRate(int ups = 60) noexcept;

		static std::chrono::steady_clock::
			time_point getUpdateStartTick() noexcept;
		static double getUpdateStartTime() noexcept;
		static double getUpdateDeltaTime() noexcept;

		static void initializeEngine(
			int majorVersion = INJECTOR_VERSION_MAJOR,
			int minorVersion = INJECTOR_VERSION_MINOR,
			int patchVersion = INJECTOR_VERSION_PATCH);
		static void terminateEngine();
		static bool isEngineInitialized() noexcept;

		static void initializeNetwork();
		static void terminateNetwork();
		static bool isNetworkInitialized();

		static void glfwErrorCallback(
			int error,
			const char* description);
		static void initializeGraphics(
			GraphicsAPI graphicsAPI = GraphicsAPI::OpenGL);
		static void terminateGraphics();
		static bool isGraphicsInitialized() noexcept;

		static void initializeVirtualReality();
		static void terminateVirtualReality();
		static bool isVirtualRealityInitialized() noexcept;

		static void startUpdateLoop();
		static void stopUpdateLoop() noexcept;
		static bool getUpdateRunning() noexcept;

		static std::chrono::steady_clock::
			time_point getTickNow() noexcept;
		static double getTimeNow() noexcept;

		static GraphicsAPI getGraphicsAPI() noexcept;
		static const FloatMatrix4& getHmdModelMatrix() noexcept;
		static const FloatMatrix4& getLeftEyeModelMatrix() noexcept;
		static const FloatMatrix4& getRightEyeModelMatrix() noexcept;
		static const FloatMatrix4& getLeftEyeProjMatrix() noexcept;
		static const FloatMatrix4& getRightEyeProjMatrix() noexcept;

		static bool addManager(
			const std::shared_ptr<EcsManager>& manager) noexcept;
		static bool removeManager(
			const std::shared_ptr<EcsManager>& manager) noexcept;
		static bool containsManager(
			const std::shared_ptr<EcsManager>& manager) noexcept;
		static void removeManagers() noexcept;
		static size_t getManagerCount() noexcept;

		template<class T = EcsManager, class ...Args>
		static std::shared_ptr<T> createManager(Args... args) noexcept
		{
			auto manager = std::make_shared<T>(args...);
			managers.push_back(manager);
			return manager;
		}
	};
}
