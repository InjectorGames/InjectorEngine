#include <injector/window.hpp>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	Window::Window(const std::string& title,
		const IntVector2& position,
		const IntVector2& size,
		uint32_t flags)
	{
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

	void Window::beginRender()
	{}
	void Window::endRender()
	{}

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

	const std::string Window::defaultTitle = "Injector Engine";
	const IntVector2 Window::defaultPosition = IntVector2(
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED);
	const IntVector2 Window::defaultSize = IntVector2(800, 600);
	const uint32_t Window::defaultFlags = SDL_WINDOW_RESIZABLE;
}