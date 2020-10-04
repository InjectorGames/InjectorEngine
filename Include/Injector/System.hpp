#pragma once

namespace Injector
{
	class System
	{
	 public:
		// Destroy system
		virtual ~System() = default;
		// Executes on each update cycle
		virtual void update() = 0;
	};
}
