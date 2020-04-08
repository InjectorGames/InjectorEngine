#include <injector_engine.hpp>

int main()
{
	Injector::Engine::Initialize();
	Injector::Vulkan::Initialize();

	// Add systems here
	Injector::Engine::AddWindow(std::make_shared<Injector::VulkanWindow>());
	Injector::Engine::BeginUpdate();
	Injector::Engine::EndUpdate();

	Injector::Vulkan::Terminate();
	Injector::Engine::Terminate();
	return 0;
}

// TODO: Try to automativcaly load best graphics API on engine initialize
