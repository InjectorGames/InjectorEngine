#pragma once
#include <inject/level.hpp>
#include <inject/camera_system.hpp>
#include <inject/transform_system.hpp>
#include <inject/first_person_system.hpp>
#include <inject/gl_render_system.hpp>
#include <inject/gl_draw_component.hpp>
#include <inject/gl_color_material.hpp>

namespace inject
{
	class GlEditorLevel : public Level
	{
	protected:
		std::shared_ptr<GlColorMaterial> colorMaterial;

		std::shared_ptr<GlMesh> squareMesh;
	public:
		GlEditorLevel(const uint32_t id) : Level(id)
		{
			colorMaterial = std::make_shared<GlColorMaterial>(
				std::make_shared<GlShader>(Shader::Type::Vertex, "resources/shaders/color.vert", true),
				std::make_shared<GlShader>(Shader::Type::Fragment, "resources/shaders/color.frag", true));

			squareMesh = GlMesh::CreateCubeV();

			systems.add<FirstPersonSystem>();
			systems.add<TransformSystem>();
			systems.add<CameraSystem>();
			systems.add<GlRenderSystem>();
			systems.configure();

			auto square = entities.create();
			square.assign<GlDrawComponent>(colorMaterial, squareMesh);
			square.assign<TransformComponent>();
			square.assign<RotateComponent>(glm::vec3(0.5f, 0.0f, 0.0f));
		}
	};
}
