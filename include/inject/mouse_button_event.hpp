#pragma once
#include <entityx/entityx.h>
#include <glm/glm.hpp>
#include <SDL.h>

namespace inject
{
	struct MouseButtonEvent final : public entityx::Event<MouseButtonEvent>
	{
		enum class Button
		{
			Left = SDL_BUTTON_LEFT,
			Middle = SDL_BUTTON_MIDDLE,
			Right = SDL_BUTTON_RIGHT,
			X1 = SDL_BUTTON_X1,
			X2 = SDL_BUTTON_X2,
		};
		enum class State
		{
			Pressed = SDL_PRESSED,
			Released = SDL_RELEASED,
		};

		uint32_t id;
		Button button;
		State state;
		uint8_t clicks;
		glm::ivec2 position;

		MouseButtonEvent(
			const uint32_t _id,
			const Button _button,
			const State _state,
			const uint8_t _clicks,
			const glm::ivec2 _position) :
			id(_id),
			button(_button),
			state(_state),
			clicks(_clicks),
			position(_position)
		{}
	};
}
