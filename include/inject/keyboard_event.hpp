#pragma once
#include <entityx/entityx.h>
#include <SDL.h>

namespace inject
{
	struct KeyboardEvent final : public entityx::Event<KeyboardEvent>
	{
		enum State
		{
			Released = SDL_RELEASED,
			Pressed = SDL_PRESSED,
		};

		const SDL_KeyboardEvent& data;

		KeyboardEvent(const SDL_KeyboardEvent& _data) :
			data(_data)
		{}
	};
}
