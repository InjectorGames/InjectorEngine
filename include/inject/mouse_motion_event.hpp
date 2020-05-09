#pragma once
#include <entityx/entityx.h>
#include <glm/glm.hpp>
#include <SDL.h>

namespace inject
{
	struct MouseMotionEvent final : public entityx::Event<MouseMotionEvent>
	{
		enum class StateBits
		{
			LeftBit = SDL_BUTTON_LMASK,
			MiddleBit = SDL_BUTTON_MMASK,
			RightBit = SDL_BUTTON_RMASK,
			X1Bit = SDL_BUTTON_X1MASK,
			X2Bit = SDL_BUTTON_X2MASK,
		};

		uint32_t id;
		uint32_t state;
		glm::ivec2 position;
		glm::ivec2 deltaPosition;

		MouseMotionEvent(
			const uint32_t _id,
			const uint32_t _state,
			const glm::ivec2 _position,
			const glm::ivec2 _deltaPosition) :
			id(_id),
			state(_state),
			position(_position),
			deltaPosition(_deltaPosition)
		{}
	};
}