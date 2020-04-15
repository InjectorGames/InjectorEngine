#include <injector_engine/engine.hpp>
#include <injector_engine/opengl.hpp>
#include <injector_engine/vulkan.hpp>

#undef VULKAN_FOUND

int main()
{
	InjectorEngine::Engine::Initialize();

#ifdef VULKAN_FOUND
	InjectorEngine::Vulkan::Initialize();
	//Injector::Engine::AddWindow(std::make_shared<Injector::VkWindow>());
	InjectorEngine::Engine::BeginUpdate();
	InjectorEngine::Vulkan::Terminate();
#else
	auto window = new InjectorEngine::GlWindow(true);
	InjectorEngine::Engine::AddWindow(window);

	auto graphics = new InjectorEngine::GlGraphics(window);
	window->AddSystem(graphics);

	InjectorEngine::Engine::Update();

	window->RemoveSystem(graphics);
	delete graphics;

	InjectorEngine::Engine::RemoveWindow(window);
	delete window;
#endif // VULKAN_FOUND

	InjectorEngine::Engine::Terminate();
	return 0;
}
