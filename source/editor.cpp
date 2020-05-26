#include <inject/engine.hpp>
#include <inject/gl_window.hpp>
#include <inject/gl_editor_window.hpp>

int main(int argc, char* args[])
{
	try
	{
		inject::Engine::initialize();
		inject::Engine::addManager(std::make_shared<inject::GlEditorWindow>());
		inject::Engine::update();
		inject::Engine::terminate();
		return 0;
	}
	catch (const std::exception& exception)
	{
		std::cerr << exception.what() << std::endl;
		throw exception;
	}
}
