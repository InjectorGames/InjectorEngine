#include <injector/graphics/window.hpp>
#include <injector/engine.hpp>
#include <injector/graphics/gl_window.hpp>
#include <injector/graphics/vk_window.hpp>

#include <SDL_events.h>

#include <stdexcept>
#include <iostream>

namespace INJECTOR_NAMESPACE
{
	const std::string Window::defaultTitle = "Injector Engine";
	const IntVector2 Window::defaultPosition = IntVector2(
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED);
	const IntVector2 Window::defaultSize = IntVector2(800, 600);
	const uint32_t Window::defaultFlags = SDL_WINDOW_RESIZABLE;

	Window::Window(const std::string& title,
		IntVector2 position,
		IntVector2 size,
		uint32_t flags)
	{
		window = SDL_CreateWindow(title.c_str(),
			position.x, position.y, size.x, size.y, flags);

		if (!window)
			throw std::runtime_error(
				"Failed to create SDL window: " + std::string(SDL_GetError()));

		SDL_SetWindowMinimumSize(window, 1, 1);
	}
	Window::~Window()
	{
		SDL_DestroyWindow(window);
		window = nullptr;
	}

	void Window::update()
	{
		SDL_Event event;

		while (SDL_PollEvent(&event) != 0)
		{
			auto windowID = getID();

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
					onResize(IntVector2(event.window.data1, event.window.data2));
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
					active = false;
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

		Manager::update();
	}
	void Window::onResize(IntVector2 size)
	{
		throw std::runtime_error("Not implemented window function");
	}

	uint32_t Window::getID() const noexcept
	{
		return SDL_GetWindowID(window);
	}
	uint32_t Window::getFlags() const noexcept
	{
		return SDL_GetWindowFlags(window);
	}
	IntVector2 Window::getSize() const noexcept
	{
		auto size = IntVector2();
		SDL_GetWindowSize(window, &size.x, &size.y);
		return size;
	}
	bool Window::isHidden() const noexcept
	{
		return SDL_GetWindowFlags(window) & SDL_WINDOW_HIDDEN;
	}
	bool Window::isShown() const noexcept
	{
		return SDL_GetWindowFlags(window) & SDL_WINDOW_SHOWN;
	}
	bool Window::isMinimized() const noexcept
	{
		return SDL_GetWindowFlags(window) & SDL_WINDOW_MINIMIZED;
	}
	bool Window::isMaximized() const noexcept
	{
		return SDL_GetWindowFlags(window) & SDL_WINDOW_MAXIMIZED;
	}
	bool Window::isResizable() const noexcept
	{
		return SDL_GetWindowFlags(window) & SDL_WINDOW_RESIZABLE;
	}

	void Window::hide() noexcept
	{
		SDL_HideWindow(window);
	}
	void Window::show() noexcept
	{
		SDL_ShowWindow(window);
	}
	void Window::minimize() noexcept
	{
		SDL_MinimizeWindow(window);
	}
	void Window::maximize() noexcept
	{
		SDL_MaximizeWindow(window);
	}
	void Window::setResizable(bool value) noexcept
	{
		SDL_SetWindowResizable(window, static_cast<SDL_bool>(value));
	}

	ShaderHandle Window::createShader(ShaderStage stage, const std::string& path)
	{
		throw std::runtime_error("Not implemented window function");
	}
	MeshHandle Window::createCubeMesh()
	{
		throw std::runtime_error("Not implemented window function");
	}

	std::shared_ptr<Window> Window::create(
		const std::string& title,
		IntVector2 position,
		IntVector2 size,
		uint32_t flags)
	{
		auto graphicsAPI = Engine::getGraphicsAPI();

		if (graphicsAPI == GraphicsAPI::OpenGL)
			return Engine::createManager<GlWindow>(false, title, position, size, flags);
		else if (graphicsAPI == GraphicsAPI::OpenGLES)
			return Engine::createManager<GlWindow>(true, title, position, size, flags);
		else if (graphicsAPI == GraphicsAPI::Vulkan)
			return Engine::createManager<VkWindow>(title, position, size, flags);
		else
			throw std::runtime_error("Failed to create window, unknown graphics API");
	}
}