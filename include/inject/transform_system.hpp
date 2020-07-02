#pragma once
#include <inject/transform_component.hpp>
#include <inject/translate_component.hpp>
#include <inject/rotate_component.hpp>

namespace INJECT_NAMESPACE
{
	class TransformSystem final :
		public entityx::System<TransformSystem>
	{
	public:
		void update(entityx::EntityManager& entities,
			entityx::EventManager& events,
			entityx::TimeDelta deltaTime) override
		{
			// TODO: paralelize this

			entities.each<TransformComponent>(
				[deltaTime](entityx::Entity entity, TransformComponent& transform)
				{
					if (entity.has_component<TranslateComponent>())
					{
						auto& translateComponent = *entity.component<TranslateComponent>();
						transform.position +=
							translateComponent.translation * static_cast<float>(deltaTime);
						transform.changed = true;
					}

					if (entity.has_component<RotateComponent>())
					{
						auto& rotateComponent = *entity.component<RotateComponent>();
						transform.rotation *=
							glm::quat(rotateComponent.rotation * static_cast<float>(deltaTime));
						transform.changed = true;
					}

					if (transform.changed)
					{
						if (transform.type == TransformComponent::Type::Spin)
						{
							transform.matrix =
								glm::translate(glm::mat4(1.0f), transform.position) *
								glm::mat4_cast(glm::normalize(transform.rotation)) *
								glm::scale(glm::mat4(1.0f), transform.scale);
							transform.changed = false;
						}
						else
						{
							transform.matrix =
								glm::scale(glm::mat4(1.0f), transform.scale) *
								glm::mat4_cast(glm::normalize(transform.rotation)) *
								glm::translate(glm::mat4(1.0f), transform.position);
							transform.changed = false;
						}
					}
				});
		}
	};
}
