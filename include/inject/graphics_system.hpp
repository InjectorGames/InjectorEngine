#pragma once
#include <entityx/entityx.h>
#include <bgfx/bgfx.h>

namespace njng
{
	class GraphicsSystem final : public entityx::System<GraphicsSystem>
	{
	public:
		void update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override
		{
			bgfx::touch(0);
			bgfx::frame();
		}
	};
}
