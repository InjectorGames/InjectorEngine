#pragma once
#include <injector/manager.hpp>
#include <injector/window_component.hpp>

#include <set>
#include <SDL_events.h>

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

		bool createWindow(Entity entity) noexcept;
		bool destroyWindow(Entity entity) noexcept;
		void destroyWindows() noexcept;
	};
}
