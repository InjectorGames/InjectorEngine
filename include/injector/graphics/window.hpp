#pragma once
#include <injector/manager.hpp>
#include <injector/mathematics/int_vector2.hpp>
#include <injector/graphics/mesh.hpp>
#include <injector/graphics/shader.hpp>
#include <injector/graphics/pipeline.hpp>

#include <SDL.h>

#include <string>
#include <cstdint>

namespace INJECTOR_NAMESPACE
{
	class Window : public Manager
	{
	protected:
		SDL_Window* window;
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
		bool isHidden() const noexcept;
		bool isShown() const noexcept;
		bool isMinimized() const noexcept;
		bool isMaximized() const noexcept;
		bool isResizable() const noexcept;

		void hide() noexcept;
		void show() noexcept;
		void minimize() noexcept;
		void maximize() noexcept;
		void setResizable(bool value) noexcept;

		virtual ShaderHandle createShader(ShaderStage stage, const std::string& path);
		virtual PipelineHandle createColorPipeline(
			const std::string& vertexPath, const std::string& fragmentPath);
		virtual MeshHandle createSquareMesh();

		static std::shared_ptr<Window> create(
			const std::string& title = Window::defaultTitle,
			IntVector2 position = Window::defaultPosition,
			IntVector2 size = Window::defaultSize,
			uint32_t flags = Window::defaultFlags);
	};

	using WindowHandle = std::shared_ptr<Window>;
}
