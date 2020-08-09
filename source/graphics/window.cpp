#include <injector/graphics/window.hpp>
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
	void Window::onResize(const IntVector2& size)
	{}

	uint32_t Window::getID() const noexcept
	{
		return SDL_GetWindowID(window);
	}
	uint32_t Window::getFlags() const noexcept
	{
		return SDL_GetWindowFlags(window);
	}
	bool Window::getShown() const noexcept
	{
		return SDL_GetWindowFlags(window) & SDL_WINDOW_SHOWN;
	}
	IntVector2 Window::getSize() const noexcept
	{
		auto size = IntVector2();
		SDL_GetWindowSize(window, &size.x, &size.y);
		return size;
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
}