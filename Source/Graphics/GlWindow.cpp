#include "Injector/Graphics/GlWindow.hpp"
#include "Injector/Graphics/GraphicsException.hpp"
#include "Injector/Graphics/GlMesh.hpp"
#include "Injector/Graphics/GlCameraSystem.hpp"
#include "Injector/Graphics/GlRenderSystem.hpp"
#include "Injector/Graphics/GlColorPipeline.hpp"
#include "Injector/Graphics/GlDiffusePipeline.hpp"

namespace Injector::Graphics
{
	GlWindow::GlWindow(
		bool _gles,
		const string& title,
		IntVector2 position,
		IntVector2 size,
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
			throw GraphicsException("Failed to create window OpenGL context, Error: " + string(SDL_GetError()));

		SDL_GL_MakeCurrent(window, context);

		if (glewInit() != GLEW_OK)
			throw GraphicsException("Failed to initialize window GLEW.");

		SDL_GL_SetSwapInterval(0);
		//glEnable(GL_DEPTH_TEST);
		//glEnable(GL_STENCIL_TEST);
	}
	GlWindow::~GlWindow()
	{
		SDL_GL_DeleteContext(context);
		context = nullptr;
	}

	bool GlWindow::isGLES() const noexcept
	{
		return gles;
	}
	SDL_GLContext GlWindow::getContext() const noexcept
	{
		return context;
	}

	void GlWindow::makeCurrent() noexcept
	{
		SDL_GL_MakeCurrent(window, context);
	}
	void GlWindow::swapBuffers() noexcept
	{
		SDL_GL_SwapWindow(window);
	}

	void GlWindow::onResize(IntVector2 size)
	{
		makeCurrent();
		glViewport(0, 0, size.x, size.y);
	}

	shared_ptr<CameraSystem> GlWindow::createCameraSystem()
	{
		auto system = make_shared<GlCameraSystem>(*this);
		systems.push_back(system);
		return system;
	}
	shared_ptr<RenderSystem> GlWindow::createRenderSystem()
	{
		auto system = make_shared<GlRenderSystem>(*this);
		systems.push_back(system);
		return system;
	}

	shared_ptr<Mesh> GlWindow::createMesh(
		size_t indexCount,
		BufferIndex indexType,
		const void* vertexData,
		size_t vertexSize,
		const void* indexData,
		size_t indexSize,
		bool staticUse)
	{
		auto usage = staticUse ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;

		auto vertexBuffer = make_shared<GlBuffer>(
			vertexSize, GL_ARRAY_BUFFER, usage, vertexData);
		auto indexBuffer = make_shared<GlBuffer>(
			indexSize, GL_ELEMENT_ARRAY_BUFFER, usage, indexData);

		return make_shared<GlMesh>(
			indexCount, indexType, vertexBuffer, indexBuffer);
	}

	shared_ptr<ColorPipeline> GlWindow::createColorPipeline()
	{
		return make_shared<GlColorPipeline>(gles);
	}
	shared_ptr<DiffusePipeline> GlWindow::createDiffusePipeline()
	{
		return make_shared<GlDiffusePipeline>(gles);
	}
}
