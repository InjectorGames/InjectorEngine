#pragma once
#include <injector/manager.hpp>
#include <injector/window.hpp>

#include <set>
#include <string>

namespace INJECTOR_NAMESPACE
{
	class WindowSystem : public System
	{
	protected:
		std::set<size_t> windows;
	public:
		WindowSystem(Manager& manager);
		virtual ~WindowSystem();

		void update() override;

		bool createWindow(size_t id,
			const std::string& title = Window::defaultTitle,
			const IntVector2& position = Window::defaultPosition,
			const IntVector2& size = Window::defaultSize,
			uint32_t flags = Window::defaultFlags) noexcept;
		bool destroyWindow(size_t id) noexcept;
		void destroyWindows() noexcept;
	};
}
