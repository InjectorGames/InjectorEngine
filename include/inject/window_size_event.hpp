#pragma once
#include <entityx/entityx.h>
#include <glm/glm.hpp>

namespace inject
{
	struct WindowSizeEvent final : public entityx::Event<WindowSizeEvent>
	{
		const glm::ivec2& size;
		const glm::ivec2& deltaSize;

		WindowSizeEvent(const glm::ivec2& _size, const glm::ivec2& _deltaSize) :
			size(_size),
			deltaSize(_deltaSize)
		{}
	};
}
