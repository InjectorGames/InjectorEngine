#pragma once
#include <injector/component.hpp>
#include <injector/graphics/window.hpp>

namespace INJECTOR_NAMESPACE
{
	struct WindowComponent final : public Component
	{
		WindowHandle window;
		WindowComponent(const WindowHandle& window = nullptr);
	};
}
