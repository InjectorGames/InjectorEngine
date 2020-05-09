#include <inject/engine.hpp>
#include <inject/gl_window.hpp>
#include <inject/gl_editor_level.hpp>

int main(int argc, char* args[])
{
	try
	{
		inject::Engine::initialize();

		auto window = std::make_shared<inject::GlWindow>();
		window->addLevel(std::make_shared<inject::GlEditorLevel>(0));
		inject::Engine::addWindow(window);

		inject::Engine::update();

		window = nullptr;

		inject::Engine::terminate();
		return 0;
	}
	catch (const std::exception& exception)
	{
		std::cerr << exception.what() << std::endl;
		throw exception;
		return -1;
	}
}
