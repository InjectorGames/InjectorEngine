#pragma once

namespace Injector
{
	// Entity Component System component structure
	struct EcsComponent
	{
		// Creates a new ECS component
		EcsComponent() = default;
		// Destroys ECS component
		virtual ~EcsComponent() = default;
	};
}
