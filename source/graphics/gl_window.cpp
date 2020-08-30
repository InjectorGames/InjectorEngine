#include <injector/graphics/gl_window.hpp>
#include <injector/graphics/gl_mesh.hpp>
#include <injector/graphics/gl_camera_system.hpp>
#include <injector/graphics/gl_render_system.hpp>
#include <injector/graphics/gl_color_pipeline.hpp>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	GlWindow::GlWindow(bool _gles,
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
			throw std::runtime_error(
				"Failed to create window OpenGL context: " + std::string(SDL_GetError()));

		SDL_GL_MakeCurrent(window, context);

		if (glewInit() != GLEW_OK)
			throw std::runtime_error("Failed to initialize window GLEW.");

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

	CameraSystemHandle GlWindow::createCameraSystem()
	{
		auto system = std::make_shared<GlCameraSystem>(*this);
		systems.push_back(system);
		return system;
	}
	RenderSystemHandle GlWindow::createRenderSystem()
	{
		auto system = std::make_shared<GlRenderSystem>(*this);
		systems.push_back(system);
		return system;
	}

	MeshHandle GlWindow::createMesh(
		size_t indexCount,
		BufferIndex indexType,
		const void* vertexData,
		size_t vertexSize,
		const void* indexData,
		size_t indexSize,
		bool staticUse)
	{
		auto usage = staticUse ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW;

		auto vertexBuffer = std::make_shared<GlBuffer>(
			vertexSize, GL_ARRAY_BUFFER, usage, vertexData);
		auto indexBuffer = std::make_shared<GlBuffer>(
			indexSize, GL_ELEMENT_ARRAY_BUFFER, usage, indexData);

		return std::make_shared<GlMesh>(
			indexCount, indexType, vertexBuffer, indexBuffer);
	}

	ColorPipelineHandle GlWindow::createColorPipeline()
	{
		return std::make_shared<GlColorPipeline>(gles);
	}
}
