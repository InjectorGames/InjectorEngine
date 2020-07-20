#pragma once
#include <injector/defines.hpp>
#include <memory>

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
		virtual void update();
	};

	using SystemHandle = std::shared_ptr<System>;
}
