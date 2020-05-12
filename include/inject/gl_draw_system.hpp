#pragma once
#include <inject/window_size_event.hpp>
#include <inject/gl_draw_component.hpp>
#include <inject/transform_component.hpp>
#include <inject/persp_camera_component.hpp>
#include <inject/ortho_camera_component.hpp>

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

			entities.each<PerspCameraComponent, TransformComponent>(
				[&](entityx::Entity entity, PerspCameraComponent& camera, TransformComponent& transform)
				{
					cameraEntities.emplace(camera.queue, entity);
				});
			entities.each<OrthoCameraComponent, TransformComponent>(
				[&](entityx::Entity entity, OrthoCameraComponent& camera, TransformComponent& transform)
				{
					cameraEntities.emplace(camera.queue, entity);
				});

			auto drawCount = 0;

			for (auto cameraEntity : cameraEntities)
			{
				auto cameraQueue = cameraEntity.first;
				auto& cameraTransform = *cameraEntity.second.component<TransformComponent>();

				glm::mat4 projMatrix;
				glm::vec2 clipPlane;

				if (cameraEntity.second.has_component<PerspCameraComponent>())
				{
					auto& camera = *cameraEntity.second.component<PerspCameraComponent>();
					projMatrix = camera.matrix;
					clipPlane = camera.clipPlane;
				}
				else
				{
					auto& camera = *cameraEntity.second.component<OrthoCameraComponent>();
					projMatrix = camera.matrix;
					clipPlane = camera.clipPlane;
				}

				auto& viewMatrix = cameraTransform.matrix;
				auto viewProjMatrix = projMatrix * viewMatrix;

				std::multimap<float, entityx::Entity> drawEntities;

				entities.each<GlDrawComponent, TransformComponent>(
					[&](entityx::Entity entity, GlDrawComponent& draw, TransformComponent& transform)
					{
						if (draw.draw && draw.queue == cameraQueue && draw.material && draw.mesh)
						{
							switch (draw.order)
							{
							case GlDrawComponent::Order::Ascending:
								drawEntities.emplace(glm::distance(-cameraTransform.position, transform.position) + clipPlane.y * draw.offset, entity);
								break;
							case GlDrawComponent::Order::Descending:
								drawEntities.emplace(-glm::distance(-cameraTransform.position, transform.position) + clipPlane.y * draw.offset, entity);
								break;
							case GlDrawComponent::Order::Front:
								drawEntities.emplace(-clipPlane.y + clipPlane.y * draw.offset, entity);
								break;
							case GlDrawComponent::Order::Back:
								drawEntities.emplace(clipPlane.y + clipPlane.y * draw.offset, entity);
								break;
							}
						}
					});

				for (auto drawEntity : drawEntities)
				{
					auto& transform = *drawEntity.second.component<TransformComponent>();
					auto& draw = *drawEntity.second.component<GlDrawComponent>();

					// TODO:
					// Multiply by parents matrices
					auto& modelMatrix = transform.matrix;
					auto mvpMatrix = viewProjMatrix * modelMatrix;

					draw.material->use();

					draw.material->setModelMatrix(modelMatrix);
					draw.material->setViewMatrix(viewMatrix);
					draw.material->setProjMatrix(projMatrix);
					draw.material->setViewProjMatrix(viewProjMatrix);
					draw.material->setMvpMatrix(mvpMatrix);

					draw.mesh->bind();
					draw.mesh->draw(draw.drawMode);
					draw.mesh->unbind();

					draw.material->unuse();
					drawCount++;

					std::cout << drawEntity.second.id() << " " << drawEntity.first << "\n";
				}
			}

			std::cout << "\n";
			//std::cout << drawCount << "\n";
		}

		void receive(const WindowSizeEvent& event)
		{
			glViewport(0, 0,
				static_cast<GLsizei>(event.size.x),
				static_cast<GLsizei>(event.size.y));
		}
	};
}
