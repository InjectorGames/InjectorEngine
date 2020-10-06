#pragma once
#include "Injector/Graphics/GlfwDefines.hpp"

namespace Injector
{
	enum class MouseMode : int
	{
		Normal = GLFW_CURSOR_NORMAL,
		Hidden = GLFW_CURSOR_HIDDEN,
		Disabled = GLFW_CURSOR_DISABLED,
	};
}
