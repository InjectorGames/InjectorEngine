#pragma once
#include <inject/config.hpp>
#include <inject/camera_system.hpp>
#include <inject/transform_system.hpp>
#include <inject/free_camera_system.hpp>
#include <inject/gl_window.hpp>
#include <inject/gl_gui_system.hpp>
#include <inject/gl_draw_system.hpp>
#include <inject/gl_color_material.hpp>
#include <inject/gl_blend_color_material.hpp>
#include <inject/gl_diffuse_material.hpp>
#include <inject/gl_blend_diffuse_material.hpp>
#include <inject/gl_gradient_sky_system.hpp>

namespace inject
{
	class GlEditorWindow : public GlWindow
	{
	protected:
		std::shared_ptr<GlColorMaterial> colorMaterial;
		std::shared_ptr<GlColorMaterial> colColorMaterial;
		std::shared_ptr<GlBlendColorMaterial> blendColorMaterial;
		std::shared_ptr<GlDiffuseMaterial> diffuseMaterial;
		std::shared_ptr<GlBlendDiffuseMaterial> blendDiffuseMaterial;
		std::shared_ptr<GlGradientSkyMaterial> gradientSkyMaterial;

		std::shared_ptr<GlMesh> squareMesh;
		std::shared_ptr<GlMesh> cubeMesh;
		std::shared_ptr<GlMesh> axisMesh;
		std::shared_ptr<GlMesh> gradientSkyMesh;
	public:
		GlEditorWindow(const std::string& title = INJECT_WINDOW_NAME + std::string(" - Editor (OpenGL)"),
			const glm::ivec2& position = glm::ivec2(SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED),
			const glm::ivec2& size = glm::ivec2(INJECT_WINDOW_WIDTH, INJECT_WINDOW_HEIGHT),
			const uint32_t flags = SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL) :
			GlWindow(title, position, size, flags)
		{
			colorMaterial = std::make_shared<GlColorMaterial>(
				std::make_shared<GlShader>(Shader::Type::Vertex, "resources/shaders/color.vert", true),
				std::make_shared<GlShader>(Shader::Type::Fragment, "resources/shaders/color.frag", true));
			colColorMaterial = std::make_shared<GlColorMaterial>(
				std::make_shared<GlShader>(Shader::Type::Vertex, "resources/shaders/col_color.vert", true),
				std::make_shared<GlShader>(Shader::Type::Fragment, "resources/shaders/col_color.frag", true));
			blendColorMaterial = std::make_shared<GlBlendColorMaterial>(
				std::make_shared<GlShader>(Shader::Type::Vertex, "resources/shaders/color.vert", true),
				std::make_shared<GlShader>(Shader::Type::Fragment, "resources/shaders/color.frag", true));
			diffuseMaterial = std::make_shared<GlDiffuseMaterial>(
				std::make_shared<GlShader>(Shader::Type::Vertex, "resources/shaders/diffuse.vert", true),
				std::make_shared<GlShader>(Shader::Type::Fragment, "resources/shaders/diffuse.frag", true));
			blendDiffuseMaterial = std::make_shared<GlBlendDiffuseMaterial>(
				std::make_shared<GlShader>(Shader::Type::Vertex, "resources/shaders/diffuse.vert", true),
				std::make_shared<GlShader>(Shader::Type::Fragment, "resources/shaders/diffuse.frag", true));
			gradientSkyMaterial = std::make_shared<GlGradientSkyMaterial>(
				std::make_shared<GlShader>(Shader::Type::Vertex, "resources/shaders/gradient_sky.vert", true),
				std::make_shared<GlShader>(Shader::Type::Fragment, "resources/shaders/gradient_sky.frag", true));

			diffuseMaterial->use();
			diffuseMaterial->setAmbientColor(
				glm::vec4(glm::mix(GlGradientSkyMaterial::defaultUpColor, GlGradientSkyMaterial::defaultUpColor, 0.5f), 1.0f) * 0.5f);
			diffuseMaterial->unuse();

			squareMesh = GlMesh::CreateSquareVN();
			cubeMesh = GlMesh::CreateCubeVN();
			axisMesh = GlMesh::CreateAxisVC();
			gradientSkyMesh = GlMesh::CreateGradientSky();

			auto freeCameraSystem = systems.add<FreeCameraSystem>();
			auto glGuiSystem = systems.add<GlGuiSystem>();
			auto transformSystem = systems.add<TransformSystem>();
			auto cameraSystem = systems.add<CameraSystem>();
			auto glGradientSkySystem = systems.add<GlGradientSkySystem>();
			auto glDrawSystem = systems.add<GlDrawSystem>();
			systems.configure();

			glGradientSkySystem->material = gradientSkyMaterial;
			glGradientSkySystem->cameraEulerAngles = const_cast<glm::vec3*>(&freeCameraSystem->getEulerAngles());

			auto axisEntity = entities.create();
			axisEntity.assign<GlDrawComponent>(0, GlDrawComponent::Order::Ascending, 0,
				colColorMaterial, axisMesh, GlMesh::DrawMode::Lines);
			axisEntity.assign<TransformComponent>();

			auto gradientSkyEntity = entities.create();
			gradientSkyEntity.assign<GlDrawComponent>(0, GlDrawComponent::Order::Back, 0,
				gradientSkyMaterial, gradientSkyMesh);
			gradientSkyEntity.assign<TransformComponent>();

			auto colorEntity = entities.create();
			colorEntity.assign<GlDrawComponent>(0, GlDrawComponent::Order::Ascending, 0,
				colorMaterial, cubeMesh);
			colorEntity.assign<TransformComponent>(TransformComponent::Type::Spin, entityx::Entity(),
				glm::vec3(1.0f), glm::vec3(0.0f, 0.0f, 2.0f));
			colorEntity.assign<RotateComponent>(glm::vec3(0.25f, 0.5f, 0.75));

			auto blendColorEntity = entities.create();
			blendColorEntity.assign<GlDrawComponent>(0, GlDrawComponent::Order::Descending, 2,
				blendColorMaterial, cubeMesh);
			blendColorEntity.assign<TransformComponent>(TransformComponent::Type::Spin, colorEntity,
				glm::vec3(1.0f), glm::vec3(0.0f, 0.0f, 4.0f));
			blendColorEntity.assign<RotateComponent>(glm::vec3(0.25f, 0.75f, 0.5f));

			auto diffuseEntity = entities.create();
			diffuseEntity.assign<GlDrawComponent>(0, GlDrawComponent::Order::Ascending, 0,
				diffuseMaterial, cubeMesh);
			diffuseEntity.assign<TransformComponent>(TransformComponent::Type::Spin, entityx::Entity(),
				glm::vec3(1.0f), glm::vec3(2.0f, 0.0f, 2.0f));
			diffuseEntity.assign<RotateComponent>(glm::vec3(0.75f, 0.5f, 0.25f));
			
			auto blendDiffuseEntity = entities.create();
			blendDiffuseEntity.assign<GlDrawComponent>(0, GlDrawComponent::Order::Descending, 2,
				blendDiffuseMaterial, cubeMesh);
			blendDiffuseEntity.assign<TransformComponent>(TransformComponent::Type::Spin, entityx::Entity(),
				glm::vec3(1.0f), glm::vec3(2.0f, 0.0f, 4.0f));
			blendDiffuseEntity.assign<RotateComponent>(glm::vec3(0.5f, 0.75f, 0.25f));

			auto aspectRatio = float(INJECT_WINDOW_WIDTH) / float(INJECT_WINDOW_HEIGHT);
			events.emit<AspectRatioEvent>(aspectRatio, aspectRatio);
		}
	};
}
