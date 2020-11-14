#pragma once
#include "imgui.h"

namespace Injector
{
	class GuiHandler
	{
	 public:
		virtual void onUpdate() = 0;
	};
}