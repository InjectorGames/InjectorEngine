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

		std::shared_ptr<Buffer> createBuffer(
			size_t size,
			BufferType type,
			bool mappable,
			const void* data) override;
		std::shared_ptr<Mesh> createMesh(
			size_t indexCount,
			BufferIndex indexType,
			const std::shared_ptr<Buffer>& vertexBuffer,
			const std::shared_ptr<Buffer>& indexBuffer) override;
		std::shared_ptr<Texture> createTexture(
        	int size,
       		TextureFormat format,
        	TextureFilter minFilter,
    		TextureFilter magFilter,
    		TextureWrap wrapU,
        	bool useMipmap,
			const std::shared_ptr<Image>& image) override;
		std::shared_ptr<Texture> createTexture(
        	const IntVector2& size,
       		TextureFormat format,
        	TextureFilter minFilter,
    		TextureFilter magFilter,
    		TextureWrap wrapU,
        	TextureWrap wrapV,
        	bool useMipmap,
			const std::shared_ptr<Image>& image) override;
		std::shared_ptr<Texture> createTexture(
        	const IntVector3& size,
       		TextureFormat format,
        	TextureFilter minFilter,
    		TextureFilter magFilter,
    		TextureWrap wrapU,
        	TextureWrap wrapV,
        	TextureWrap wrapW,
        	bool useMipmap,
			const std::shared_ptr<Image>& image) override;

		std::shared_ptr<ColorPipeline> createColorPipeline() override;
		std::shared_ptr<ColorPipeline> createColColorPipeline() override;
		std::shared_ptr<DiffusePipeline> createDiffusePipeline() override;
		std::shared_ptr<TexDiffusePipeline> createTexDiffusePipeline(
			const std::shared_ptr<Texture>& texture) override;
	};
}
