#include <injector/transform_system.hpp>
#include <injector/transform_component.hpp>
#include <injector/translate_component.hpp>
#include <injector/rotate_component.hpp>

namespace INJECTOR_NAMESPACE
{
	TransformSystem::TransformSystem() :
		transforms(), translates(), rotates()
	{}
	TransformSystem::~TransformSystem()
	{}

	void TransformSystem::update()
	{
		for (auto& transform : transforms)
		{
			TransformComponent* transformComponent;

			if (transform->getComponent(transformComponent))
			{
				if (transformComponent->changed)
				{
					if (transformComponent->type == TransformComponent::Type::Spin)
					{
						/*transformComponent->matrix =
							glm::translate(glm::mat4(1.0f), transform.position) *
							glm::mat4_cast(glm::normalize(transform.rotation)) *
							glm::scale(glm::mat4(1.0f), transform.scale);*/
						transformComponent->changed = false;
					}
					else
					{
						/*transformComponent->matrix =
							glm::scale(glm::mat4(1.0f), transform.scale) *
							glm::mat4_cast(glm::normalize(transform.rotation)) *
							glm::translate(glm::mat4(1.0f), transform.position);*/
						transformComponent->changed = false;
					}
				}
			}
		}

		/*entities.each<TransformComponent>(
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
			});*/
	}

	bool TransformSystem::createTransformComponent(
		const EntityHandle& entity,
		TransformComponent::Type type,
		const EntityHandle& parent,
		const Vector3& scale,
		const Vector3& position,
		const Quaternion& rotation,
		const Matrix4& matrix,
		const bool changed) noexcept
	{
		if (entity == nullptr)
			return false;

		TransformComponent* transformComponent;

		if (!entity->createComponent(transformComponent,
			type, parent, scale, position, rotation, matrix, changed))
			return false;

		transforms.emplace(entity);
		return true;
	}
	bool TransformSystem::destroyTransformComponent(
		const EntityHandle& entity) noexcept
	{
		if (entity == nullptr)
			return false;

		auto iterator = transforms.find(entity);

		if (iterator == transforms.end())
			return false;

		entity->destroyComponent<TransformComponent>();
		transforms.erase(iterator);
		return true;
	}
	void TransformSystem::destroyTransformComponents() noexcept
	{
		for (auto& transform : transforms)
			transform->destroyComponent<TransformComponent>();

		transforms.clear();
	}
	size_t TransformSystem::transformComponentCount() const noexcept
	{
		return transforms.size();
	}
}
