#pragma once
#include"Injector/Graphics/Window.hpp"

#include "GL/glew.h"
#include "SDL_opengl.h"

namespace Injector
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

		std::shared_ptr<CameraSystem> createCameraSystem() override;
		std::shared_ptr<RenderSystem> createRenderSystem() override;

		std::shared_ptr<Mesh> createMesh(
			size_t indexCount,
			BufferIndex indexType,
			const void* vertexData,
			size_t vertexSize,
			const void* indexData,
			size_t indexSize,
			bool staticUse) override;

		std::shared_ptr<ColorPipeline> createColorPipeline() override;
		std::shared_ptr<DiffusePipeline> createDiffusePipeline() override;
	};
}
