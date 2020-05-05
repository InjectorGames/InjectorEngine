#pragma once
#include <inject/level.hpp>

#include <SDL.h>

#include <map>
#include <string>
#include <stdexcept>

namespace njng
{
	class Engine final
	{
	public:
		inline static const auto DefaultWindowWidth = 800;
		inline static const auto DefaultWindowHeight = 600;
		inline static const auto DefaultWindowName = "Injector Engine";
	private:
		inline static bool initialized = false;
		inline static double lastTime = 0;

		inline static void initializeSDL(uint32_t flags = SDL_INIT_EVERYTHING)
		{
			if (SDL_Init(static_cast<Uint32>(flags)) < 0)
				throw std::runtime_error("Failed to intialize SDL. Error: " + std::string(SDL_GetError()));
		}
		inline static void terminateSDL()
		{
			SDL_Quit();
		}
	public:
		inline static void initialize(uint32_t flags = SDL_INIT_EVERYTHING)
		{
			if (initialized)
				throw std::runtime_error("Engine is already initialized");

			initializeSDL(flags);

			initialized = true;
		}
		inline static void terminate()
		{
			if (!initialized)
				throw std::runtime_error("Engine is not initialized");

			terminateSDL();

			initialized = false;
		}

		inline static void update()
		{
			bool quit = false;
			SDL_Event event = {};

			while (!quit)
			{
				while (SDL_PollEvent(&event) != 0)
				{
					if (event.type == SDL_QUIT)
						quit = true;
				}
			}
			

			/*if (m_window)
			{
				while (!glfwWindowShouldClose(m_window))
				{
					auto time = glfwGetTime();
					auto dt = time - lastTime;

					for (const auto& pair : levels)
					{
						const auto& level = pair.second;
						level->systems.update_all(static_cast<entityx::TimeDelta>(dt));
					}

					lastTime = time;
					glfwPollEvents();
				}
			}
			else
			{
				auto time = glfwGetTime();
				auto dt = time - lastTime;

				for (const auto& pair : levels)
				{
					const auto& level = pair.second;
					level->systems.update_all(static_cast<entityx::TimeDelta>(dt));
				}

				lastTime = time;
				glfwPollEvents();
			}*/
		}

		/*
		inline static void addLevel(std::shared_ptr<Level> level)
		{
			if (!levels.emplace(level->id, level).second)
				throw std::exception("Failed to add level");
		}
		inline static void removeLevel(const size_t id)
		{
			if (levels.erase(id) == 0)
				throw std::exception("Failed to remove level");
		}
		inline static void removeLevels()
		{
			levels.clear();
		}*/
	};
}
