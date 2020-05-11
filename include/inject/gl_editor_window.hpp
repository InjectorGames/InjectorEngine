#pragma once
#include <inject/config.hpp>
#include <inject/camera_system.hpp>
#include <inject/transform_system.hpp>
#include <inject/free_camera_system.hpp>
#include <inject/gl_window.hpp>
#include <inject/gl_draw_system.hpp>
#include <inject/gl_color_material.hpp>
#include <inject/gl_diffuse_material.hpp>

namespace inject
{
	class GlEditorWindow : public GlWindow
	{
	protected:
		std::shared_ptr<GlColorMaterial> colorMaterial;
		std::shared_ptr<GlDiffuseMaterial> diffuseMaterial;

		std::shared_ptr<GlMesh> squareMesh;
		std::shared_ptr<GlMesh> cubeMesh;
	public:
		GlEditorWindow(const std::string& title = INJECT_WINDOW_NAME + std::string("- Editor (OpenGL)"),
			const glm::ivec2& position = glm::ivec2(SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED),
			const glm::ivec2& size = glm::ivec2(INJECT_WINDOW_WIDTH, INJECT_WINDOW_HEIGHT),
			const uint32_t flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL) :
			GlWindow(title, position, size, flags)
		{
			colorMaterial = std::make_shared<GlColorMaterial>(
				std::make_shared<GlShader>(Shader::Type::Vertex, "resources/shaders/color.vert", true),
				std::make_shared<GlShader>(Shader::Type::Fragment, "resources/shaders/color.frag", true));
			diffuseMaterial = std::make_shared<GlDiffuseMaterial>(
				std::make_shared<GlShader>(Shader::Type::Vertex, "resources/shaders/diffuse.vert", true),
				std::make_shared<GlShader>(Shader::Type::Fragment, "resources/shaders/diffuse.frag", true));

			squareMesh = GlMesh::CreateSquareVN();
			cubeMesh = GlMesh::CreateCubeVN();

			systems.add<FreeCameraSystem>();
			systems.add<TransformSystem>();
			systems.add<CameraSystem>();
			systems.add<GlDrawSystem>();
			systems.configure();

			auto cube = entities.create();
			cube.assign<GlDrawComponent>(diffuseMaterial, cubeMesh);
			cube.assign<TransformComponent>(glm::vec3(1.0f), glm::vec3(0.0f, 0.0f, 2.0f));
			cube.assign<RotateComponent>(glm::vec3(0.75f, 0.5f, 0.25f));

			cube = entities.create();
			cube.assign<GlDrawComponent>(colorMaterial, cubeMesh);
			cube.assign<TransformComponent>(glm::vec3(1.0f), glm::vec3(4.0f, 0.0f, 2.0f));
			cube.assign<RotateComponent>(glm::vec3(0.25f, 0.5f, 0.75f));

			events.emit<AspectRatioEvent>(
				float(INJECT_WINDOW_WIDTH) / float(INJECT_WINDOW_HEIGHT), 0.0f);
		}
	};
}
