#pragma once
#include <injector/mathematics/int_vector2.hpp>

#include <string>
#include <memory>
#include <cstdint>

#include <SDL.h>

namespace INJECTOR_NAMESPACE
{
	class Window
	{
	protected:
		SDL_Window* window;
	public:
		static const std::string defaultTitle;
		static const IntVector2 defaultPosition;
		static const IntVector2 defaultSize;
		static const uint32_t defaultFlags;

		Window(const std::string& title = defaultTitle,
			const IntVector2& position = defaultPosition,
			const IntVector2& size = defaultSize,
			uint32_t flags = defaultFlags);
		virtual ~Window();

		virtual void beginRender();
		virtual void endRender();
		virtual void onResize(const IntVector2& size);

		uint32_t getID() const noexcept;
		uint32_t getFlags() const noexcept;
		bool getShown() const noexcept;
		IntVector2 getSize() const noexcept;

		void hide() noexcept;
		void show() noexcept;
		void minimize() noexcept;
		void maximize() noexcept;
	};

	using WindowHandle = std::shared_ptr<Window>;
}
