#pragma once
#include <inject/window_size_event.hpp>
#include <inject/camera_component.hpp>
#include <inject/gl_draw_component.hpp>
#include <inject/transform_component.hpp>

namespace inject
{
	class GlDrawSystem final :
		public entityx::System<GlDrawSystem>,
		public entityx::Receiver<GlDrawSystem>
	{
	public:
		void configure(entityx::EntityManager& entities,
			entityx::EventManager& events) override
		{
			events.subscribe<WindowSizeEvent>(*this);
		}

		void update(entityx::EntityManager& entities,
			entityx::EventManager& events,
			entityx::TimeDelta deltaTime) override
		{
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_FRONT);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			std::multimap<int, entityx::Entity> cameraEntities;

			entities.each<CameraComponent>(
				[&](entityx::Entity entity, CameraComponent& cameraComponent)
				{
					cameraEntities.emplace(cameraComponent.renderQueue, entity);
				});


			for (auto cameraEntity : cameraEntities)
			{
				const auto& cameraComponent = *cameraEntity.second.component<CameraComponent>();
				const auto& viewMatrix = cameraComponent.viewMatrix;
				const auto& projMatrix = cameraComponent.projMatrix;
				const auto viewProjMatrix = projMatrix * viewMatrix;

				entities.each<GlDrawComponent, TransformComponent>(
					[&](entityx::Entity entity,GlDrawComponent& drawComponent,TransformComponent& transformComponent)
					{
						const auto& material = drawComponent.material;
						const auto& mesh = drawComponent.mesh;

						if (drawComponent.draw && material && mesh)
						{
							// TODO:
							// Multiply by parents matrices
							const auto& modelMatrix = transformComponent.matrix;
							const auto mvpMatrix = viewProjMatrix * modelMatrix;

							material->use();

							material->setModelMatrix(modelMatrix);
							material->setViewMatrix(viewMatrix);
							material->setProjMatrix(projMatrix);
							material->setViewProjMatrix(viewProjMatrix);
							material->setMvpMatrix(mvpMatrix);

							mesh->bind();
							mesh->draw();
							mesh->unbind();

							material->unuse();
						}
					});
			}
		}

		void receive(const WindowSizeEvent& event)
		{
			glViewport(0, 0, static_cast<GLsizei>(event.size.x), static_cast<GLsizei>(event.size.y));
		}
	};
}
