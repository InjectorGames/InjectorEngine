#include "Injector/Mathematics/TransformSystem.hpp"
#include "Injector/Engine.hpp"

#include <iostream>

namespace Injector::Mathematics
{
	TransformSystem::~TransformSystem()
	{}

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
			transformComponent->changed = true;
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
			transformComponent->changed = true;
		}

		for (auto& transform : transforms)
		{
			TransformComponent* transformComponent;

			if (!transform->getComponent(transformComponent) ||
				!transformComponent->changed)
				continue;

			transformComponent->rotation = transformComponent->rotation.getNormalized();

			Matrix4 matrix;

			if (transformComponent->origin == RotationOrigin::Spin)
			{
				matrix = Matrix4::identity.getTranslated(transformComponent->position);
				matrix *= transformComponent->rotation.getMatrix4();
				matrix *= Matrix4::identity.getScaled(transformComponent->scale);
			}
			else
			{
				matrix = transformComponent->rotation.getMatrix4();
				matrix *= Matrix4::identity.getTranslated(transformComponent->position);
				matrix *= Matrix4::identity.getScaled(transformComponent->scale);
			}

			transformComponent->matrix = matrix;
			transformComponent->changed = false;
		}

		for (auto& attach : attaches)
		{
			TransformComponent* transformComponent;
			AttachComponent* attachComponent;

			if (!attach->getComponent(transformComponent) ||
				!attach->getComponent(attachComponent))
				continue;

			auto matrix = transformComponent->matrix;
			auto target = attachComponent->target;

			while (target)
			{
				TransformComponent* targetTransformComponent;
				AttachComponent* targetAttachComponent;

				if (!target->getComponent(targetTransformComponent) ||
					!target->getComponent(targetAttachComponent))
					break;

				matrix *= targetTransformComponent->matrix;
				target = targetAttachComponent->target;
			}

			transformComponent->matrix = matrix;
		}
	}

	size_t TransformSystem::getTransformCount() const noexcept
	{
		return transforms.size();
	}

	bool TransformSystem::addTransform(const shared_ptr<Entity>& entity) noexcept
	{
		return transforms.emplace(entity).second;
	}
	bool TransformSystem::removeTransform(const shared_ptr<Entity>& entity) noexcept
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

	bool TransformSystem::addTranslate(const shared_ptr<Entity>& entity) noexcept
	{
		return translates.emplace(entity).second;
	}
	bool TransformSystem::removeTranslate(const shared_ptr<Entity>& entity) noexcept
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

	bool TransformSystem::addRotate(const shared_ptr<Entity>& entity) noexcept
	{
		return rotates.emplace(entity).second;
	}
	bool TransformSystem::removeRotate(const shared_ptr<Entity>& entity) noexcept
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

	bool TransformSystem::addAttach(const shared_ptr<Entity>& entity) noexcept
	{
		return attaches.emplace(entity).second;
	}
	bool TransformSystem::removeAttach(const shared_ptr<Entity>& entity) noexcept
	{
		if (entity == nullptr)
			return false;

		auto iterator = attaches.find(entity);

		if (iterator == attaches.end())
			return false;

		attaches.erase(iterator);
		return true;
	}
	void TransformSystem::removeAttaches() noexcept
	{
		attaches.clear();
	}
}
