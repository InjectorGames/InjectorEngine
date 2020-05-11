#pragma once
#include <entityx/entityx.h>

namespace starnet
{
	class VoxelSystem final : public entityx::System<VoxelSystem>
	{
	public:
		void update(entityx::EntityManager& entities,
			entityx::EventManager& events,
			entityx::TimeDelta deltaTime) override
		{

		}
	}
}
