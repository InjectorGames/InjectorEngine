#pragma once
#include <injector/manager.hpp>
#include <injector/window_component.hpp>

namespace INJECTOR_NAMESPACE
{
	class WindowSystem : public System
	{
	protected:
		bool (*createWindowPointer)(const EntityHandle&, const std::string&,
			const IntVector2&, const IntVector2&, uint32_t) noexcept;

		std::set<EntityHandle> windows;

		static bool createWindowOpenGL(const EntityHandle& entity,
			const std::string& title = Window::defaultTitle,
			const IntVector2& position = Window::defaultPosition,
			const IntVector2& size = Window::defaultSize,
			uint32_t flags = Window::defaultFlags) noexcept;
		static bool createWindowOpenGLES(const EntityHandle& entity,
			const std::string& title = Window::defaultTitle,
			const IntVector2& position = Window::defaultPosition,
			const IntVector2& size = Window::defaultSize,
			uint32_t flags = Window::defaultFlags) noexcept;
		static bool createWindowVulkan(const EntityHandle& entity,
			const std::string& title = Window::defaultTitle,
			const IntVector2& position = Window::defaultPosition,
			const IntVector2& size = Window::defaultSize,
			uint32_t flags = Window::defaultFlags) noexcept;
	public:
		WindowSystem();
		virtual ~WindowSystem();

		void update() override;

		bool addWindow(const EntityHandle& entity) noexcept;
		bool removeWindow(const EntityHandle& entity) noexcept;
		void removeWindows() noexcept;
		size_t getWindowCount() const noexcept;

		bool createWindowComponent(const EntityHandle& entity,
			const std::string& title = Window::defaultTitle,
			const IntVector2& position = Window::defaultPosition,
			const IntVector2& size = Window::defaultSize,
			uint32_t flags = Window::defaultFlags) noexcept;
	};
}
