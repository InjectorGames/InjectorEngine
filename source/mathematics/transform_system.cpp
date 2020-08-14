#include <injector/mathematics/transform_system.hpp>
#include <injector/engine.hpp>

#include <iostream>

namespace INJECTOR_NAMESPACE
{
	TransformSystem::TransformSystem() :
		transforms()
	{}
	TransformSystem::~TransformSystem()
	{}

	void TransformSystem::update()
	{
		auto deltaTime = static_cast<float>(Engine::getUpdateDeltaTime());

		for (auto& transform : transforms)
		{
			TransformComponent* transformComponent;

			if (!transform->getComponent(transformComponent))
				continue;

			TranslateComponent* translateComponent;
			if (transform->getComponent(translateComponent))
			{
				transformComponent->position +=
					translateComponent->translation * deltaTime;
				transformComponent->changed = true;
			}

			RotateComponent* rotateComponent;
			if (transform->getComponent(rotateComponent))
			{
				transformComponent->rotation *=
					rotateComponent->rotation * deltaTime;
				transformComponent->rotation =
					transformComponent->rotation.getNormalized();
				transformComponent->changed = true;
			}

			if (!transformComponent->changed)
				continue;

			if (transformComponent->type == TransformComponent::Type::Spin)
			{
				auto matrix = Matrix4::identity.getTranslated(transformComponent->position);
				matrix *= transformComponent->rotation.getNormalized().getMatrix4();
				matrix *= Matrix4::identity.getScaled(transformComponent->scale);

				auto& relative = transformComponent->parent;
				while (relative)
				{
					TransformComponent* relativeTransform;

					if (!relative->getComponent(relativeTransform))
						break;

					matrix = relativeTransform->matrix * matrix;
					relative = relativeTransform->parent;
				}

				transformComponent->matrix = matrix;
				transformComponent->changed = false;
			}
			else
			{
				auto matrix = Matrix4::identity.getScaled(transformComponent->scale);
				matrix *= transformComponent->rotation.getNormalized().getMatrix4();
				matrix *= Matrix4::identity.getTranslated(transformComponent->position);

				auto& relative = transformComponent->parent;
				while (relative)
				{
					TransformComponent* relativeTransform;

					if (!relative->getComponent(relativeTransform))
						break;

					matrix = relativeTransform->matrix * matrix;
					relative = relativeTransform->parent;
				}

				transformComponent->matrix = matrix;
				transformComponent->changed = false;
			}
		}
	}

	size_t TransformSystem::getTransformCount() const noexcept
	{
		return transforms.size();
	}

	bool TransformSystem::addTransform(const EntityHandle& entity) noexcept
	{
		if (entity == nullptr || !entity->containsComponent<TransformComponent>())
			return false;

		return transforms.emplace(entity).second;
	}
	bool TransformSystem::removeTransform(const EntityHandle& entity) noexcept
	{
		if (entity == nullptr)
			return false;

		auto iterator = transforms.find(entity);

		if (iterator == transforms.end())
			return false;

		transforms.erase(iterator);
		return true;
	}
	void TransformSystem::removeTransforms() noexcept
	{
		transforms.clear();
	}
}
