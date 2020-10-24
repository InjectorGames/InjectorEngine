#include "Injector/Graphics/SimSkyEcsSystem.hpp"
#include "Injector/Exception/NullException.hpp"

namespace Injector
{
	SimSkyEcsSystem::SimSkyEcsSystem(
		const std::shared_ptr<GpuWindow>& _window) :
		window(_window)
	{
		if(!window)
		{
			throw NullException(
				std::string(typeid(SimSkyEcsSystem).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"window");
		}
	}

	void SimSkyEcsSystem::update()
	{

	}
}
