#pragma once
#include <injector/defines.hpp>

namespace INJECTOR_NAMESPACE
{
	class Manager;

	class System
	{
	protected:
		Manager& manager;
	public:
		System(Manager& manager);
		virtual ~System();

		virtual void initialize() = 0;
		virtual void terminate() = 0;
		virtual void update() = 0;
	};
}
