#pragma once
#include "Injector/Graphics/GUI/GuiHandler.hpp"

namespace Injector
{
	class DragGuiHandler : public GuiHandler
	{
	 public:
		void update() override;

		void onMouseEnter() override;
		void onMouseExit() override;
		void onMouseStay() override;

		void onMouseButton(
			MouseButton button,
			ButtonState state) override;
	};
}
