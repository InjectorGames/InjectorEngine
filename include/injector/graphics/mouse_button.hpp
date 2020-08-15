#pragma once
#include <injector/defines.hpp>
#include <SDL_mouse.h>

#include <cstdint>

namespace INJECTOR_NAMESPACE
{
	enum class MouseButton : uint32_t
	{
		Left = SDL_BUTTON(SDL_BUTTON_LEFT),
		Middle = SDL_BUTTON(SDL_BUTTON_MIDDLE),
		Right = SDL_BUTTON(SDL_BUTTON_RIGHT),
		Forward = SDL_BUTTON(SDL_BUTTON_X1),
		Back = SDL_BUTTON(SDL_BUTTON_X2),
	};

	inline uint32_t operator|(uint32_t a, MouseButton b)
	{
		return a| static_cast<uint32_t>(b);
	}
	inline uint32_t operator|(MouseButton a, uint32_t b)
	{
		return static_cast<uint32_t>(a) | b;
	}
	inline uint32_t operator&(uint32_t a, MouseButton b)
	{
		return a & static_cast<uint32_t>(b);
	}
	inline uint32_t operator&(MouseButton a, uint32_t b)
	{
		return static_cast<uint32_t>(a) & b;
	}
}
