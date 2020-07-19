#include <injector/window_system.hpp>
#include <injector/component.hpp>
#include <injector/transform_component.hpp>
#include <injector/gl_window.hpp>
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
				Component<Window*>* windowComponent;

				if (manager.getComponent(id, windowComponent))
				{
					auto windowID = windowComponent->value->getID();

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
							windowComponent->value->hide();
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
			Component<Window*>* windowComponent;

			if (manager.getComponent(id, windowComponent))
			{
				if (windowComponent->value->getFlags() & SDL_WINDOW_SHOWN)
					existsVisible = true;
			}
		}

		if (!existsVisible)
			Engine::stopUpdateLoop();

		/*for (auto id : windows)
		{
			WindowComponent* windowComponent;

			if (manager.getComponent(id, windowComponent))
				windowComponent->window->update();
		}*/
	}

	bool WindowSystem::createWindow(size_t id, const std::string& title,
		const IntVector2& position, const IntVector2& size, uint32_t flags) noexcept
	{
		auto graphicsAPI = Engine::getGraphicsAPI();

		Window* window;

		if (graphicsAPI == GraphicsAPI::OpenGL || graphicsAPI == GraphicsAPI::OpenGLES)
			window = new GlWindow(title, position, size, flags);
		else
			return false;

		Component<Window*>* windowComponent;

		if (!manager.createComponent(id, windowComponent, window))
		{
			delete window;
			return false;
		}

		windows.emplace(id);
		return true;
	}
	bool WindowSystem::destroyWindow(size_t id) noexcept
	{
		auto iterator = windows.find(id);

		if (iterator == windows.end())
			return false;

		Component<Window*>* windowComponent;

		if (!manager.getComponent(id, windowComponent))
		{
			delete windowComponent->value;
			manager.destroyComponent<Component<Window*>>(id);
		}
		
		windows.erase(iterator);
		return true;
	}
	void WindowSystem::destroyWindows() noexcept
	{
		for (auto id : windows)
		{
			Component<Window*>* windowComponent;

			if (manager.getComponent(id, windowComponent))
			{
				delete windowComponent->value;
				manager.destroyComponent<Component<Window*>>(id);
			}
		}
	}
}
