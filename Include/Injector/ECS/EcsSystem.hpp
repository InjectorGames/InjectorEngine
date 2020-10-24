#pragma once

namespace Injector
{
	// Entity Component System system class
	class EcsSystem
	{
	 public:
		// Creates a new ECS system
		EcsSystem() = default;
		// Deleted ECS system copy constructor
		EcsSystem(const EcsSystem& system) = delete;
		// Deleted ECS system move constructor
		EcsSystem(EcsSystem&& system) = delete;
		// Destroys ECS system
		virtual ~EcsSystem() = default;

		// Executes on each update cycle
		virtual void update() = 0;
	};
}
