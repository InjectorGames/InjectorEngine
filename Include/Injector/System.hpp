#pragma once

namespace Injector
{
	class System
	{
	 public:
		virtual ~System() = default;
		virtual void update() = 0;
	};
}
