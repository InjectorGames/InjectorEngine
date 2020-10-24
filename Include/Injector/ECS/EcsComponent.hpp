#pragma once

namespace Injector
{
	// Entity Component System component structure
	struct EcsComponent
	{
		// Creates a new ECS component
		EcsComponent() = default;
		// Deleted ECS component copy constructor
		EcsComponent(const EcsComponent& component) = delete;
		// Deleted ECS component move constructor
		EcsComponent(EcsComponent&& component) = delete;
		// Destroys ECS component
		virtual ~EcsComponent() = default;
	};
}
