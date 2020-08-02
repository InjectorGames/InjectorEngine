#pragma once
#include <injector/graphics/window.hpp>
#include <memory>

namespace INJECTOR_NAMESPACE
{
	struct WindowComponent
	{
		WindowHandle window;
		WindowComponent(const WindowHandle& window = nullptr);
	};
}
