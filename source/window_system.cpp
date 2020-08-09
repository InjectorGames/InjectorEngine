#include <injector/window_system.hpp>
#include <injector/engine.hpp>
#include <injector/graphics/gl_window.hpp>
#include <injector/graphics/vk_window.hpp>

#include <SDL_events.h>

namespace INJECTOR_NAMESPACE
{
	bool WindowSystem::createWindowOpenGL(
		const EntityHandle& entity,
		const std::string& title,
		const IntVector2& position,
		const IntVector2& size,
		uint32_t flags) noexcept
	{
		if (entity == nullptr)
			return false;

		WindowComponent* component;
		auto window = std::make_shared<GlWindow>(false, title, position, size, flags);
		return entity->createComponent(component, window);
	}
	bool WindowSystem::createWindowOpenGLES(
		const EntityHandle& entity,
		const std::string& title,
		const IntVector2& position,
		const IntVector2& size,
		uint32_t flags) noexcept
	{
		if (entity == nullptr)
			return false;

		WindowComponent* component;
		auto window = std::make_shared<GlWindow>(true, title, position, size, flags);
		return entity->createComponent(component, window);
	}
	bool WindowSystem::createWindowVulkan(
		const EntityHandle& entity,
		const std::string& title,
		const IntVector2& position,
		const IntVector2& size,
		uint32_t flags) noexcept
	{
		if (entity == nullptr)
			return false;

		WindowComponent* component;
		auto window = std::make_shared<VkWindow>(title, position, size, flags);
		return entity->createComponent(component, window);
	}

	WindowSystem::WindowSystem() :
		windows()
	{
		auto graphicsAPI = Engine::getGraphicsAPI();

		switch (graphicsAPI)
		{
		case GraphicsAPI::OpenGL:
			createWindowPointer = createWindowOpenGL;
			break;
		case GraphicsAPI::OpenGLES:
			createWindowPointer = createWindowOpenGLES;
			break;
		case GraphicsAPI::Vulkan:
			createWindowPointer = createWindowVulkan;
			break;
		default:
			throw std::runtime_error("Unknown graphics API");
		}
	}

	void WindowSystem::update()
	{
		SDL_Event event;

		while (SDL_PollEvent(&event) != 0)
		{
			for (auto& window : windows)
			{
				WindowComponent* windowComponent;

				if (!window->getComponent(windowComponent))
					continue;

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
						window->onResize(IntVector2(event.window.data1, event.window.data2));
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

			if (window->getComponent(windowComponent) &&
				windowComponent->window->getFlags() & SDL_WINDOW_SHOWN)
				existsVisible = true;
		}

		if (!existsVisible)
			Engine::stopUpdateLoop();
	}

	bool WindowSystem::addWindow(const EntityHandle& entity) noexcept
	{
		if (entity == nullptr || !entity->containsComponent<WindowComponent>())
			return false;

		return windows.emplace(entity).second;
	}
	bool WindowSystem::removeWindow(const EntityHandle& entity) noexcept
	{
		if (entity == nullptr)
			return false;

		auto iterator = windows.find(entity);

		if (iterator == windows.end())
			return false;

		windows.erase(iterator);
		return true;
	}
	void WindowSystem::removeWindows() noexcept
	{
		windows.clear();
	}
	size_t WindowSystem::getWindowCount() const noexcept
	{
		return windows.size();
	}

	bool WindowSystem::createWindowComponent(
		const EntityHandle& entity,
		const std::string& title,
		const IntVector2& position,
		const IntVector2& size,
		uint32_t flags) noexcept
	{
		return createWindowPointer(entity, title, position, size, flags);
	}
}
