#include <injector/graphics/gl_window.hpp>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	GlWindow::GlWindow(bool _gles,
		const std::string& title,
		const IntVector2& position,
		const IntVector2& size,
		uint32_t flags) :
		Window(title, position, size, flags | SDL_WINDOW_OPENGL),
		gles(_gles)
	{
		if (_gles)
		{
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
		}
		else
		{
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		}
		
		context = SDL_GL_CreateContext(window);

		if (!context)
			throw std::runtime_error(
				"Failed to create window OpenGL context: " + std::string(SDL_GetError()));

		SDL_GL_MakeCurrent(window, context);
		SDL_GL_SetSwapInterval(0);

		if (glewInit() != GLEW_OK)
			throw std::runtime_error("Failed to initialize window GLEW.");
	}
	GlWindow::~GlWindow()
	{
		SDL_GL_DeleteContext(context);
		context = nullptr;
	}

	bool GlWindow::getGLES() const noexcept
	{
		return gles;
	}
	SDL_GLContext GlWindow::getContext() const noexcept
	{
		return context;
	}

	void GlWindow::beginRender()
	{
		SDL_GL_MakeCurrent(window, context);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_STENCIL_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	}
	void GlWindow::endRender()
	{
		SDL_GL_SwapWindow(window);
	}
}
