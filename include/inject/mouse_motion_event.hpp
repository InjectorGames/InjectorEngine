#pragma once
#include <entityx/entityx.h>
#include <SDL.h>

namespace inject
{
	struct MouseMotionEvent final :
		public entityx::Event<MouseMotionEvent>
	{
		enum class StateBits
		{
			LeftBit = SDL_BUTTON_LMASK,
			MiddleBit = SDL_BUTTON_MMASK,
			RightBit = SDL_BUTTON_RMASK,
			X1Bit = SDL_BUTTON_X1MASK,
			X2Bit = SDL_BUTTON_X2MASK,
		};

		const SDL_MouseMotionEvent& data;

		MouseMotionEvent(
			const SDL_MouseMotionEvent& _data) :
			data(_data)
		{}
	};
}