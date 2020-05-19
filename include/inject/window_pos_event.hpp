#pragma once
#include <entityx/entityx.h>

#define GLM_FORCE_CXX17
#define GLM_FORCE_INLINE
#define GLM_FORCE_INTRINSICS
#define GLM_FORCE_LEFT_HANDED
#define GLM_FORCE_ALIGNED_GENTYPES
#define GLM_FORCE_DEFAULT_ALIGNED_GENTYPES
#include <glm/glm.hpp>

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
