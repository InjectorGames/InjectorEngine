#pragma once
#include <inject/level.hpp>
#include <inject/keyboard_event.hpp>
#include <inject/window_pos_event.hpp>
#include <inject/window_size_event.hpp>
#include <inject/aspect_ratio_event.hpp>
#include <inject/mouse_button_event.hpp>
#include <inject/mouse_motion_event.hpp>

#include <SDL.h>
#include <glm/glm.hpp>

#include <map>
#include <string>
#include <cstdint>
#include <stdexcept>

namespace inject
{
#define INJECT_WINDOW_NAME "Inject Engine"
#define INJECT_WINDOW_WIDTH 800
#define INJECT_WINDOW_HEIGHT 600

	class Window
	{
	protected:
		SDL_Window* window;

		glm::ivec2 windowPos;
		glm::ivec2 windowSize;
		float aspectRatio;

		std::map<uint32_t, std::shared_ptr<Level>> levels;

		inline void handleSizeChangedEvent(const SDL_WindowEvent& event)
		{
			const auto newWindowSize = glm::ivec2(
				static_cast<int>(event.data1),
				static_cast<int>(event.data2));
			const auto deltaWindowSize = newWindowSize - windowSize;
			windowSize = newWindowSize;

			const auto newAspectRatio = float(newWindowSize.x) / float(newWindowSize.y);
			const auto deltaAspectRatio = newAspectRatio - aspectRatio;
			aspectRatio = newAspectRatio;

			for (const auto& pair : levels)
			{
				const auto& level = pair.second;
				level->events.emit<WindowSizeEvent>(newWindowSize, deltaWindowSize);
				level->events.emit<AspectRatioEvent>(newAspectRatio, deltaAspectRatio);
			}
		}
		inline void handleMovedEvent(const SDL_WindowEvent& event)
		{
			const auto newWindowPos = glm::ivec2(
				static_cast<int>(event.data1), 
				static_cast<int>(event.data2));
			const auto deltaWindowPos = newWindowPos - windowPos;
			windowPos = newWindowPos;

			for (const auto& pair : levels)
			{
				const auto& level = pair.second;
				level->events.emit<WindowPosEvent>(newWindowPos, deltaWindowPos);
			}
		}
	public:
		Window(const std::string& title = INJECT_WINDOW_NAME,
			const glm::ivec2& position = glm::ivec2(SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED),
			const glm::ivec2& size = glm::ivec2(INJECT_WINDOW_WIDTH, INJECT_WINDOW_HEIGHT),
			const uint32_t flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE) :
			windowSize(glm::ivec2(INJECT_WINDOW_WIDTH, INJECT_WINDOW_HEIGHT)),
			aspectRatio(float(INJECT_WINDOW_WIDTH) / float(INJECT_WINDOW_HEIGHT))
		{
			window = SDL_CreateWindow(title.c_str(), position.x, position.y, size.x, size.y, flags);

			if (!window)
				throw std::runtime_error("Failed to create SDL window. Error: " + std::string(SDL_GetError()));

			SDL_GetWindowPosition(window, &windowPos.x, &windowPos.y);
		}
		virtual ~Window()
		{
			levels.clear();

			SDL_DestroyWindow(window);
			window = nullptr;
		}

		inline uint32_t getId() const noexcept
		{
			return static_cast<uint32_t>(SDL_GetWindowID(window));
		}
		inline bool isShown() const noexcept
		{
			return SDL_GetWindowFlags(window) & SDL_WINDOW_SHOWN;
		}

		inline void addLevel(std::shared_ptr<Level> level)
		{
			if (!levels.emplace(level->getId(), level).second)
				throw std::exception("Failed to add level");
		}
		inline void removeLevel(const uint32_t id)
		{
			if (levels.erase(id) == 0)
				throw std::exception("Failed to remove level");
		}
		inline void removeLevels()
		{
			levels.clear();
		}

		virtual void handleCloseEvent(const SDL_WindowEvent& event)
		{
			SDL_HideWindow(window);
		}
		virtual void handleEvent(const SDL_Event& event)
		{
			auto id = getId();

			if (event.type == SDL_WINDOWEVENT && event.window.windowID == id)
			{
				switch (event.window.event)
				{
				case SDL_WINDOWEVENT_HIDDEN:
					break;
				case SDL_WINDOWEVENT_SHOWN:
					break;
				case SDL_WINDOWEVENT_EXPOSED:
					break;
				case SDL_WINDOWEVENT_MOVED:
					handleMovedEvent(event.window);
					break;
				case SDL_WINDOWEVENT_SIZE_CHANGED:
					handleSizeChangedEvent(event.window);
					break;
				case SDL_WINDOWEVENT_MINIMIZED:
					break;
				case SDL_WINDOWEVENT_MAXIMIZED:
					break;
				case SDL_WINDOWEVENT_RESTORED:
					break;
				case SDL_WINDOWEVENT_ENTER:
					break;
				case SDL_WINDOWEVENT_LEAVE:
					break;
				case SDL_WINDOWEVENT_FOCUS_GAINED:
					break;
				case SDL_WINDOWEVENT_FOCUS_LOST:
					break;
				case SDL_WINDOWEVENT_CLOSE:
					handleCloseEvent(event.window);
					break;
				}
			}
			else if ((event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) && event.key.windowID == id)
			{
				for (const auto& pair : levels)
				{
					const auto& level = pair.second;
					level->events.emit<KeyboardEvent>(event.key);
				}
			}
			else if (event.type == SDL_MOUSEMOTION && event.motion.windowID == id)
			{
				for (const auto& pair : levels)
				{
					const auto& level = pair.second;
					level->events.emit<MouseMotionEvent>(event.motion);
				}
			}
			else if ((event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) && event.button.windowID == id)
			{
				for (const auto& pair : levels)
				{
					const auto& level = pair.second;
					level->events.emit<MouseButtonEvent>(event.button);
				}
			}
		}

		virtual void update(const double deltaTime)
		{
			for (const auto& pair : levels)
			{
				const auto& level = pair.second;
				level->update(deltaTime);
			}
		}
	};
}