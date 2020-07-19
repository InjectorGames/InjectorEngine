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

		Manager& getManager() const noexcept;

		virtual void preUpdate();
		virtual void update();
		virtual void postUpdate();
	};
}
