#pragma once
#include "Injector/ECS/EcsEntity.hpp"

namespace Injector
{
	// Entity Component System system class
	class EcsSystem
	{
	 public:
		// Destroys ECS system
		virtual ~EcsSystem() = default;

		// Executes on each update cycle
		virtual void onUpdate() = 0;

		// Returns true if entity removed from the system
		virtual bool removeEntity(
			const std::shared_ptr<EcsEntity>& entity) = 0;
	};
}
