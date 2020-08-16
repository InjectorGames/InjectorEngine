#pragma once
#include <injector/manager.hpp>
#include <injector/graphics/mesh.hpp>
#include <injector/graphics/shader.hpp>
#include <injector/graphics/pipeline.hpp>
#include <injector/graphics/mouse_button.hpp>
#include <injector/graphics/render_system.hpp>
#include <injector/graphics/camera_system.hpp>

#include <SDL.h>

#include <string>
#include <cstdint>

namespace INJECTOR_NAMESPACE
{
	class Window : public Manager
	{
	protected:
		SDL_Window* window;
		IntVector2 mouseMotion;
	public:
		static const std::string defaultTitle;
		static const IntVector2 defaultPosition;
		static const IntVector2 defaultSize;
		static const uint32_t defaultFlags;

		Window(const std::string& title = defaultTitle,
			IntVector2 position = defaultPosition,
			IntVector2 size = defaultSize,
			uint32_t flags = defaultFlags);
		virtual ~Window();

		void update() override;
		virtual void onResize(IntVector2 size);

		uint32_t getID() const noexcept;
		uint32_t getFlags() const noexcept;
		IntVector2 getSize() const noexcept;
		IntVector2 getMousePosition() const noexcept;
		IntVector2 getGlobalMousePosition() const noexcept;
		IntVector2 getMouseMotion() const noexcept;
		uint32_t getMouseButtons() const noexcept;
		uint32_t getGlobalMouseButtons() const noexcept;
		void getMouseState(IntVector2& position, uint32_t& buttons) const noexcept;
		void getGlobalMouseState(IntVector2& position, uint32_t& buttons) const noexcept;
		bool isHidden() const noexcept;
		bool isShown() const noexcept;
		bool isMinimized() const noexcept;
		bool isMaximized() const noexcept;
		bool isResizable() const noexcept;

		void hide() noexcept;
		void show() noexcept;
		void minimize() noexcept;
		void maximize() noexcept;
		void setResizable(bool resizable) noexcept;
		bool setMouseMode(bool realtive) noexcept;

		virtual CameraSystemHandle createCameraSystem();
		virtual RenderSystemHandle createRenderSystem();
		virtual PipelineHandle createColorPipeline();
		virtual MeshHandle createSquareMesh();
		virtual MeshHandle createCubeMesh();

		static std::shared_ptr<Window> create(
			const std::string& title = Window::defaultTitle,
			IntVector2 position = Window::defaultPosition,
			IntVector2 size = Window::defaultSize,
			uint32_t flags = Window::defaultFlags);
	};

	using WindowHandle = std::shared_ptr<Window>;
}
