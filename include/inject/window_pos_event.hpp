#pragma once
#include <inject/glm_defines.hpp>
#include <entityx/entityx.h>

namespace inject
{
	struct WindowPosEvent final : public entityx::Event<WindowPosEvent>
	{
		const glm::ivec2& position;
		const glm::ivec2& deltaPosition;

		WindowPosEvent(const glm::ivec2& _position, const glm::ivec2& _deltaPosition) :
			position(_position),
			deltaPosition(_deltaPosition)
		{}
	};
}
