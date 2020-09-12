#include "Injector/Graphics/GlWindow.hpp"
#include "Injector/Graphics/GraphicsException.hpp"
#include "Injector/Graphics/GlMesh.hpp"
#include "Injector/Graphics/GlCameraSystem.hpp"
#include "Injector/Graphics/GlRenderSystem.hpp"
#include "Injector/Graphics/GlColorPipeline.hpp"
#include "Injector/Graphics/GlDiffusePipeline.hpp"

namespace Injector
{
	GlWindow::GlWindow(
		bool _gles,
		const std::string& title,
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
			throw GraphicsException("Failed to create window OpenGL context, Error: " + std::string(SDL_GetError()));

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

	std::shared_ptr<CameraSystem> GlWindow::createCameraSystem()
	{
		auto system = std::make_shared<GlCameraSystem>(*this);
		systems.push_back(system);
		return system;
	}
	std::shared_ptr<RenderSystem> GlWindow::createRenderSystem()
	{
		auto system = std::make_shared<GlRenderSystem>(*this);
		systems.push_back(system);
		return system;
	}

	std::shared_ptr<Buffer> GlWindow::createBuffer(
		size_t size,
		BufferType type,
		bool mappable,
		const void* data)
	{
		auto usage = mappable ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW;
		return std::make_shared<GlBuffer>(type, size, usage, data);
	}
	std::shared_ptr<Mesh> GlWindow::createMesh(
		size_t indexCount,
		BufferIndex indexType,
		const std::shared_ptr<Buffer>& vertexBuffer,
		const std::shared_ptr<Buffer>& indexBuffer)
	{
		return std::make_shared<GlMesh>(
			indexCount, indexType, vertexBuffer, indexBuffer);
	}
	std::shared_ptr<Texture> GlWindow::createTexture()
	{
		return nullptr;
	}

	std::shared_ptr<ColorPipeline> GlWindow::createColorPipeline()
	{
		return std::make_shared<GlColorPipeline>(gles);
	}
	std::shared_ptr<DiffusePipeline> GlWindow::createDiffusePipeline()
	{
		return std::make_shared<GlDiffusePipeline>(gles);
	}
}
