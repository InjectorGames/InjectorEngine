#include <injector/engine.hpp>
#include <injector/window_system.hpp>
//#include <injector/gl/editor_window.hpp>

using namespace INJECTOR_NAMESPACE;

int main(int argc, char* args[])
{
	Engine::initializeVideo();
	Engine::initializeEngine();

	auto manager = Engine::createManager<Manager>();
	auto windowSystem = manager->createSystem<WindowSystem>();
	auto window = manager->createEntity();
	windowSystem->createWindow(window);

	Engine::startUpdateLoop();
	Engine::terminateEngine();
	return 0;
}
