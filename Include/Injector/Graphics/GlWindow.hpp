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
		GlWindow(
			bool gles = false,
			const std::string& title = defaultTitle,
			const IntVector2& size = defaultSize);
		virtual ~GlWindow();

		bool isGLES() const noexcept;

		void makeCurrent() noexcept;
		void swapBuffers() noexcept;

		void onFramebufferResize(const IntVector2& size) override;

		std::shared_ptr<CameraSystem> createCameraSystem() override;
		std::shared_ptr<RenderSystem> createRenderSystem() override;

		std::shared_ptr<GpuBuffer> createBuffer(
			size_t size,
			GpuBufferType type,
			bool mappable,
			const void* data) override;
		std::shared_ptr<GpuMesh> createMesh(
			size_t indexCount,
			GpuBufferIndex indexType,
			const std::shared_ptr<GpuBuffer>& vertexBuffer,
			const std::shared_ptr<GpuBuffer>& indexBuffer) override;
		std::shared_ptr<ShaderData> readShaderData(
			const std::string& filePath) override;
		std::shared_ptr<GpuShader> createShader(
			GpuShaderStage stage,
			const std::shared_ptr<ShaderData>& data) override;
		std::shared_ptr<GpuImage> createImage(
			GpuImageType type,
			const IntVector3& size,
			GpuImageFormat format,
			GpuImageFilter minFilter,
			GpuImageFilter magFilter,
			GpuImageWrap wrapU,
			GpuImageWrap wrapV,
			GpuImageWrap wrapW,
			bool useMipmap,
			const std::shared_ptr<ImageData>& data) override;
		std::shared_ptr<GpuFramebuffer> createFramebuffer(
			const std::shared_ptr<GpuImage>& colorImage,
			const std::shared_ptr<GpuImage>& depthImage,
			const std::shared_ptr<GpuImage>& stencilImage) override;

		std::shared_ptr<ColorGpuPipeline> createColorPipeline(
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader) override;
		std::shared_ptr<ColorGpuPipeline> createColColorPipeline(
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader) override;
		std::shared_ptr<DiffuseGpuPipeline> createDiffusePipeline(
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader) override;
		std::shared_ptr<TextureDiffuseGpuPipeline> createTexDiffusePipeline(
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader,
			const std::shared_ptr<GpuImage>& texture) override;
		std::shared_ptr<SimulatedSkyGpuPipeline> createSkyPipeline(
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader) override;
	};
}
