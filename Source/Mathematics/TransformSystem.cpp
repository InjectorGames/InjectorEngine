#include "Injector/Mathematics/TransformSystem.hpp"
#include "Injector/Exception/OutOfRangeException.hpp"
#include "Injector/Engine.hpp"

#include <iostream>

namespace Injector
{
	TransformSystem::TransformSystem() :
		transforms(),
		translates(),
		rotates()
	{
	}
	TransformSystem::~TransformSystem()
	{
	}

	void TransformSystem::update()
	{
		auto deltaTime = static_cast<float>(Engine::getUpdateDeltaTime());

		for (auto& translate : translates)
		{
			TransformComponent* transformComponent;
			TranslateComponent* translateComponent;

			if (!translate->getComponent(transformComponent) ||
				!translate->getComponent(translateComponent))
				continue;

			transformComponent->position +=
				translateComponent->translation * deltaTime;
		}

		for (auto& rotate : rotates)
		{
			TransformComponent* transformComponent;
			RotateComponent* rotateComponent;

			if (!rotate->getComponent(transformComponent) ||
				!rotate->getComponent(rotateComponent))
				continue;

			transformComponent->rotation *=
				rotateComponent->rotation * deltaTime;
		}

		for (auto& transform : transforms)
		{
			TransformComponent* transformComponent;

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
			TransformComponent* transformComponent;

			if (!transform->getComponent(transformComponent))
				continue;

			if (transformComponent->parent)
			{
				auto parent = transformComponent->parent;
				auto matrix = transformComponent->matrix;
				TransformComponent* parentTransformComponent;

				auto cycleCount = 0;

				while (parent)
				{
					if (!parent->getComponent(parentTransformComponent))
						break;

					parent = parentTransformComponent->parent;
					matrix = parentTransformComponent->matrix * matrix;

					if(cycleCount >= 0xFFFF)
					{
						throw OutOfRangeException(
							"TransformSystem",
							"update",
							cycleCount,
							0xFFFF);
					}
				}

				transformComponent->matrix = matrix;
			}
		}
	}

	size_t TransformSystem::getTransformCount() const noexcept
	{
		return transforms.size();
	}

	bool TransformSystem::addTransform(
		const std::shared_ptr<Entity>& entity) noexcept
	{
		return transforms.emplace(entity).second;
	}
	bool TransformSystem::removeTransform(
		const std::shared_ptr<Entity>& entity) noexcept
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

	bool TransformSystem::addTranslate(
		const std::shared_ptr<Entity>& entity) noexcept
	{
		return translates.emplace(entity).second;
	}
	bool TransformSystem::removeTranslate(
		const std::shared_ptr<Entity>& entity) noexcept
	{
		if (entity == nullptr)
			return false;

		auto iterator = translates.find(entity);

		if (iterator == translates.end())
			return false;

		translates.erase(iterator);
		return true;
	}
	void TransformSystem::removeTranslates() noexcept
	{
		translates.clear();
	}

	bool TransformSystem::addRotate(
		const std::shared_ptr<Entity>& entity) noexcept
	{
		return rotates.emplace(entity).second;
	}
	bool TransformSystem::removeRotate(
		const std::shared_ptr<Entity>& entity) noexcept
	{
		if (entity == nullptr)
			return false;

		auto iterator = rotates.find(entity);

		if (iterator == rotates.end())
			return false;

		rotates.erase(iterator);
		return true;
	}
	void TransformSystem::removeRotates() noexcept
	{
		rotates.clear();
	}
}
