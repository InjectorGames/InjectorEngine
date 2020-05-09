#pragma once
#include <entityx/entityx.h>
#include <SDL.h>

namespace inject
{
	struct MouseButtonEvent final : public entityx::Event<MouseButtonEvent>
	{
		enum Button
		{
			Left = SDL_BUTTON_LEFT,
			Middle = SDL_BUTTON_MIDDLE,
			Right = SDL_BUTTON_RIGHT,
			X1 = SDL_BUTTON_X1,
			X2 = SDL_BUTTON_X2,
		};
		enum State
		{
			Released = SDL_RELEASED,
			Pressed = SDL_PRESSED,
		};

		const SDL_MouseButtonEvent& data;

		MouseButtonEvent(const SDL_MouseButtonEvent& _data) :
			data(_data)
		{}
	};
}
