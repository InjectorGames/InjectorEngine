#include <injector/engine.hpp>

#include <thread>
#include <cstdlib>
#include <iostream>

#include <SDL.h>
#include <SDL_vulkan.h>

#if defined(_MSC_VER) && ( !defined(__clang__) || defined(__c2__) )

#define BYTE_SWAP_16(x) _byteswap_ushort(x)
#define BYTE_SWAP_32(x) _byteswap_ulong(x)
#define BYTE_SWAP_64(x) _byteswap_uint64(x)

#elif (defined(__clang__) && __has_builtin(__builtin_bswap32) && __has_builtin(__builtin_bswap64)) \
	|| (defined(__GNUC__ ) && (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3)))

#if (defined(__clang__) && __has_builtin(__builtin_bswap16)) \
	|| (defined(__GNUC__) &&(__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 8)))
#define BYTE_SWAP_16(x) __builtin_bswap16(x)
#else
#define BYTE_SWAP_16(x) __builtin_bswap32((x) << 16)
#endif

#define BYTE_SWAP_32(x) __builtin_bswap32(x)
#define BYTE_SWAP_64(x) __builtin_bswap64(x)

#elif defined(__linux__)

#include <byteswap.h>
#define BYTE_SWAP_16(x) bswap_16(x)
#define BYTE_SWAP_32(x) bswap_32(x)
#define BYTE_SWAP_64(x) bswap_64(x)

#endif

namespace INJECTOR_NAMESPACE
{
	bool Engine::engineInitialized = false;
	bool Engine::videoInitialized = false;
	bool Engine::eventsInitialized = false;

	GraphicsAPI Engine::graphicsAPI = GraphicsAPI::Unknown;

	bool Engine::capUpdateRate = true;
	int Engine::targetUpdateRate = 60;

	bool Engine::updateRunning = false;
	Engine::tick_t Engine::updateStartTick = {};
	double Engine::updateDeltaTime = 0.0;

	std::vector<ManagerHandle> Engine::managers = {};

	bool Engine::getCapUpdateRate() noexcept
	{
		return capUpdateRate;
	}
	void Engine::setCapUpdateRate(bool cap) noexcept
	{
		capUpdateRate = cap;
	}

	int Engine::getTargetUpdateRate() noexcept
	{
		return targetUpdateRate;
	}
	void Engine::setTargetUpdateRate(int ups) noexcept
	{
		targetUpdateRate = ups;
	}

	Engine::tick_t Engine::getUpdateStartTick() noexcept
	{
		return updateStartTick;
	}
	double Engine::getUpdateDeltaTime() noexcept
	{
		return updateDeltaTime;
	}

	void Engine::initializeEngine()
	{
		if (engineInitialized)
			throw std::runtime_error("Engine is already initialized");

		engineInitialized = true;

		std::cout << "Initialized engine (" <<
			INJECTOR_VERSION_MAJOR << "." <<
			INJECTOR_VERSION_MINOR << "." <<
			INJECTOR_VERSION_PATCH << ")\n";
	}
	void Engine::terminateEngine()
	{
		if (!engineInitialized)
			throw std::runtime_error("Engine is already terminated");

		managers.clear();

		if (videoInitialized)
			terminateVideo();
		if (eventsInitialized)
			terminateEvents();

		SDL_Quit();
		
		engineInitialized = false;

		std::cout << "Terminated engine\n";
	}
	bool Engine::getEngineInitialized() noexcept
	{
		return engineInitialized;
	}

	void Engine::initializeVideo(GraphicsAPI api)
	{
		if (engineInitialized)
			throw std::runtime_error("Engine is already initialized");
		if (videoInitialized)
			throw std::runtime_error("Video subsystem is already initialized");

		if (SDL_InitSubSystem(SDL_INIT_VIDEO) != 0)
			throw std::runtime_error("Failed to intialize video subsystem. Error: " +
				std::string(SDL_GetError()));

		if (api == GraphicsAPI::Vulkan)
		{
			if (SDL_Vulkan_LoadLibrary(nullptr) != 0)
			{
				SDL_QuitSubSystem(SDL_INIT_VIDEO);
				throw std::runtime_error("Failed to load Vulkan library. Error: " +
					std::string(SDL_GetError()));
			}
		}
		
		graphicsAPI = api;
		videoInitialized = true;

		std::cout << "Initialized video subsytem\n";
	}
	void Engine::terminateVideo()
	{
		if (!engineInitialized)
			throw std::runtime_error("Engine is already terminated");
		if (!videoInitialized)
			throw std::runtime_error("Video subsystem is already terminated");

		if (graphicsAPI == GraphicsAPI::Vulkan)
			SDL_Vulkan_UnloadLibrary();

		SDL_QuitSubSystem(SDL_INIT_VIDEO);

		graphicsAPI = GraphicsAPI::Unknown;
		videoInitialized = false;

		std::cout << "Terminated video subsystem\n";
	}
	bool Engine::getVideoInitialized() noexcept
	{
		return videoInitialized;
	}
	GraphicsAPI Engine::getGraphicsAPI() noexcept
	{
		return graphicsAPI;
	}

	void Engine::initializeEvents()
	{
		if (engineInitialized)
			throw std::runtime_error("Engine is already initialized");
		if (eventsInitialized)
			throw std::runtime_error("Events subsystem is already initialized");

		if (SDL_InitSubSystem(SDL_INIT_EVENTS) != 0)
			throw std::runtime_error("Failed to intialize events subsystem. Error: " +
				std::string(SDL_GetError()));

		eventsInitialized = true;

		std::cout << "Initialized events subsytem\n";
	}
	void Engine::terminateEvents()
	{
		if (!engineInitialized)
			throw std::runtime_error("Engine is already terminated");
		if (!eventsInitialized)
			throw std::runtime_error("Events subsystem is already terminated");

		SDL_QuitSubSystem(SDL_INIT_EVENTS);
		eventsInitialized = false;

		std::cout << "Terminated events subsystem\n";
	}
	bool Engine::getEventsInitialized() noexcept
	{
		return eventsInitialized;
	}

	void Engine::startUpdateLoop()
	{
		if (updateRunning)
			throw std::runtime_error("Update is already started");

		updateRunning = true;

		while (updateRunning)
		{
			auto tick = std::chrono::high_resolution_clock::now();
			updateDeltaTime = std::chrono::duration_cast<
				std::chrono::duration<double>>(tick - updateStartTick).count();
			updateStartTick = tick;

			for (auto& manager : managers)
				manager->update();

			if (capUpdateRate)
			{
				tick = std::chrono::high_resolution_clock::now();
				updateDeltaTime = std::chrono::duration_cast<
					std::chrono::duration<double>>(tick - updateStartTick).count();
				auto delayTime = (1.0 / targetUpdateRate - updateDeltaTime) * 1000 - 1.0;

				if (delayTime > 0)
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(
						static_cast<uint64_t>(delayTime)));
				}
			}
		}
	}
	void Engine::stopUpdateLoop()
	{
		if (!updateRunning)
			throw std::runtime_error("Update is already stopped");

		updateRunning = false;
	}
	bool Engine::getUpdateRunning() noexcept
	{
		return updateRunning;
	}

	Engine::tick_t Engine::getTickNow() noexcept
	{
		return std::chrono::high_resolution_clock::now();
	}
	double Engine::getTimeNow() noexcept
	{
		return std::chrono::duration_cast<std::chrono::duration<double>>(
			std::chrono::high_resolution_clock::now().time_since_epoch()).count();
	}

	bool Engine::addManager(const ManagerHandle& manager) noexcept
	{
		if (manager == nullptr)
			return false;

		managers.push_back(manager);
		return true;
	}
	bool Engine::removeManager(const ManagerHandle& manager) noexcept
	{
		if (manager == nullptr)
			return false;

		for (auto i = managers.begin(); i != managers.end(); i++)
		{
			if (manager == *i)
			{
				managers.erase(i);
				return true;
			}
		}

		return false;
	}
	bool Engine::containsManager(const ManagerHandle& manager) noexcept
	{
		if (manager == nullptr)
			return false;

		for (auto i = managers.begin(); i != managers.end(); i++)
		{
			if (manager == *i)
				return true;
		}

		return false;
	}
	void Engine::removeManagers() noexcept
	{
		managers.clear();
	}
	size_t Engine::getManagerCount() noexcept
	{
		return managers.size();
	}

	float Engine::toDegrees(float value)
	{
		return value * (static_cast<float>(M_PI) / 180.0f);
	}
	double Engine::toDegrees(double value)
	{
		return value * (M_PI / 180.0);
	}
	float Engine::toRadians(float value)
	{
		return value * (180.0f / static_cast<float>(M_PI));
	}
	double Engine::toRadians(double value)
	{
		return value * (180.0 / M_PI);
	}

	uint16_t Engine::swapEndian(uint16_t value) noexcept
	{
		return static_cast<uint16_t>(BYTE_SWAP_16(value));
	}
	int16_t Engine::swapEndian(int16_t value) noexcept
	{
		auto result = BYTE_SWAP_16(*reinterpret_cast<uint16_t*>(&value));
		return *reinterpret_cast<int16_t*>(&result);
	}
	uint32_t Engine::swapEndian(uint32_t value) noexcept
	{
		return static_cast<uint32_t>(BYTE_SWAP_32(value));
	}
	int32_t Engine::swapEndian(int32_t value) noexcept
	{
		auto result = BYTE_SWAP_32(*reinterpret_cast<uint32_t*>(&value));
		return *reinterpret_cast<int32_t*>(&result);
	}
	uint64_t Engine::swapEndian(uint64_t value) noexcept
	{
		return static_cast<uint64_t>(BYTE_SWAP_64(value));
	}
	int64_t Engine::swapEndian(int64_t value) noexcept
	{
		auto result = BYTE_SWAP_64(*reinterpret_cast<uint64_t*>(&value));
		return *reinterpret_cast<int64_t*>(&result);
	}
	float Engine::swapEndian(float value) noexcept
	{
		auto result = BYTE_SWAP_32(*reinterpret_cast<uint32_t*>(&value));
		return *reinterpret_cast<float*>(&result);
	}
	double Engine::swapEndian(double value) noexcept
	{
		auto result = BYTE_SWAP_64(*reinterpret_cast<uint64_t*>(&value));
		return *reinterpret_cast<double*>(&result);
	}
	
	uint16_t Engine::swapBigEndian(uint16_t value) noexcept
	{
#if INJECTOR_BIG_ENDIAN
		return value;
#else
		return swapEndian(value);
#endif
	}
	int16_t Engine::swapBigEndian(int16_t value) noexcept
	{
#if INJECTOR_BIG_ENDIAN
		return value;
#else
		return swapEndian(value);
#endif
	}
	uint32_t Engine::swapBigEndian(uint32_t value) noexcept
	{
#if INJECTOR_BIG_ENDIAN
		return value;
#else
		return swapEndian(value);
#endif
	}
	int32_t Engine::swapBigEndian(int32_t value) noexcept
	{
#if INJECTOR_BIG_ENDIAN
		return value;
#else
		return swapEndian(value);
#endif
	}
	uint64_t Engine::swapBigEndian(uint64_t value) noexcept
	{
#if INJECTOR_BIG_ENDIAN
		return value;
#else
		return swapEndian(value);
#endif
	}
	int64_t Engine::swapBigEndian(int64_t value) noexcept
	{
#if INJECTOR_BIG_ENDIAN
		return value;
#else
		return swapEndian(value);
#endif
	}
	float Engine::swapBigEndian(float value) noexcept
	{
#if INJECTOR_BIG_ENDIAN
		return value;
#else
		return swapEndian(value);
#endif
	}
	double Engine::swapBigEndian(double value) noexcept
	{
#if INJECTOR_BIG_ENDIAN
		return value;
#else
		return swapEndian(value);
#endif
	}

	uint16_t Engine::swapLittleEndian(uint16_t value) noexcept
	{
#if INJECTOR_BIG_ENDIAN
		return swapEndian(value);
#else
		return value;
#endif
	}
	int16_t Engine::swapLittleEndian(int16_t value) noexcept
	{
#if INJECTOR_BIG_ENDIAN
		return swapEndian(value);
#else
		return value;
#endif
	}
	uint32_t Engine::swapLittleEndian(uint32_t value) noexcept
	{
#if INJECTOR_BIG_ENDIAN
		return swapEndian(value);
#else
		return value;
#endif
	}
	int32_t Engine::swapLittleEndian(int32_t value) noexcept
	{
#if INJECTOR_BIG_ENDIAN
		return swapEndian(value);
#else
		return value;
#endif
	}
	uint64_t Engine::swapLittleEndian(uint64_t value) noexcept
	{
#if INJECTOR_BIG_ENDIAN
		return swapEndian(value);
#else
		return value;
#endif
	}
	int64_t Engine::swapLittleEndian(int64_t value) noexcept
	{
#if INJECTOR_BIG_ENDIAN
		return swapEndian(value);
#else
		return value;
#endif
	}
	float Engine::swapLittleEndian(float value) noexcept
	{
#if INJECTOR_BIG_ENDIAN
		return swapEndian(value);
#else
		return value;
#endif
	}
	double Engine::swapLittleEndian(double value) noexcept
	{
#if INJECTOR_BIG_ENDIAN
		return swapEndian(value);
#else
		return value;
#endif
	}
}
