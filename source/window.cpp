#include <injector/window.hpp>
#include <injector/engine.hpp>

#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	Window::Window(const std::string& title, const IntVector2& position,
		const IntVector2& size, uint32_t flags)
	{
		auto graphicsAPI = Engine::getGraphicsAPI();

		switch (graphicsAPI)
		{
		case injector::GraphicsAPI::OpenGL:
		case injector::GraphicsAPI::OpenGLES:
			flags |= SDL_WINDOW_OPENGL;
			break;
		case injector::GraphicsAPI::Vulkan:
			flags |= SDL_WINDOW_VULKAN;
			break;
		default:
			throw std::runtime_error("Unknown graphics API");
		}

		window = SDL_CreateWindow(title.c_str(),
			position.x, position.y, size.x, size.y, flags);

		if (!window)
			throw std::runtime_error(
				"Failed to create SDL window: " + std::string(SDL_GetError()));
	}
	Window::~Window()
	{
		SDL_DestroyWindow(window);
		window = nullptr;
	}

	uint32_t Window::getID() noexcept
	{
		return SDL_GetWindowID(window);
	}
	uint32_t Window::getFlags() noexcept
	{
		return SDL_GetWindowFlags(window);
	}

	void Window::hide() noexcept
	{
		SDL_HideWindow(window);
	}
}