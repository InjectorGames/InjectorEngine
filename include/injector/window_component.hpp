#pragma once
#include <injector/defines.hpp>

#include <SDL_video.h>

namespace INJECTOR_NAMESPACE
{
	struct WindowComponent
	{
		SDL_Window* window;

		WindowComponent(
			SDL_Window* _window = nullptr) :
			window(_window)
		{}
	};
}
