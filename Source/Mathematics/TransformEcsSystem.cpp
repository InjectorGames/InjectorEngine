#include "Injector/Mathematics/TransformEcsSystem.hpp"
#include "Injector/Exception/OutOfRangeException.hpp"
#include "Injector/Engine.hpp"

namespace Injector
{
	TransformEcsSystem::TransformEcsSystem() noexcept :
		transforms(),
		translates(),
		rotates()
	{
	}

	const std::set<std::shared_ptr<EcsEntity>>&
		TransformEcsSystem::getTransforms() const noexcept
	{
		return transforms;
	}
	const std::set<std::shared_ptr<EcsEntity>>&
		TransformEcsSystem::getTranslates() const noexcept
	{
		return translates;
	}
	const std::set<std::shared_ptr<EcsEntity>>&
		TransformEcsSystem::getRotates() const noexcept
	{
		return rotates;
	}

	void TransformEcsSystem::update()
	{
		auto deltaTime = static_cast<float>(Engine::getUpdateDeltaTime());

		for (auto& translate : translates)
		{
			TransformEcsComponent* transformComponent;
			TranslateEcsComponent* translateComponent;

			if (!translate->getComponent(transformComponent) ||
				!translate->getComponent(translateComponent))
				continue;

			transformComponent->position +=
				translateComponent->translation * deltaTime;
		}

		for (auto& rotate : rotates)
		{
			TransformEcsComponent* transformComponent;
			RotateEcsComponent* rotateComponent;

			if (!rotate->getComponent(transformComponent) ||
				!rotate->getComponent(rotateComponent))
				continue;

			transformComponent->rotation *=
				rotateComponent->rotation * deltaTime;
		}

		for (auto& transform : transforms)
		{
			TransformEcsComponent* transformComponent;

			if (!transform->getComponent(transformComponent))
				continue;

			auto rotation = transformComponent->rotation.getNormalized();
			transformComponent->rotation = rotation;

			Matrix4 matrix;

			if (transformComponent->origin == RotationOrigin::Spin)
			{
				matrix = Matrix4::identity.getTranslated(transformComponent->position);
				matrix *= rotation.getMatrix4();
				matrix *= Matrix4::identity.getScaled(transformComponent->scale);
			}
			else
			{
				matrix = rotation.getMatrix4();
				matrix *= Matrix4::identity.getTranslated(transformComponent->position);
				matrix *= Matrix4::identity.getScaled(transformComponent->scale);
			}

			transformComponent->matrix = matrix;
		}

		for (auto& transform : transforms)
		{
			TransformEcsComponent* transformComponent;

			if (!transform->getComponent(transformComponent))
				continue;

			if (transformComponent->parent)
			{
				auto parent = transformComponent->parent;
				auto matrix = transformComponent->matrix;
				TransformEcsComponent* parentTransformComponent;

				auto cycleCount = 0;

				while (parent)
				{
					if (!parent->getComponent(parentTransformComponent))
						break;

					parent = parentTransformComponent->parent;
					matrix = parentTransformComponent->matrix * matrix;

					if (cycleCount > 0xFFFF)
					{
						throw OutOfRangeException(
							THIS_FUNCTION_NAME,
							cycleCount,
							0xFFFF);
					}
					else
					{
						cycleCount++;
					}
				}

				transformComponent->matrix = matrix;
			}
		}
	}

	bool TransformEcsSystem::addTransform(
		const std::shared_ptr<EcsEntity>& entity) noexcept
	{
		if (!entity)
			return false;

		return transforms.emplace(entity).second;
	}
	bool TransformEcsSystem::addTranslate(
		const std::shared_ptr<EcsEntity>& entity) noexcept
	{
		if (!entity)
			return false;

		return translates.emplace(entity).second;
	}
	bool TransformEcsSystem::addRotate(
		const std::shared_ptr<EcsEntity>& entity) noexcept
	{
		if (!entity)
			return false;

		return rotates.emplace(entity).second;
	}

	bool TransformEcsSystem::removeTransform(
		const std::shared_ptr<EcsEntity>& entity) noexcept
	{
		if (!entity)
			return false;

		auto iterator = transforms.find(entity);

		if (iterator == transforms.end())
			return false;

		transforms.erase(iterator);
		return true;
	}
	bool TransformEcsSystem::removeTranslate(
		const std::shared_ptr<EcsEntity>& entity) noexcept
	{
		if (!entity)
			return false;

		auto iterator = translates.find(entity);

		if (iterator == translates.end())
			return false;

		translates.erase(iterator);
		return true;
	}
	bool TransformEcsSystem::removeRotate(
		const std::shared_ptr<EcsEntity>& entity) noexcept
	{
		if (!entity)
			return false;

		auto iterator = rotates.find(entity);

		if (iterator == rotates.end())
			return false;

		rotates.erase(iterator);
		return true;
	}

	void TransformEcsSystem::removeTransforms() noexcept
	{
		transforms.clear();
	}
	void TransformEcsSystem::removeTranslates() noexcept
	{
		translates.clear();
	}
	void TransformEcsSystem::removeRotates() noexcept
	{
		rotates.clear();
	}
}
