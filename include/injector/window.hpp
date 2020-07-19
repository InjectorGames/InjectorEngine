#pragma once
#include <injector/int_vector2.hpp>

#include <string>
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

		virtual void update();

		uint32_t getID() noexcept;
		uint32_t getFlags() noexcept;

		void hide() noexcept;
	};
}
