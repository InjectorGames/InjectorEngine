#pragma once
#include "Injector/Graphics/GlfwDefines.hpp"

namespace Injector
{
	// Keyboard or mouse button state
	enum class ButtonState : int
	{
		Press = GLFW_PRESS,
		Release = GLFW_RELEASE,
		Repeat = GLFW_REPEAT,
	};
}