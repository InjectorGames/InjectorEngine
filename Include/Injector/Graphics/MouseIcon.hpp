#pragma once
#include "Injector/Graphics/GlfwDefines.hpp"

namespace Injector
{
	enum class MouseIcon : int
	{
		Arrow = GLFW_ARROW_CURSOR,
		Ibeam = GLFW_IBEAM_CURSOR,
		Crosshair = GLFW_CROSSHAIR_CURSOR,
		Hand = GLFW_HAND_CURSOR,
		HorizontalResize = GLFW_HRESIZE_CURSOR,
		VerticalResize = GLFW_VRESIZE_CURSOR,
	};
}