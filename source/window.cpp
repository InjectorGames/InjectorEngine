#include <injector/window.hpp>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	const std::string Window::defaultTitle = INJECTOR_WINDOW_NAME;
	const IntVector2 Window::defaultPosition = IntVector2(
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED);
	const IntVector2 Window::defaultSize = IntVector2(
		INJECTOR_WINDOW_WIDTH, INJECTOR_WINDOW_HEIGHT);
	const uint32_t Window::defaultFlags = SDL_WINDOW_RESIZABLE;

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

	void Window::setContext()
	{}
	void Window::swapChain()
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
}