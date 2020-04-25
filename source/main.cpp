
#include <injector_engine/engine.hpp>
//#include <injector_engine/opengl.hpp>
//#include <injector_engine/vulkan.hpp>

#undef VULKAN_FOUND

namespace Test
{
	class Application : entry::AppI
	{
		public:
		Application(const char* _name, const char* _description, const char* _url) :
			entry::AppI(_name, _description, _url)
		{}
		~Application() override
		{}

		void init(int32_t _argc, const char* const* _argv, uint32_t _width, uint32_t _height) override
		{
			/*
			Args args(_argc, _argv);

			m_width = _width;
			m_height = _height;
			m_debug = BGFX_DEBUG_TEXT;
			m_reset = BGFX_RESET_VSYNC;
			*/

			bgfx::Init init = {};
			init.type = bgfx::RendererType::Count;
			init.vendorId = BGFX_PCI_ID_NONE;
			init.debug = true;
			init.profile = true;
			init.resolution.width = 800;
			init.resolution.height = 600;
			init.resolution.reset = BGFX_RESET_VSYNC;

			if (bgfx::init(init))
				throw "Failed to initialize bgfx.";

			// Set view 0 clear state.
			bgfx::setViewClear(0
				, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH
				, 0x303030ff
				, 1.0f
				, 0
			);

			//imguiCreate();
		}

		virtual int shutdown() override
		{
			//imguiDestroy();

			bgfx::shutdown();
			return 0;
		}

		bool update() override
		{
			/*
			if (!entry::processEvents(m_width, m_height, m_debug, m_reset, &m_mouseState))
			{
				imguiBeginFrame(m_mouseState.m_mx
					, m_mouseState.m_my
					, (m_mouseState.m_buttons[entry::MouseButton::Left] ? IMGUI_MBUT_LEFT : 0)
					| (m_mouseState.m_buttons[entry::MouseButton::Right] ? IMGUI_MBUT_RIGHT : 0)
					| (m_mouseState.m_buttons[entry::MouseButton::Middle] ? IMGUI_MBUT_MIDDLE : 0)
					, m_mouseState.m_mz
					, uint16_t(m_width)
					, uint16_t(m_height)
				);

				showExampleDialog(this);

				imguiEndFrame();

				// Set view 0 default viewport.
				bgfx::setViewRect(0, 0, 0, uint16_t(m_width), uint16_t(m_height));

				// This dummy draw call is here to make sure that view 0 is cleared
				// if no other draw calls are submitted to view 0.
				bgfx::touch(0);

				// Use debug font to print information about this example.
				bgfx::dbgTextClear();
				bgfx::dbgTextImage(
					bx::max<uint16_t>(uint16_t(m_width / 2 / 8), 20) - 20
					, bx::max<uint16_t>(uint16_t(m_height / 2 / 16), 6) - 6
					, 40
					, 12
					, s_logo
					, 160
				);
				bgfx::dbgTextPrintf(0, 1, 0x0f, "Color can be changed with ANSI \x1b[9;me\x1b[10;ms\x1b[11;mc\x1b[12;ma\x1b[13;mp\x1b[14;me\x1b[0m code too.");

				bgfx::dbgTextPrintf(80, 1, 0x0f, "\x1b[;0m    \x1b[;1m    \x1b[; 2m    \x1b[; 3m    \x1b[; 4m    \x1b[; 5m    \x1b[; 6m    \x1b[; 7m    \x1b[0m");
				bgfx::dbgTextPrintf(80, 2, 0x0f, "\x1b[;8m    \x1b[;9m    \x1b[;10m    \x1b[;11m    \x1b[;12m    \x1b[;13m    \x1b[;14m    \x1b[;15m    \x1b[0m");

				const bgfx::Stats* stats = bgfx::getStats();
				bgfx::dbgTextPrintf(0, 2, 0x0f, "Backbuffer %dW x %dH in pixels, debug text %dW x %dH in characters."
					, stats->width
					, stats->height
					, stats->textWidth
					, stats->textHeight
				);

				// Advance to next frame. Rendering thread will be kicked to
				// process submitted rendering primitives.
				bgfx::frame();

				return true;
			}
			*/

			return false;
		}
	};
}

int main()
{
	//auto app = Test::Application("Test", "Test", "none");

	bgfx::Init init;
	init.type = bgfx::RendererType::Count;
	init.vendorId = BGFX_PCI_ID_NONE;
	init.resolution.width = 800;
	init.resolution.height = 600;
	init.resolution.reset = BGFX_RESET_VSYNC;

	if (!bgfx::init(init))
		throw "Failed to initialize bgfx.";

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
