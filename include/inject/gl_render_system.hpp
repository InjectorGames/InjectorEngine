#pragma once
#include <inject/window_size_event.hpp>
#include <inject/gl_draw_component.hpp>

#include <entityx/entityx.h>

#include <GL/glew.h>
#include <SDL_opengl.h>

namespace inject
{
	class GlRenderSystem final :
		public entityx::System<GlRenderSystem>,
		public entityx::Receiver<GlRenderSystem>
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
			glClear(GL_COLOR_BUFFER_BIT);

			std::multimap<int, entityx::Entity> cameraEntities;

			entities.each<CameraComponent, TransformComponent>([&](
				entityx::Entity entity,
				CameraComponent& cameraComponent,
				TransformComponent& transformComponent)
				{
					cameraEntities.emplace(cameraComponent.renderQueue, entity);
				});


			for (auto cameraEntity : cameraEntities)
			{
				const auto& cameraComponent = *cameraEntity.second.component<CameraComponent>();
				const auto& transformComponent = *cameraEntity.second.component<TransformComponent>();

				const auto& viewMatrix = transformComponent.matrix;
				const auto& projMatrix = cameraComponent.projMatrix;
				const auto viewProjMatrix = projMatrix * viewMatrix;

				entities.each<GlDrawComponent, TransformComponent>([&](
					entityx::Entity entity,
					GlDrawComponent& drawComponent,
					TransformComponent& transformComponent)
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

							material->setModel(modelMatrix);
							material->setView(viewMatrix);
							material->setProj(projMatrix);
							material->setViewProj(viewProjMatrix);
							material->setMVP(mvpMatrix);

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
