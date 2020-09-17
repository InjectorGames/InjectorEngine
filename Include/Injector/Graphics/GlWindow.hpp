#pragma once
#include "Injector/Graphics/Window.hpp"

#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace Injector
{
	class GlWindow : public Window
	{
	protected:
		bool gles;
		
		static GLFWwindow* createWindow(
			bool gles,
			const std::string& title,
			const IntVector2& size);
	public:	
		GlWindow(bool gles = false,
			const std::string& title = defaultTitle,
			const IntVector2& size = defaultSize);
		virtual ~GlWindow();

		bool isGLES() const noexcept;

		void makeCurrent() noexcept;
		void swapBuffers() noexcept;

		void onFramebufferResize(const IntVector2& size) override;

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
