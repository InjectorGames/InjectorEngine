#include <injector/window_system.hpp>
#include <injector/window.hpp>
#include <injector/engine.hpp>

#include <SDL_events.h>

namespace INJECTOR_NAMESPACE
{
	WindowSystem::WindowSystem(Manager& manager) :
		System(manager),
		windows()
	{}
	WindowSystem::~WindowSystem()
	{
		destroyWindows();
	}

	void WindowSystem::update()
	{
		SDL_Event event;

		while (SDL_PollEvent(&event) != 0)
		{
			for (auto id : windows)
			{
				Window* window;

				if (manager.getComponent(id, window))
				{
					auto windowID = window->getID();

					if (event.type == SDL_WINDOWEVENT && event.window.windowID == windowID)
					{
						switch (event.window.event)
						{
						case SDL_WINDOWEVENT_HIDDEN:
							//handleHiddenEvent(event.window);
							break;
						case SDL_WINDOWEVENT_SHOWN:
							//handleShownEvent(event.window);
							break;
						case SDL_WINDOWEVENT_EXPOSED:
							break;
						case SDL_WINDOWEVENT_MOVED:
							//handleMovedEvent(event.window);
							break;
						case SDL_WINDOWEVENT_SIZE_CHANGED:
							//handleSizeChangedEvent(event.window);
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
							window->hide();
							break;
						}
					}
				}
				/*else if ((event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) && event.key.windowID == id)
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
				}*/
			}
		}

		bool existsVisible = false;

		for (auto id : windows)
		{
			Window* window;

			if (manager.getComponent(id, window))
			{
				if (window->getFlags() & SDL_WINDOW_SHOWN)
					existsVisible = true;
			}
		}

		if (!existsVisible)
			Engine::stopUpdateLoop();
	}

	bool WindowSystem::createWindow(size_t id) noexcept
	{
		Window* window;

		if (!manager.createComponent(id, window))
			return false;

		windows.emplace(id);
		return true;
	}
	bool WindowSystem::destroyWindow(size_t id) noexcept
	{
		auto iterator = windows.find(id);

		if (iterator == windows.end())
			return false;

		Window* window;

		if (!manager.getComponent(id, window))
			manager.destroyComponent<Window>(id);
		
		windows.erase(iterator);
		return true;
	}
	void WindowSystem::destroyWindows() noexcept
	{
		for (auto id : windows)
		{
			Window* component;

			if (manager.getComponent(id, component))
				manager.destroyComponent<Window>(id);
		}
	}
}
