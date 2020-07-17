#include <injector/manager.hpp>
//#include <injector/gl/editor_window.hpp>

using namespace INJECTOR_NAMESPACE;

int main(int argc, char* args[])
{
	auto manager = Manager(0);
	auto entity = manager.createEntity();
	entity.addComponent<int>();

	/*try
	{
		inject::Engine::initialize(SDL_INIT_EVERYTHING, false);

		inject::Engine::addManager(
			std::make_shared<inject::GlEditorWindow>());
		inject::Engine::update();

		inject::Engine::terminate();
		return 0;
	}
	catch (const std::exception& exception)
	{
		inject::Engine::logCritical(exception.what());
		throw exception;
	}*/

	return 0;
}
