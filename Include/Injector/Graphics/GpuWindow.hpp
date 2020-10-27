#pragma once
#include "Injector/ECS/EcsManager.hpp"
#include "Injector/Graphics/GpuMesh.hpp"
#include "Injector/Graphics/GpuImage.hpp"
#include "Injector/Graphics/GpuShader.hpp"
#include "Injector/Graphics/ImageData.hpp"
#include "Injector/Graphics/ModelData.hpp"
#include "Injector/Graphics/MouseIcon.hpp"
#include "Injector/Graphics/MouseMode.hpp"
#include "Injector/Graphics/ShaderData.hpp"
#include "Injector/Graphics/MouseButton.hpp"
#include "Injector/Graphics/GpuPipeline.hpp"
#include "Injector/Graphics/ButtonState.hpp"
#include "Injector/Graphics/RenderEcsSystem.hpp"
#include "Injector/Graphics/CameraEcsSystem.hpp"
#include "Injector/Graphics/GpuImageWrap.hpp"
#include "Injector/Graphics/GpuImageFilter.hpp"
#include "Injector/Graphics/KeyboardButton.hpp"
#include "Injector/Graphics/GpuFramebuffer.hpp"

#include <string>
#include <cstdint>

namespace Injector
{
	class GpuWindow : public EcsManager
	{
	 protected:
		GLFWwindow* window;
		GLFWcursor* cursor;
		Vector2 deltaScroll;
		bool isResized;

		static void scrollCallback(
			GLFWwindow* window,
			double x,
			double y);
		static void framebufferSizeCallback(
			GLFWwindow* window,
			int width,
			int height);
	 public:
		static const std::string defaultTitle;
		static const IntVector2 defaultSize;

		explicit GpuWindow(
			GLFWwindow* window);
		virtual ~GpuWindow();

		const Vector2& getDeltaScroll() const noexcept;

		void update() override;

		virtual void onFramebufferResize(
			const IntVector2& size) = 0;

		IntVector2 getSize() const noexcept;
		IntVector2 getFramebufferSize() const noexcept;
		IntVector2 getPosition() const noexcept;
		Vector2 getMousePosition() const noexcept;
		ButtonState getMouseButton(
			MouseButton button) const noexcept;
		ButtonState getKeyboardButton(
			KeyboardButton button) const noexcept;

		void setSize(const IntVector2& size);
		void setSizeLimits(const IntVector2& min, const IntVector2& max);
		void setPosition(const IntVector2& position);
		void setTitle(const std::string& title);
		void setIcons(const std::vector<std::shared_ptr<ImageData>>& icons);
		void setMouseMode(MouseMode mode);
		void setMouseIcon(MouseIcon icon);
		void setMouseIcon(
			const std::shared_ptr<ImageData>& icon,
			const IntVector2& hotspot);
		void setResizable(bool resizable);
		void setDecorated(bool decorated);

		bool isFocused() const noexcept;
		bool isMinimized() const noexcept;
		bool isVisible() const noexcept;
		bool isResizable() const noexcept;
		bool isDecorated() const noexcept;

		void hide() noexcept;
		void show() noexcept;
		void minimize() noexcept;
		void maximize() noexcept;
		void focus() noexcept;
		void requestAttention() noexcept;

		virtual std::shared_ptr<CameraEcsSystem> createCameraSystem() = 0;
		virtual std::shared_ptr<RenderEcsSystem> createRenderSystem(
			const std::shared_ptr<GpuWindow>& window) = 0;

		virtual std::shared_ptr<GpuBuffer> createBuffer(
			size_t size,
			GpuBufferType type,
			bool mappable,
			const void* data) = 0;
		virtual std::shared_ptr<GpuMesh> createMesh(
			size_t indexCount,
			const std::shared_ptr<GpuBuffer>& vertexBuffer,
			const std::shared_ptr<GpuBuffer>& indexBuffer) = 0;
		virtual std::shared_ptr<ShaderData> readShaderData(
			const std::string& filePath) = 0;
		virtual std::shared_ptr<GpuShader> createShader(
			GpuShaderStage stage,
			const std::shared_ptr<ShaderData>& data) = 0;
		virtual std::shared_ptr<GpuImage> createImage(
			GpuImageType type,
			GpuImageFormat format,
			const IntVector3& size,
			bool useMipmap,
			const std::shared_ptr<ImageData>& data) = 0;
		virtual std::shared_ptr<GpuFramebuffer> createFramebuffer(
			const std::shared_ptr<GpuImage>& colorImage,
			const std::shared_ptr<GpuImage>& depthImage,
			const std::shared_ptr<GpuImage>& stencilImage) = 0;

		virtual std::shared_ptr<GpuPipeline> createColorPipeline(
			GpuDrawMode drawMode,
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader,
			const Vector4& color) = 0;
		virtual std::shared_ptr<GpuPipeline> createColorColorPipeline(
			GpuDrawMode drawMode,
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader,
			const Vector4& color) = 0;
		virtual std::shared_ptr<GpuPipeline> createDiffusePipeline(
			GpuDrawMode drawMode,
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader,
			const Vector4& objectColor,
			const Vector4& ambientColor,
			const Vector4& lightColor,
			const Vector3& lightDirection) = 0;
		virtual std::shared_ptr<GpuPipeline> createImageDiffusePipeline(
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
			const Vector2& imageOffset) = 0;
		virtual std::shared_ptr<GpuPipeline> createSkyPipeline(
			GpuDrawMode drawMode,
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader) = 0;

		std::shared_ptr<GpuMesh> createMesh(
			const std::vector<float>& vertices,
			bool mappableVertices,
			const std::vector<uint32_t>& indices,
			bool mappableIndices);

		std::shared_ptr<GpuImage> createImage(
			GpuImageFormat format,
			int size,
			bool useMipmap,
			const std::shared_ptr<ImageData>& data = nullptr);
		std::shared_ptr<GpuImage> createImage(
			GpuImageFormat format,
			const IntVector2& size,
			bool useMipmap,
			const std::shared_ptr<ImageData>& data = nullptr);
		std::shared_ptr<GpuImage> createImage(
			GpuImageFormat format,
			const IntVector3& size,
			bool useMipmap,
			const std::shared_ptr<ImageData>& data = nullptr);

		std::shared_ptr<GpuPipeline> createColorPipeline(
			GpuDrawMode drawMode,
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader);
		std::shared_ptr<GpuPipeline> createColorColorPipeline(
			GpuDrawMode drawMode,
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader);
		std::shared_ptr<GpuPipeline> createDiffusePipeline(
			GpuDrawMode drawMode,
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader);
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
			const std::shared_ptr<GpuImage>& image);

		static std::shared_ptr<GpuWindow> create(
			const std::string& title = defaultTitle,
			const IntVector2& size = defaultSize);
	};
}
