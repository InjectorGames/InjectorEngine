#include <injector/window_system.hpp>
#include <injector/window_component.hpp>
#include <injector/transform_component.hpp>
#include <injector/gl_window.hpp>
#include <injector/engine.hpp>

#include <SDL_events.h>

namespace INJECTOR_NAMESPACE
{
	WindowSystem::WindowSystem() :
		windows()
	{}
	WindowSystem::~WindowSystem()
	{}

	void WindowSystem::update()
	{
		SDL_Event event;

		while (SDL_PollEvent(&event) != 0)
		{
			for (auto& window : windows)
			{
				WindowComponent* windowComponent;

				if (window->getComponent(windowComponent))
				{
					auto window = windowComponent->window;
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

		for (auto& window : windows)
		{
			WindowComponent* windowComponent;

			if (window->getComponent(windowComponent))
			{
				if (windowComponent->window->getFlags() & SDL_WINDOW_SHOWN)
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

	bool WindowSystem::createWindowComponent(
		const EntityHandle& entity,
		const std::string& title,
		const IntVector2& position,
		const IntVector2& size,
		uint32_t flags) noexcept
	{
		if (entity == nullptr)
			return false;

		auto graphicsAPI = Engine::getGraphicsAPI();

		WindowHandle window;

		if (graphicsAPI == GraphicsAPI::OpenGL || graphicsAPI == GraphicsAPI::OpenGLES)
			window = std::make_shared<GlWindow>(title, position, size, flags);
		else
			return false;

		WindowComponent* windowComponent;

		if (!entity->createComponent(windowComponent, window))
			return false;

		windows.emplace(entity);
		return true;
	}
	bool WindowSystem::destroyWindowComponent(
		const EntityHandle& entity) noexcept
	{
		if (entity == nullptr)
			return false;

		auto iterator = windows.find(entity);

		if (iterator == windows.end())
			return false;

		entity->destroyComponent<WindowComponent>();
		windows.erase(iterator);
		return true;
	}
	void WindowSystem::destroyWindowComponents() noexcept
	{
		for (auto& window : windows)
			window->destroyComponent<WindowComponent>();

		windows.clear();
	}
	size_t WindowSystem::windowComponentCount() const noexcept
	{
		return windows.size();
	}
}
