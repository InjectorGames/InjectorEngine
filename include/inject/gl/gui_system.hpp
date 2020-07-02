#pragma once
#include <inject/window_size_event.hpp>
#include <inject/mouse_button_event.hpp>
#include <inject/gl/draw_component.hpp>
#include <inject/gl/sprite_color_material.hpp>

namespace INJECT_NAMESPACE
{
	class GlGuiSystem :
		public entityx::System<GlGuiSystem>,
		public entityx::Receiver<GlGuiSystem>
	{
	private:
		entityx::Entity camera;
		entityx::Entity hierarchy;

		glm::ivec2 newWindowSize;

		std::shared_ptr<GlSpriteColorMaterial> spriteColorMaterial;
		std::shared_ptr<GlMesh> spriteMesh;
	public:
		GlGuiSystem() :
			camera(),
			hierarchy(),
			newWindowSize()
		{
			spriteColorMaterial = std::make_shared<GlSpriteColorMaterial>(
				std::make_shared<GlShader>(Shader::Type::Vertex, "resources/shaders/color.vert", true),
				std::make_shared<GlShader>(Shader::Type::Fragment, "resources/shaders/color.frag", true));
			spriteMesh = GlMesh::CreateSquareV();

			spriteColorMaterial->use();
			spriteColorMaterial->setColor(glm::vec4(0.25f, 0.25f, 0.25f, 0.75f));
			spriteColorMaterial->unuse();
		}

		void configure(entityx::EntityManager& entities,
			entityx::EventManager& events) override
		{
			events.subscribe<WindowSizeEvent>(*this);
			events.subscribe<MouseButtonEvent>(*this);

			camera = entities.create();
			camera.assign<OrthoCameraComponent>(1);
			camera.assign<TransformComponent>(TransformComponent::Type::Orbit,
				entityx::Entity(), glm::vec3(1.0f));

			hierarchy = entities.create();
			hierarchy.assign<GlDrawComponent>(1, GlDrawComponent::Order::Descending, 0,
				spriteColorMaterial, spriteMesh, GlMesh::DrawMode::Triangles, true);
			hierarchy.assign<TransformComponent>(TransformComponent::Type::Spin, entityx::Entity(),
				glm::vec3(300.0f, 20.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		}

		void update(entityx::EntityManager& entities,
			entityx::EventManager& events,
			entityx::TimeDelta deltaTime) override
		{
			if (newWindowSize.x != 0.0f && camera.valid() && camera.has_component<OrthoCameraComponent>())
			{
				// TODO: add scale modification

				auto& cameraComponent = *camera.component<OrthoCameraComponent>();
				const auto sizeRatio = newWindowSize.y / 2.0f;
				const auto aspectRatio = newWindowSize.x / float(newWindowSize.y);
				cameraComponent.frustum.x = -sizeRatio * aspectRatio;
				cameraComponent.frustum.y = sizeRatio * aspectRatio;
				cameraComponent.frustum.z = -sizeRatio;
				cameraComponent.frustum.w = sizeRatio;
				cameraComponent.clipPlane.x = -sizeRatio;
				cameraComponent.clipPlane.y = sizeRatio;
				cameraComponent.changed = true;
				newWindowSize = glm::ivec2(0.0f);
			}
		}

		void receive(const WindowSizeEvent& event)
		{
			newWindowSize = event.size;
		}
		void receive(const MouseButtonEvent& event)
		{
			//std::cout << event.data.x << "_" << event.data.y << "\n";
		}
	};
}
