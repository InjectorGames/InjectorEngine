#pragma once
#include <njng/transform_component.hpp>
#include <njng/translate_component.hpp>
#include <njng/rotate_component.hpp>

namespace njng
{
	class TransformSystem final : public entityx::System<TransformSystem>
	{
		void update(entityx::EntityManager& entities, entityx::EventManager& events, entityx::TimeDelta dt) override
		{
			// TODO: paralelize this

			entities.each<TransformComponent>([dt](entityx::Entity entity, TransformComponent& transformComponent)
				{
					if (entity.has_component<TranslateComponent>())
					{
						auto& translateComponent = *entity.component<TranslateComponent>();
						transformComponent.position += translateComponent.translation * static_cast<float>(dt);
						transformComponent.changed = true;
					}

					if (entity.has_component<RotateComponent>())
					{
						auto& rotateComponent = *entity.component<RotateComponent>();
						transformComponent.rotation *= glm::quat(rotateComponent.rotation * static_cast<float>(dt));
						transformComponent.changed = true;
					}

					if (transformComponent.changed)
					{
						transformComponent.matrix = glm::translate(glm::scale(glm::mat4_cast(glm::normalize(transformComponent.rotation)), transformComponent.scale), transformComponent.position);
						transformComponent.changed = false;
					}
				});
		}
	};
}
