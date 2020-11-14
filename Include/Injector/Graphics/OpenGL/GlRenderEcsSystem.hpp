#pragma once
#include "Injector/Graphics/RenderEcsSystem.hpp"
#include "Injector/Graphics/OpenGL/GlGpuWindow.hpp"

namespace Injector
{
	class GlRenderEcsSystem : public RenderEcsSystem
	{
	 protected:
		std::shared_ptr<GlGpuWindow> window;
	 public:
		explicit GlRenderEcsSystem(
			const std::shared_ptr<GlGpuWindow>& window);

		const std::shared_ptr<GlGpuWindow>&
			getWindow() const noexcept;

		void onUpdate() override;
	};
}
