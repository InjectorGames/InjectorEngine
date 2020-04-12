#include <injector_engine.hpp>

int main()
{
	Injector::Engine::Initialize();

#ifdef  VULKAN_FOUND
	Injector::Vulkan::Initialize();
#endif // VULKAN_FOUND

	// Add systems here
	
	//Injector::Engine::AddWindow(std::make_shared<Injector::VkWindow>());
	//Injector::Engine::AddWindow(std::make_shared<Injector::GlWindow>());
	Injector::Engine::AddWindow(std::make_shared<Injector::GlesWindow>());

	/*
	try
	{
		Injector::Engine::AddWindow(std::make_shared<Injector::GlWindow>());
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << "\nTrying to create OpenGL ES window...\n";
		Injector::Engine::AddWindow(std::make_shared<Injector::GlesWindow>());
	}
	*/

	auto shader = new Injector::GlShader("resources/shaders/color.vert", Injector::Shader::Type::Vertex);
	delete shader;

	Injector::Engine::BeginUpdate();
	Injector::Engine::EndUpdate();

#ifdef  VULKAN_FOUND
	Injector::Vulkan::Terminate();
#endif // VULKAN_FOUND

	Injector::Engine::Terminate();
	return 0;
}
