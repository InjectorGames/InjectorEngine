

//#include <injector_engine/engine.hpp>
//#include <injector_engine/opengl.hpp>
//#include <injector_engine/vulkan.hpp>

#undef VULKAN_FOUND

int main()
{
	//bgfx::Init init = {};
	//init.type = bgfx::RendererType::Count;
	//init.vendorId = BGFX_PCI_ID_NONE;
	//init.deviceId = 0;
	//init.debug = true;
	//init.profile = true;
	//init.platformData.

	//f (bgfx::init(init))
	//	throw "Failed to initialize bgfx.";

	/*
	InjectorEngine::Engine::Initialize();

#ifdef VULKAN_FOUND
	InjectorEngine::Vulkan::Initialize();
	//Injector::Engine::AddWindow(std::make_shared<Injector::VkWindow>());
	//InjectorEngine::Engine::BeginUpdate();
	InjectorEngine::Vulkan::Terminate();
#else
	auto window = InjectorEngine::Engine::InstantiateWindow<InjectorEngine::GlWindow>();
	auto systems = window->GetSystems();
	systems->add<InjectorEngine::FirstPersonSystem>(window);
	systems->add<InjectorEngine::TransformSystem>();
	systems->add<InjectorEngine::CameraSystem>(window);
	systems->add<InjectorEngine::GlGraphicsSystem>(window);
	systems->configure();

	InjectorEngine::Engine::Update();
#endif // VULKAN_FOUND

	InjectorEngine::Engine::Terminate();
	*/
	return 0;
}
