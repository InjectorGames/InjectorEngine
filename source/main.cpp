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
	//InjectorEngine::Engine::BeginUpdate();
	InjectorEngine::Vulkan::Terminate();
#else
	auto window = new InjectorEngine::GlWindow();
	InjectorEngine::Engine::AddWindow(window);

	auto systems = window->GetSystems();
	systems->add<InjectorEngine::TransformSystem>();
	systems->add<InjectorEngine::CameraSystem>();
	systems->add<InjectorEngine::GlGraphicsSystem>(window);
	systems->configure();

	InjectorEngine::Engine::Update();

	InjectorEngine::Engine::RemoveWindow(window);
	delete window;
#endif // VULKAN_FOUND

	InjectorEngine::Engine::Terminate();
	return 0;
}
