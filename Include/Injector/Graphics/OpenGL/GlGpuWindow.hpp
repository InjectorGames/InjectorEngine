#pragma once
#include "Injector/Graphics/GpuWindow.hpp"
#include "Injector/Graphics/GlfwDefines.hpp"

#include "GLFW/glfw3.h"

namespace Injector
{
	class GlGpuWindow : public GpuWindow
	{
	 protected:
		bool gles;

		static GLFWwindow* createWindow(
			bool gles,
			const std::string& title,
			const IntVector2& size);
	 public:
		explicit GlGpuWindow(
			bool gles = false,
			const std::string& title = defaultTitle,
			const IntVector2& size = defaultSize);

		bool isGLES() const noexcept;

		void makeCurrent() noexcept;
		void swapBuffers() noexcept;

		void onFramebufferResize(const IntVector2& size) override;

		std::shared_ptr<CameraEcsSystem> createCameraSystem() override;
		std::shared_ptr<RenderEcsSystem> createRenderSystem(
			const std::shared_ptr<GpuWindow>& window) override;

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
			GpuImageFormat format,
			const IntVector3& size,
			bool useMipmap,
			const std::shared_ptr<ImageData>& data) override;
		std::shared_ptr<GpuFramebuffer> createFramebuffer(
			const std::shared_ptr<GpuImage>& colorImage,
			const std::shared_ptr<GpuImage>& depthImage,
			const std::shared_ptr<GpuImage>& stencilImage) override;

		std::shared_ptr<GpuPipeline> createColorPipeline(
			GpuDrawMode drawMode,
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader,
			const Vector4& color) override;
		std::shared_ptr<GpuPipeline> createColorColorPipeline(
			GpuDrawMode drawMode,
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader,
			const Vector4& color) override;
		std::shared_ptr<GpuPipeline> createDiffusePipeline(
			GpuDrawMode drawMode,
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader,
			const Vector4& objectColor,
			const Vector4& ambientColor,
			const Vector4& lightColor,
			const Vector3& lightDirection) override;
		std::shared_ptr<GpuPipeline> createImageDiffusePipeline(
			GpuDrawMode drawMode,
			GpuImageFilter imageMinFilter,
			GpuImageFilter imageMagFilter,
			GpuImageFilter mipmapFilter,
			GpuImageWrap imageWrapU,
			GpuImageWrap imageWrapV,
			GpuImageWrap imageWrapW,
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader,
			const std::shared_ptr<GpuImage>& image,
			const Vector4& objectColor,
			const Vector4& ambientColor,
			const Vector4& lightColor,
			const Vector3& lightDirection,
			const Vector2& imageScale,
			const Vector2& imageOffset) override;
		std::shared_ptr<GpuPipeline> createSkyPipeline(
			GpuDrawMode drawMode,
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader) override;
	};
}
