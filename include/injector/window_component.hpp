#pragma once
#include <injector/window.hpp>
#include <memory>

namespace INJECTOR_NAMESPACE
{
	struct WindowComponent
	{
		WindowHandle window;
		WindowComponent(const WindowHandle& window = {});
	};
}
