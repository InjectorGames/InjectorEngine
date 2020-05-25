#pragma once
#include <inject/window.hpp>

#include <GL/glew.h>
#include <SDL_opengl.h>

namespace inject
{
	class GlWindow : public Window
	{
		SDL_GLContext context;
	public:
		// SDL_WINDOW_ALLOW_HIGHDPI
		GlWindow(const std::string& title = INJECT_WINDOW_NAME + std::string(" (OpenGL)"),
			const glm::ivec2& position = glm::ivec2(SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED),
			const glm::ivec2& size = glm::ivec2(INJECT_WINDOW_WIDTH, INJECT_WINDOW_HEIGHT),
			const uint32_t flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL) :
			Window(title, position, size, flags)
		{
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

			context = SDL_GL_CreateContext(window);

			if(!context)
				throw std::runtime_error("Failed to create SDL window OpenGL context. Error: " + std::string(SDL_GetError()));

			SDL_GL_MakeCurrent(window, context);
			SDL_GL_SetSwapInterval(0);

			if(glewInit() != GLEW_OK)
				throw std::runtime_error("Failed to initialize SDL window GLEW.");
		}
		virtual ~GlWindow()
		{
			SDL_GL_DeleteContext(context);
		}

		void update(const double deltaTime) override
		{
			SDL_GL_MakeCurrent(window, context);
			Window::update(deltaTime);
			SDL_GL_SwapWindow(window);
		}
	};
}
