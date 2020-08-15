#include <injector/graphics/gl_render_system.hpp>

namespace INJECTOR_NAMESPACE
{
	GlRenderSystem::GlRenderSystem(GlWindow& _window) :
		window(_window)
	{}
	GlRenderSystem::~GlRenderSystem()
	{}

	void GlRenderSystem::update()
	{
		window.makeCurrent();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		window.swapBuffers();
	}
}
