#include <injector_engine.hpp>

int main()
{
	Injector::Engine::Initialize();

#ifdef  VULKAN_FOUND
	Injector::Vulkan::Initialize();
#endif // VULKAN_FOUND

	// Add systems here
	
	//Injector::Engine::AddWindow(std::make_shared<Injector::VulkanWindow>());

	try
	{
		Injector::Engine::AddWindow(std::make_shared<Injector::OpenGLWindow>());
	}
	catch(const std::exception& e)
	{
		std::cout << e.what() << "\nTrying to create OpenGL ES window...\n";
		Injector::Engine::AddWindow(std::make_shared<Injector::OpenGLESWindow>());
	}

	Injector::Engine::BeginUpdate();
	Injector::Engine::EndUpdate();

#ifdef  VULKAN_FOUND
	Injector::Vulkan::Terminate();
#endif // VULKAN_FOUND

	Injector::Engine::Terminate();
	return 0;
}
