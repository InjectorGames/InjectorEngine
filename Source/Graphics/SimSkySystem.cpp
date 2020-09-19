#include "Injector/Graphics/SimSkySystem.hpp"
#include "Injector/Exception/NullException.hpp"

namespace Injector
{
	SimSkySystem::SimSkySystem(
		const std::shared_ptr<Window>& _window) :
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
	SimSkySystem::~SimSkySystem()
	{
	}

	void SimSkySystem::update()
	{

	}
}
