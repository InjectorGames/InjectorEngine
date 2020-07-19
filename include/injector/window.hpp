#pragma once
#include <injector/int_vector2.hpp>

#include <string>
#include <SDL.h>

namespace INJECTOR_NAMESPACE
{
	class Window
	{
	protected:
		SDL_Window* window;
	public:
		Window(const std::string& title = INJECTOR_WINDOW_NAME,
			const IntVector2& position = IntVector2(
				SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED),
			const IntVector2& size = IntVector2(
				INJECTOR_WINDOW_WIDTH, INJECTOR_WINDOW_HEIGHT),
			uint32_t flags = SDL_WINDOW_RESIZABLE);
		virtual ~Window();

		uint32_t getID() noexcept;
		uint32_t getFlags() noexcept;

		void hide() noexcept;
	};
}
