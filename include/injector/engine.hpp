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
		OpenGLES,
		Vulkan,
	};

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

		static float toDegrees(float value);
		static double toDegrees(double value);
		static float toRadians(float value);
		static double toRadians(double value);

		static uint16_t swapEndian(uint16_t value) noexcept;
		static int16_t swapEndian(int16_t value) noexcept;
		static uint32_t swapEndian(uint32_t value) noexcept;
		static int32_t swapEndian(int32_t value) noexcept;
		static uint64_t swapEndian(uint64_t value) noexcept;
		static int64_t swapEndian(int64_t value) noexcept;
		static float swapEndian(float value) noexcept;
		static double swapEndian(double value) noexcept;

		static uint16_t swapBigEndian(uint16_t value) noexcept;
		static int16_t swapBigEndian(int16_t value) noexcept;
		static uint32_t swapBigEndian(uint32_t value) noexcept;
		static int32_t swapBigEndian(int32_t value) noexcept;
		static uint64_t swapBigEndian(uint64_t value) noexcept;
		static int64_t swapBigEndian(int64_t value) noexcept;
		static float swapBigEndian(float value) noexcept;
		static double swapBigEndian(double value) noexcept;

		static uint16_t swapLittleEndian(uint16_t value) noexcept;
		static int16_t swapLittleEndian(int16_t value) noexcept;
		static uint32_t swapLittleEndian(uint32_t value) noexcept;
		static int32_t swapLittleEndian(int32_t value) noexcept;
		static uint64_t swapLittleEndian(uint64_t value) noexcept;
		static int64_t swapLittleEndian(int64_t value) noexcept;
		static float swapLittleEndian(float value) noexcept;
		static double swapLittleEndian(double value) noexcept;
	};
}
