#pragma once
#include <injector/defines.hpp>
#include <memory>

namespace INJECTOR_NAMESPACE
{
	class Manager;

	class System
	{
	public:
		virtual ~System();
		virtual void update();
	};

	using SystemHandle = std::shared_ptr<System>;
}
