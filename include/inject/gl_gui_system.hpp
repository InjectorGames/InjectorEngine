#pragma once
#include <inject/aspect_ratio_event.hpp>
#include <inject/mouse_button_event.hpp>
#include <inject/gl_draw_component.hpp>
#include <inject/gl_sprite_color_material.hpp>

namespace inject
{
	class GlGuiSystem :
		public entityx::System<GlGuiSystem>,
		public entityx::Receiver<GlGuiSystem>
	{
	private:
		entityx::Entity camera;
		entityx::Entity toolbar;
		float newAspectRatio;

		std::shared_ptr<GlSpriteColorMaterial> spriteColorMaterial;
		std::shared_ptr<GlMesh> spriteMesh;
	public:
		GlGuiSystem() :
			camera(),
			toolbar(),
			newAspectRatio()
		{
			spriteColorMaterial = std::make_shared<GlSpriteColorMaterial>(
				std::make_shared<GlShader>(Shader::Type::Vertex, "resources/shaders/color.vert", true),
				std::make_shared<GlShader>(Shader::Type::Fragment, "resources/shaders/color.frag", true));
			spriteMesh = GlMesh::CreateSquareV();
		}

		void configure(entityx::EntityManager& entities,
			entityx::EventManager& events) override
		{
			events.subscribe<AspectRatioEvent>(*this);
			events.subscribe<MouseButtonEvent>(*this);

			camera = entities.create();
			camera.assign<OrthoCameraComponent>(1);
			camera.assign<TransformComponent>(TransformComponent::Type::Orbit,
				entityx::Entity(), glm::vec3(1.0f));

			/*toolbar = entities.create();
			toolbar.assign<GlDrawComponent>(1, GlDrawComponent::Order::Front, 0,
				spriteColorMaterial, spriteMesh, GlMesh::DrawMode::Triangles, true);
			toolbar.assign<TransformComponent>(TransformComponent::Type::Spin,
				glm::vec3(1.0f, 0.1f, 1.0f), glm::vec3(0.0f, 0.95f, 0.0f));*/
		}

		void update(entityx::EntityManager& entities,
			entityx::EventManager& events,
			entityx::TimeDelta deltaTime) override
		{
			if (newAspectRatio != 0.0f && camera.valid() && camera.has_component<OrthoCameraComponent>())
			{
				auto& cameraComponent = *camera.component<OrthoCameraComponent>();
				cameraComponent.frustum.x = -newAspectRatio;
				cameraComponent.frustum.y = newAspectRatio;
				cameraComponent.changed = true;
				newAspectRatio = 0.0f;
			}
		}

		void receive(const AspectRatioEvent& event)
		{
			newAspectRatio = event.aspectRatio;
		}
		void receive(const MouseButtonEvent& event)
		{

		}
	};
}
