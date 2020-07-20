#pragma once
#include <injector/window.hpp>

namespace INJECTOR_NAMESPACE
{
	class GlWindow : public Window
	{
	protected:
		void* context;
	public:
		GlWindow(const std::string& title = defaultTitle,
			const IntVector2& position = defaultPosition,
			const IntVector2& size = defaultSize,
			uint32_t flags = defaultFlags);
		virtual ~GlWindow();

		void setContext() override;
		void swapChain() override;
	};
}
