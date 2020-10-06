#pragma once
#include "Injector/Graphics/GlfwDefines.hpp"

namespace Injector
{
	enum class ButtonState : int
	{
		Press = GLFW_PRESS,
		Release = GLFW_RELEASE,
		Repeat = GLFW_REPEAT,
	};
}