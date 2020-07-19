#pragma once
#include <injector/manager.hpp>

#include <set>

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

		bool createWindow(size_t id) noexcept;
		bool destroyWindow(size_t id) noexcept;
		void destroyWindows() noexcept;
	};
}
