#pragma once

namespace Injector
{
	// Entity Component System component
	struct EcsComponent
	{
		// Creates a new component
		EcsComponent() = default;
		// Deleted component copy constructor
		EcsComponent(const EcsComponent& component) = delete;
		// Deleted component move constructor
		EcsComponent(EcsComponent&& component) = delete;
		// Destroys component
		virtual ~EcsComponent() = default;
	};
}
