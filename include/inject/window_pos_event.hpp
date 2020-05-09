#pragma once
#include <entityx/entityx.h>
#include <glm/glm.hpp>

namespace inject
{
	struct WindowPosEvent final : public entityx::Event<WindowPosEvent>
	{
		glm::ivec2 position;
		glm::ivec2 deltaPosition;

		WindowPosEvent(const glm::ivec2 _position, const glm::ivec2 _deltaPosition) :
			position(_position),
			deltaPosition(_deltaPosition)
		{}
	};
}
