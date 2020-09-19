#include "Injector/System.hpp"
#include "Injector/Exception/NotImplementedException.hpp"

namespace Injector
{
	System::~System()
	{
	}
	void System::update()
	{
		throw NotImplementedException(
			"System",
			"update");
	}
}
