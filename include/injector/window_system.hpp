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
		std::set<EntityHandle> windows;
	public:
		WindowSystem();
		virtual ~WindowSystem();

		void update() override;

		bool createWindowComponent(
			const EntityHandle& entity,
			const std::string& title = Window::defaultTitle,
			const IntVector2& position = Window::defaultPosition,
			const IntVector2& size = Window::defaultSize,
			uint32_t flags = Window::defaultFlags) noexcept;
		bool destroyWindowComponent(
			const EntityHandle& entity) noexcept;
		void destroyWindowComponents() noexcept;
		size_t windowComponentCount() const noexcept;
	};
}
