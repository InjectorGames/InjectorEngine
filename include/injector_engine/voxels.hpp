#pragma once
#include <injector_engine/engine.hpp>

namespace InjectorEngine
{
	class VoxelSystem : public ecs::System<VoxelSystem>
	{
	public:
		void configure(ecs::EntityManager& entities, ecs::EventManager& events) override
		{
		}

		void update(ecs::EntityManager& entities, ecs::EventManager& events, ecs::TimeDelta deltaTime) override
		{
		}
	};
}
