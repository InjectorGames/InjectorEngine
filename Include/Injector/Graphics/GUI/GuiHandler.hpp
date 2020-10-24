#pragma once
#include "Injector/Graphics/MouseButton.hpp"

namespace Injector
{
	class GuiHandler
	{
	 public:
		virtual void onMouseEnter() = 0;
		virtual void onMouseExit() = 0;
		virtual void onMouseStay() = 0;

		virtual void onMouseButton(
			MouseButton button) = 0;
	};
}
