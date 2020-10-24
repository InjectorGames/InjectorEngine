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
				"SimSkySystem",
				"SimSkySystem",
				"window");
		}
	}

	void SimSkyEcsSystem::update()
	{

	}
}
