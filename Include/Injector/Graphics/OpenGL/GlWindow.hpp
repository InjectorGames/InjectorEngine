#pragma once
#include "Injector/Graphics/Window.hpp"
#include "Injector/Graphics/GlfwDefines.hpp"

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
		explicit GlWindow(
			bool gles = false,
			const std::string& title = defaultTitle,
			const IntVector2& size = defaultSize);

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

		std::shared_ptr<GpuPipeline> createColorPipeline(
			PrimitiveTopology primitiveTopology,
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader,
			const Vector4& color) override;
		std::shared_ptr<GpuPipeline> createColorColorPipeline(
			PrimitiveTopology primitiveTopology,
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader) override;
		std::shared_ptr<GpuPipeline> createDiffusePipeline(
			PrimitiveTopology primitiveTopology,
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader) override;
		std::shared_ptr<GpuPipeline> createImageDiffusePipeline(
			PrimitiveTopology primitiveTopology,
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader,
			const std::shared_ptr<GpuImage>& image) override;
		std::shared_ptr<GpuPipeline> createSkyPipeline(
			PrimitiveTopology primitiveTopology,
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader) override;
	};
}
