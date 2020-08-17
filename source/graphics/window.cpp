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
	const uint32_t Window::defaultFlags = SDL_WINDOW_HIDDEN | SDL_WINDOW_RESIZABLE;

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

		mouseMotion = IntVector2::zero;

		while (SDL_PollEvent(&event) != 0)
		{
			auto windowID = getID();

			if (event.type == SDL_WINDOWEVENT && event.window.windowID == windowID)
			{
				switch (event.window.event)
				{
				case SDL_WINDOWEVENT_SIZE_CHANGED:
					onResize(IntVector2(event.window.data1, event.window.data2));
					break;
				case SDL_WINDOWEVENT_CLOSE:
					active = false;
					break;
				}
			}
			else if (event.type == SDL_MOUSEMOTION && event.motion.windowID == windowID)
			{
				mouseMotion += IntVector2(event.motion.xrel, event.motion.yrel);
			}
			/*else if ((event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) && event.key.windowID == id)
			{
				events.emit<KeyboardEvent>(event.key);
			}
			
			else if ((event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP) && event.button.windowID == id)
			{
				events.emit<MouseButtonEvent>(event.button);
			}*/
		}

		if(!isMinimized())
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
	IntVector2 Window::getMousePosition() const noexcept
	{
		auto position = IntVector2();
		SDL_GetMouseState(&position.x, &position.y);
		return position;
	}
	IntVector2 Window::getGlobalMousePosition() const noexcept
	{
		auto position = IntVector2();
		SDL_GetGlobalMouseState(&position.x, &position.y);
		return position;
	}
	IntVector2 Window::getMouseMotion() const noexcept
	{
		return mouseMotion;
	}
	uint32_t Window::getMouseButtons() const noexcept
	{
		return static_cast<uint32_t>(SDL_GetMouseState(nullptr, nullptr));
	}
	uint32_t Window::getGlobalMouseButtons() const noexcept
	{
		return static_cast<uint32_t>(SDL_GetGlobalMouseState(nullptr, nullptr));
	}
	void Window::getMouseState(IntVector2& position, uint32_t& buttons) const noexcept
	{
		buttons = static_cast<uint32_t>(SDL_GetMouseState(&position.x, &position.y));
	}
	void Window::getGlobalMouseState(IntVector2& position, uint32_t& buttons) const noexcept
	{
		buttons = static_cast<uint32_t>(SDL_GetGlobalMouseState(&position.x, &position.y));
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
	void Window::setResizable(bool resizable) noexcept
	{
		SDL_SetWindowResizable(window, static_cast<SDL_bool>(resizable));
	}
	bool Window::setMouseMode(bool realtive) noexcept
	{
		return SDL_SetRelativeMouseMode(static_cast<SDL_bool>(realtive)) == 0;
	}

	CameraSystemHandle Window::createCameraSystem()
	{
		throw std::runtime_error("Not implemented window function");
	}
	RenderSystemHandle Window::createRenderSystem()
	{
		throw std::runtime_error("Not implemented window function");
	}

	ShaderHandle Window::createShader(ShaderStage stage, const std::string& path)
	{
		throw std::runtime_error("Not implemented window function");
	}
	BufferHandle Window::createBuffer(
		size_t size,
		BufferType type,
		BufferUsage usage,
		const void* data)
	{
		throw std::runtime_error("Not implemented window function");
	}

	PipelineHandle Window::createColorPipeline()
	{
		throw std::runtime_error("Not implemented window function");
	}

	MeshHandle Window::createSquareMesh()
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