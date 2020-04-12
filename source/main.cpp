#include <injector_engine.hpp>

int main()
{
	Injector::Engine::Initialize();

#ifdef  VULKAN_FOUND
	Injector::Vulkan::Initialize();
#endif // VULKAN_FOUND

	// Add systems here
	
	//Injector::Engine::AddWindow(std::make_shared<Injector::VulkanWindow>());
	Injector::Engine::AddWindow(std::make_shared<Injector::OpenGLWindow>());

	Injector::Engine::BeginUpdate();
	Injector::Engine::EndUpdate();

#ifdef  VULKAN_FOUND
	Injector::Vulkan::Terminate();
#endif // VULKAN_FOUND

	Injector::Engine::Terminate();
	return 0;
}
