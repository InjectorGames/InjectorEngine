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
		static size_t freeManagerID;

		static std::map<size_t, Manager*> managers;
	public:
		static bool getCapUpdateRate() noexcept;
		static void setCapUpdateRate(bool cap = true) noexcept;

		static int getTargetUpdateRate() noexcept;
		static void setTargetUpdateRate(int ups = 60) noexcept;

		static tick_t getUpdateStartTick() noexcept;
		static double getUpdateDeltaTime() noexcept;

		static size_t getFreeManagerID() noexcept;

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

		static size_t getManagerCount() noexcept;
		static bool destroyManager(size_t id) noexcept;
		static void destroyManagers() noexcept;

		template<class T>
		static T* createManager()
		{
			if (freeManagerID == SIZE_MAX)
			{
				// TODO: reorder map
			}

			auto manager = new T(freeManagerID);

			if (!managers.emplace(freeManagerID, manager).second)
			{
				delete manager;
				throw std::exception("Failed to add engine manager");
			}
			
			freeManagerID++;
			return manager;
		}
		template<class T>
		static bool createManager(T*& manager) noexcept
		{
			if (freeManagerID == SIZE_MAX)
			{
				// TODO: reorder map
			}

			manager = new T(freeManagerID);

			if (!managers.emplace(freeManagerID, manager).second)
			{
				delete manager;
				return false;
			}

			freeManagerID++;
			return true;
		}

		template<class T>
		static T* getManager(size_t id)
		{
			if (id == 0)
				throw std::runtime_error("Manager id is null");

			return dynamic_cast<T>(managers.at(id));
		}
		template<class T>
		static bool getManager(size_t id, T*& manager) noexcept
		{
			if (id == 0)
				return false;

			auto iterator = managers.find(id);

			if (iterator == managers.end())
				return false;

			manager = dynamic_cast<T>(iterator->second);
			return true;
		}
	};
}
