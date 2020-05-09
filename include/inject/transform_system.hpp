#pragma once
#include <inject/transform_component.hpp>
#include <inject/translate_component.hpp>
#include <inject/rotate_component.hpp>

namespace inject
{
	class TransformSystem final : public entityx::System<TransformSystem>
	{
		void update(entityx::EntityManager& entities,
			entityx::EventManager& events,
			entityx::TimeDelta deltaTime) override
		{
			// TODO: paralelize this

			entities.each<TransformComponent>(
				[deltaTime](entityx::Entity entity, TransformComponent& transformComponent)
				{
					if (entity.has_component<TranslateComponent>())
					{
						auto& translateComponent = *entity.component<TranslateComponent>();
						transformComponent.position += 
							translateComponent.translation * static_cast<float>(deltaTime);
						transformComponent.changed = true;
					}

					if (entity.has_component<RotateComponent>())
					{
						auto& rotateComponent = *entity.component<RotateComponent>();
						transformComponent.rotation *= 
							glm::quat(rotateComponent.rotation * static_cast<float>(deltaTime));
						transformComponent.changed = true;
					}

					if (transformComponent.changed)
					{
						transformComponent.matrix = 
							glm::translate(glm::mat4(1.0f), transformComponent.position) *
							glm::mat4_cast(glm::normalize(transformComponent.rotation)) *
							glm::scale(glm::mat4(1.0f), transformComponent.scale);
						transformComponent.changed = false;
					}
				});
		}
	};
}
