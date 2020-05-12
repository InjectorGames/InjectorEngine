#pragma once
#include <inject/transform_component.hpp>
#include <inject/ortho_camera_component.hpp>

namespace inject
{
	class InterfaceSystem : entityx::System<InterfaceSystem>
	{
	private:
		entityx::Entity camera;
	public:
		void configure(entityx::EntityManager& entities,
			entityx::EventManager& events) override
		{
			camera = entities.create();
			camera.assign<OrthoCameraComponent>(1);
			camera.assign<TransformComponent>(
				TransformComponent::Type::Orbit, glm::vec3(-1.0f));
		}

		void update(entityx::EntityManager& entities,
			entityx::EventManager& events,
			entityx::TimeDelta deltaTime) override
		{
		}
	};
}
