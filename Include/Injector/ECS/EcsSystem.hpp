#pragma once

namespace Injector
{
	// Entity Component System system
	class EcsSystem
	{
	 public:
		// Creates a new system
		EcsSystem() = default;
		// Deleted copy constructor
		EcsSystem(const EcsSystem& system) = delete;
		// Deleted move constructor
		EcsSystem(EcsSystem&& system) = delete;
		// Destroys system
		virtual ~EcsSystem() = default;

		// Executes on each update cycle
		virtual void update() = 0;
	};
}
