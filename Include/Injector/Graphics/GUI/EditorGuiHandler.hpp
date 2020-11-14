#pragma once
#include "Injector/Graphics/GuiHandler.hpp"

namespace Injector
{
	class EditorGuiHandler : public GuiHandler
	{
	 public:
		void onUpdate() override;
	};
}
