#pragma once
#include "Injector/Manager.hpp"
#include "Injector/Graphics/Mesh.hpp"
#include "Injector/Graphics/Pipeline.hpp"
#include "Injector/Graphics/MouseButton.hpp"
#include "Injector/Graphics/RenderSystem.hpp"
#include "Injector/Graphics/CameraSystem.hpp"
#include "Injector/Graphics/ColorPipeline.hpp"
#include "Injector/Graphics/DiffusePipeline.hpp"

#include "SDL.h"

#include <string>
#include <cstdint>

namespace Injector::Graphics
{
	class Window : public Manager
	{
	protected:
		SDL_Window* window;
		Vector3 translation;
		Vector3 rotation;
		IntVector2 mouseMotion;
	public:
		static const string defaultTitle;
		static const IntVector2 defaultPosition;
		static const IntVector2 defaultSize;
		static const uint32_t defaultFlags;

		Window(const string& title = defaultTitle,
			IntVector2 position = defaultPosition,
			IntVector2 size = defaultSize,
			uint32_t flags = defaultFlags);
		virtual ~Window();

		const Vector3& getTranslation() const noexcept;
		const Vector3& getRotation() const noexcept;
		const IntVector2& getMouseMotion() const noexcept;

		void update() override;
		virtual void onResize(IntVector2 size);

		uint32_t getID() const noexcept;
		uint32_t getFlags() const noexcept;
		IntVector2 getSize() const noexcept;
		IntVector2 getMousePosition() const noexcept;
		IntVector2 getGlobalMousePosition() const noexcept;
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

		virtual shared_ptr<CameraSystem> createCameraSystem();
		virtual shared_ptr<RenderSystem> createRenderSystem();

		virtual shared_ptr<Mesh> createMesh(
			size_t indexCount,
			BufferIndex indexType,
			const void* vertexData,
			size_t vertexSize,
			const void* indexData,
			size_t indexSize,
			bool staticUse);

		virtual shared_ptr<ColorPipeline> createColorPipeline();
		virtual shared_ptr<DiffusePipeline> createDiffusePipeline();

		shared_ptr<Mesh> createSquareMeshV(bool staticUse);
		shared_ptr<Mesh> createSquareMeshVN(bool staticUse);
		shared_ptr<Mesh> createCubeMeshV(bool staticUse);
		shared_ptr<Mesh> createCubeMeshVN(bool staticUse);

		static shared_ptr<Window> create(
			const string& title = Window::defaultTitle,
			IntVector2 position = Window::defaultPosition,
			IntVector2 size = Window::defaultSize,
			uint32_t flags = Window::defaultFlags);
	};
}
