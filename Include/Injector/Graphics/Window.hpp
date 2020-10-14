#pragma once
#include "Injector/ECS/Manager.hpp"
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
#include "Injector/Graphics/RenderSystem.hpp"
#include "Injector/Graphics/CameraSystem.hpp"
#include "Injector/Graphics/KeyboardButton.hpp"
#include "Injector/Graphics/GpuFramebuffer.hpp"
#include "Injector/Graphics/Pipeline/ColorGpuPipeline.hpp"
#include "Injector/Graphics/Pipeline/SimulatedSkyGpuPipeline.hpp"
#include "Injector/Graphics/Pipeline/TextureDiffuseGpuPipeline.hpp"

#include <string>
#include <cstdint>

namespace Injector
{
	class Window : public Manager
	{
	 protected:
		GLFWwindow* window;
		GLFWcursor* cursor;
		Vector2 deltaScroll;
		bool isResized;

		static void scrollCallback(
			GLFWwindow* window, double x, double y);
		static void framebufferSizeCallback(
			GLFWwindow* window, int width, int height);
	 public:
		static const std::string defaultTitle;
		static const IntVector2 defaultSize;

		explicit Window(
			GLFWwindow* window);
		virtual ~Window();

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

		virtual std::shared_ptr<CameraSystem> createCameraSystem() = 0;
		virtual std::shared_ptr<RenderSystem> createRenderSystem() = 0;

		virtual std::shared_ptr<GpuBuffer> createBuffer(
			size_t size,
			GpuBufferType type,
			bool mappable,
			const void* data) = 0;
		virtual std::shared_ptr<GpuMesh> createMesh(
			size_t indexCount,
			GpuBufferIndex indexType,
			const std::shared_ptr<GpuBuffer>& vertexBuffer,
			const std::shared_ptr<GpuBuffer>& indexBuffer) = 0;
		virtual std::shared_ptr<ShaderData> readShaderData(
			const std::string& filePath) = 0;
		virtual std::shared_ptr<GpuShader> createShader(
			GpuShaderStage stage,
			const std::shared_ptr<ShaderData>& data) = 0;
		virtual std::shared_ptr<GpuImage> createImage(
			GpuImageType type,
			const IntVector3& size,
			GpuImageFormat format,
			GpuImageFilter minFilter,
			GpuImageFilter magFilter,
			GpuImageWrap wrapU,
			GpuImageWrap wrapV,
			GpuImageWrap wrapW,
			bool useMipmap,
			const std::shared_ptr<ImageData>& data) = 0;
		virtual std::shared_ptr<GpuFramebuffer> createFramebuffer(
				const std::shared_ptr<GpuImage>& colorImage,
				const std::shared_ptr<GpuImage>& depthImage,
				const std::shared_ptr<GpuImage>& stencilImage) = 0;

		virtual std::shared_ptr<ColorGpuPipeline> createColorPipeline(
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader) = 0;
		virtual std::shared_ptr<ColorGpuPipeline> createColColorPipeline(
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader) = 0;
		virtual std::shared_ptr<DiffuseGpuPipeline> createDiffusePipeline(
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader) = 0;
		virtual std::shared_ptr<TextureDiffuseGpuPipeline> createTexDiffusePipeline(
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader,
			const std::shared_ptr<GpuImage>& texture) = 0;
		virtual std::shared_ptr<SimulatedSkyGpuPipeline> createSkyPipeline(
			const std::shared_ptr<GpuShader>& vertexShader,
			const std::shared_ptr<GpuShader>& fragmentShader) = 0;

		std::shared_ptr<GpuMesh> createMesh(
			const std::vector<float>& vertices,
			bool mappableVertices,
			const std::vector<uint16_t>& indices,
			bool mappableIndices);
		std::shared_ptr<GpuMesh> createMesh(
			const std::vector<float>& vertices,
			bool mappableVertices,
			const std::vector<uint32_t>& indices,
			bool mappableIndices);

		std::shared_ptr<GpuImage> createImage(
			int size,
			GpuImageFormat format,
			GpuImageFilter minFilter,
			GpuImageFilter magFilter,
			GpuImageWrap wrapU,
			bool useMipmap,
			const std::shared_ptr<ImageData>& data = nullptr);
		std::shared_ptr<GpuImage> createImage(
			const IntVector2& size,
			GpuImageFormat format,
			GpuImageFilter minFilter,
			GpuImageFilter magFilter,
			GpuImageWrap wrapU,
			GpuImageWrap wrapV,
			bool useMipmap,
			const std::shared_ptr<ImageData>& data = nullptr);
		std::shared_ptr<GpuImage> createImage(
			const IntVector3& size,
			GpuImageFormat format,
			GpuImageFilter minFilter,
			GpuImageFilter magFilter,
			GpuImageWrap wrapU,
			GpuImageWrap wrapV,
			GpuImageWrap wrapW,
			bool useMipmap,
			const std::shared_ptr<ImageData>& data = nullptr);

		static std::shared_ptr<Window> create(
			const std::string& title = defaultTitle,
			const IntVector2& size = defaultSize);
	};
}
