#pragma once
#include "Injector/Input/MouseButton.hpp"
#include "Injector/Input/ButtonState.hpp"

namespace Injector
{
	class GuiHandler
	{
	 public:
		virtual void onMouseEnter() = 0;
		virtual void onMouseExit() = 0;
		virtual void onMouseStay() = 0;

		virtual void onMouseButton(
			MouseButton button,
			ButtonState state) = 0;

		virtual void update() = 0;
	};
}
