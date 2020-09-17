#pragma once
#include "Injector/Manager.hpp"
#include "Injector/Graphics/Mesh.hpp"
#include "Injector/Graphics/Image.hpp"
#include "Injector/Graphics/Texture.hpp"
#include "Injector/Graphics/Pipeline.hpp"
#include "Injector/Graphics/MouseIcon.hpp"
#include "Injector/Graphics/MouseMode.hpp"
#include "Injector/Graphics/MouseButton.hpp"
#include "Injector/Graphics/ButtonState.hpp"
#include "Injector/Graphics/KeyboardButton.hpp"
#include "Injector/Graphics/RenderSystem.hpp"
#include "Injector/Graphics/CameraSystem.hpp"
#include "Injector/Graphics/ColorPipeline.hpp"
#include "Injector/Graphics/TexDiffusePipeline.hpp"

#include <string>
#include <cstdint>

namespace Injector
{
	class Window : public Manager
	{
	protected:
		GLFWwindow* window;
		Vector2 deltaScroll;
		bool isResized;

		static void scrollCallback(GLFWwindow* window, double x, double y);
		static void cursorPositionCallback(GLFWwindow* window, double x, double y);
		static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	public:
		static const std::string defaultTitle;
		static const IntVector2 defaultSize;

		Window(GLFWwindow* window);
		virtual ~Window();

		const Vector2& getDeltaScroll() const noexcept;

		void update() override;
		virtual void onFramebufferResize(const IntVector2& size);

		IntVector2 getSize() const noexcept;
		IntVector2 getFramebufferSize() const noexcept;
		IntVector2 getPosition() const noexcept;
		Vector2 getMousePosition() const noexcept;
		ButtonState getMouseButton(MouseButton button) const noexcept;
		ButtonState getKeyboardButton(KeyboardButton button) const noexcept;

		void setSize(const IntVector2& size);
		void setSizeLimits(const IntVector2& min, const IntVector2& max);
		void setPosition(const IntVector2& position);	
		void setTitle(const std::string& title);
		void setIcons(const std::vector<std::shared_ptr<Image>>& icons);
		void setMouseMode(MouseMode mode);
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

		virtual std::shared_ptr<CameraSystem> createCameraSystem();
		virtual std::shared_ptr<RenderSystem> createRenderSystem();

		virtual std::shared_ptr<Buffer> createBuffer(
			size_t size,
			BufferType type,
			bool mappable,
			const void* data);
		virtual std::shared_ptr<Mesh> createMesh(
			size_t indexCount,
			BufferIndex indexType,
			const std::shared_ptr<Buffer>& vertexBuffer,
			const std::shared_ptr<Buffer>& indexBuffer);
		virtual std::shared_ptr<Texture> createTexture(
        	int size,
        	TextureFormat format,
        	TextureFilter minFilter,
    		TextureFilter magFilter,
    		TextureWrap wrapU,
        	bool useMipmap,
			const std::shared_ptr<Image>& image);
		virtual std::shared_ptr<Texture> createTexture(
        	const IntVector2& size,
        	TextureFormat format,
        	TextureFilter minFilter,
    		TextureFilter magFilter,
    		TextureWrap wrapU,
        	TextureWrap wrapV,
        	bool useMipmap,
			const std::shared_ptr<Image>& image);
		virtual std::shared_ptr<Texture> createTexture(
        	const IntVector3& size,
        	TextureFormat format,
        	TextureFilter minFilter,
    		TextureFilter magFilter,
    		TextureWrap wrapU,
        	TextureWrap wrapV,
        	TextureWrap wrapW,
        	bool useMipmap,
			const std::shared_ptr<Image>& image);

		virtual std::shared_ptr<ColorPipeline> createColorPipeline();
		virtual std::shared_ptr<ColorPipeline> createColColorPipeline();
		virtual std::shared_ptr<DiffusePipeline> createDiffusePipeline();
		virtual std::shared_ptr<TexDiffusePipeline> createTexDiffusePipeline(
			const std::shared_ptr<Texture>& texture);

		std::shared_ptr<Mesh> createSquareMeshV(bool mappable);
		std::shared_ptr<Mesh> createSquareMeshVN(bool mappable);
		std::shared_ptr<Mesh> createSquareMeshVT(bool mappable);
		std::shared_ptr<Mesh> createSquareMeshVNT(bool mappable);
		std::shared_ptr<Mesh> createCubeMeshV(bool mappable);
		std::shared_ptr<Mesh> createCubeMeshVN(bool mappable);
		std::shared_ptr<Mesh> createCubeMeshVT(bool mappable);
		std::shared_ptr<Mesh> createCubeMeshVNT(bool mappable);

		static std::shared_ptr<Window> create(
			const std::string& title = defaultTitle,
			const IntVector2& size = defaultSize);
	};
}
