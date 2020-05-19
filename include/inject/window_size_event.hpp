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
