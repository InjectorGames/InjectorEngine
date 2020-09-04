#pragma once
#include <injector/graphics/render_system.hpp>
#include <injector/graphics/gl_window.hpp>

namespace injector::graphics
{
	class GlRenderSystem : public RenderSystem
	{
	protected:
		GlWindow& window;
	public:
		GlRenderSystem(GlWindow& window);
		virtual ~GlRenderSystem();

		void update() override;
	};
}
