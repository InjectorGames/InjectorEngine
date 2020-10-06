#pragma once

namespace Injector
{
	class System
	{
	 public:
		// Creates a new system
		System() = default;
		// Deleted copy constructor
		System(const System& system) = delete;
		// Deleted move constructor
		System(System&& system) = delete;
		// Destroys system
		virtual ~System() = default;

		// Executes on each update cycle
		virtual void update() = 0;
	};
}
