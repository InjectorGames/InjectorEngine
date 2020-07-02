#include <inject/engine.hpp>
#include <inject/gl/window.hpp>
#include <inject/gl/editor_window.hpp>

int main(int argc, char* args[])
{
	try
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
	}
}
