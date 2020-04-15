#include <injector_engine/opengl.hpp>

namespace InjectorEngine
{
	GlGraphics::GlGraphics(GlWindow* window, int updateQueue) : System(updateQueue)
	{
		if (!window->IsES())
		{
			auto colorVert = GlShader(ShaderType::Vertex, "resources/shaders/color.vert", true);
			auto colorFrag = GlShader(ShaderType::Fragment, "resources/shaders/color.frag", true);
			materialColor = new GlMaterialColor(colorVert.shader, colorFrag.shader);
		}
		else
		{
			auto colorVert = GlShader(ShaderType::Vertex, "resources/shaders/es_color.vert", true);
			auto colorFrag = GlShader(ShaderType::Fragment, "resources/shaders/es_color.frag", true);
			materialColor = new GlMaterialColor(colorVert.shader, colorFrag.shader);
		}

		//auto& registry = window->GetRegistry();
		//auto camera = registry.create();
		//registry.assign<Transform>(camera);
		//registry.assign<Camera>(camera);
	}
	GlGraphics::~GlGraphics()
	{
		if (materialColor)
		{
			delete materialColor;
			materialColor = nullptr;
		}
	}

	void GlGraphics::OnUpdate(Window* window)
	{
		auto _window = window->GetWindow();
		glfwMakeContextCurrent(_window);

		gl::glClear(gl::ClearBufferMask::GL_COLOR_BUFFER_BIT | gl::ClearBufferMask::GL_DEPTH_BUFFER_BIT | gl::ClearBufferMask::GL_STENCIL_BUFFER_BIT | gl::ClearBufferMask::GL_ACCUM_BUFFER_BIT);

		//auto& registry = window->GetRegistry();
		//auto cameraView = registry.view<Camera, Transform>();

		//for (auto cameraEntity : cameraView)
		//{
			//auto& camera = cameraView.get<Camera>(cameraEntity);


		//}

		glfwSwapBuffers(_window);
	}
}
