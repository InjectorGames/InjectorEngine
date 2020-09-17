#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace Injector
{
	enum class ButtonState : int
	{
		Press = GLFW_PRESS,
		Release = GLFW_RELEASE,
	};
}