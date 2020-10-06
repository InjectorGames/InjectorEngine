#pragma once

namespace Injector
{
	struct Component
	{
		// Creates a new component
		Component() = default;
		// Deleted component copy constructor
		Component(const Component& component) = delete;
		// Deleted component move constructor
		Component(Component&& component) = delete;
		// Destroys component
		virtual ~Component() = default;
	};
}
