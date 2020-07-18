#pragma once
#include <injector/manager.hpp>
#include <injector/keyboard_event.hpp>
#include <injector/window_pos_event.hpp>
#include <injector/window_size_event.hpp>
#include <injector/mouse_button_event.hpp>
#include <injector/mouse_motion_event.hpp>

#include <SDL_events.h>
#include <string>

namespace INJECT_NAMESPACE
{
	class Window : public Manager
	{
	protected:
		SDL_Window* window;

		glm::ivec2 windowPos;
		glm::ivec2 windowSize;

		inline void handleHiddenEvent(const SDL_WindowEvent& event)
		{
			isActive = false;
		}
		inline void handleShownEvent(const SDL_WindowEvent& event)
		{
			isActive = true;
		}
		inline void handleSizeChangedEvent(const SDL_WindowEvent& event)
		{
			const auto newWindowSize = glm::ivec2(
				static_cast<int>(event.data1),
				static_cast<int>(event.data2));
			const auto deltaWindowSize = newWindowSize - windowSize;
			windowSize = newWindowSize;
			events.emit<WindowSizeEvent>(newWindowSize, deltaWindowSize);
		}
		inline void handleMovedEvent(const SDL_WindowEvent& event)
		{
			const auto newWindowPos = glm::ivec2(
				static_cast<int>(event.data1), 
				static_cast<int>(event.data2));
			const auto deltaWindowPos = newWindowPos - windowPos;
			windowPos = newWindowPos;
			events.emit<WindowPosEvent>(newWindowPos, deltaWindowPos);
		}
		virtual void handleCloseEvent(const SDL_WindowEvent& event)
		{
			SDL_HideWindow(window);
		}
	public:
		Window(const std::string& title = INJECT_WINDOW_NAME,
			const glm::ivec2& position = glm::ivec2(SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED),
			const glm::ivec2& size = glm::ivec2(INJECT_WINDOW_WIDTH, INJECT_WINDOW_HEIGHT),
			const uint32_t flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE) :
			windowSize(glm::ivec2(INJECT_WINDOW_WIDTH, INJECT_WINDOW_HEIGHT))
		{
			window = SDL_CreateWindow(title.c_str(), position.x, position.y, size.x, size.y, flags);

			if (!window)
				throw std::runtime_error("Failed to create SDL window. Error: " + std::string(SDL_GetError()));

			id = static_cast<uint32_t>(SDL_GetWindowID(window));
			SDL_GetWindowPosition(window, &windowPos.x, &windowPos.y);
		}
		virtual ~Window()
		{
			SDL_DestroyWindow(window);
			window = nullptr;
		}
		
		virtual void handleEvent(const SDL_Event& event)
		{
			auto id = SDL_GetWindowID(window);

			if (event.type == SDL_WINDOWEVENT && event.window.windowID == id)
			{
				switch (event.window.event)
				{
				case SDL_WINDOWEVENT_HIDDEN:
					handleHiddenEvent(event.window);
					break;
				case SDL_WINDOWEVENT_SHOWN:
					handleShownEvent(event.window);
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
				events.emit<KeyboardEvent>(event.key);
			}
			else if (event.type == SDL_MOUSEMOTION && event.motion.windowID == id)
			{
				events.emit<MouseMotionEvent>(event.motion);
			}
			else if ((event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) && event.button.windowID == id)
			{
				events.emit<MouseButtonEvent>(event.button);
			}
		}
	};
}