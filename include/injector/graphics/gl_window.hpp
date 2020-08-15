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
			IntVector2 position = defaultPosition,
			IntVector2 size = defaultSize,
			uint32_t flags = defaultFlags);
		virtual ~GlWindow();

		bool isGLES() const noexcept;
		SDL_GLContext getContext() const noexcept;

		void makeCurrent() noexcept;
		void swapBuffers() noexcept;

		void onResize(IntVector2 size) override;

		CameraSystemHandle createCameraSystem() override;
		RenderSystemHandle createRenderSystem() override;
		PipelineHandle createColorPipeline() override;
		MeshHandle createSquareMesh() override;
	};
}
