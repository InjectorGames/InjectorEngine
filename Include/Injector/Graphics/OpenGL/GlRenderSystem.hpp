#pragma once
#include "Injector/Graphics/RenderSystem.hpp"
#include "Injector/Graphics/OpenGL/GlWindow.hpp"

namespace Injector
{
	class GlRenderSystem : public RenderSystem
	{
	 protected:
		std::shared_ptr<GlWindow> window;
	 public:
		explicit GlRenderSystem(
			const std::shared_ptr<GlWindow>& window);

		void update() override;
	};
}
