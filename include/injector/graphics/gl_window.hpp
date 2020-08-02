#pragma once
#include <injector/graphics/window.hpp>

#include <GL/glew.h>
#include <SDL_opengl.h>

namespace INJECTOR_NAMESPACE
{
	class GlWindow : public Window
	{
	protected:
		bool gles;
		SDL_GLContext context;
	public:
		GlWindow(bool gles = false,
			const std::string& title = defaultTitle,
			const IntVector2& position = defaultPosition,
			const IntVector2& size = defaultSize,
			uint32_t flags = defaultFlags);
		virtual ~GlWindow();

		bool getGLES() const noexcept;
		SDL_GLContext getContext() const noexcept;

		void beginRender() override;
		void endRender() override;
	};
}
