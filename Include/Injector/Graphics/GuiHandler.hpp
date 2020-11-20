#pragma once
#include "Injector/Graphics/ImguiDefines.hpp"

namespace Injector
{
	class GuiHandler
	{
	 public:
		virtual void onUpdate() = 0;
	};
}