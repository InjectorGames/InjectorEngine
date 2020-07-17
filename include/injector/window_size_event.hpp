#pragma once
#include <inject/defines.hpp>
#include <inject/glm_defines.hpp>
#include <entityx/entityx.h>

namespace INJECT_NAMESPACE
{
	struct WindowSizeEvent final :
		public entityx::Event<WindowSizeEvent>
	{
		const glm::ivec2& size;
		const glm::ivec2& deltaSize;

		WindowSizeEvent(
			const glm::ivec2& _size,
			const glm::ivec2& _deltaSize) :
			size(_size),
			deltaSize(_deltaSize)
		{}
	};
}
