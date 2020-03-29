#include <engine.hpp>
#include <vulkan_window.hpp>

int main()
{
	Injector::Engine::Initialize();

	auto window = new Injector::VulkanWindow();
	window->BeginUpdate();
	delete window;

	Injector::Engine::Terminate();
	return 0;
}
