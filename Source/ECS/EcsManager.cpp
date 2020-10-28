#include "Injector/ECS/EcsManager.hpp"
#include "Injector/Exception/Exception.hpp"

namespace Injector
{
	EcsManager::EcsManager(bool _active) noexcept :
		active(_active),
		entities(),
		systems()
	{
	}

	void EcsManager::update()
	{
		for (auto system : systems)
			system->update();
	}

	bool EcsManager::isActive() const noexcept
	{
		return active;
	}
	size_t EcsManager::getEntityCount() const noexcept
	{
		return entities.size();
	}
	size_t EcsManager::getSystemCount() const noexcept
	{
		return systems.size();
	}

	std::shared_ptr<EcsEntity> EcsManager::createEntity()
	{
		auto entity = std::make_shared<EcsEntity>();

		if (!entities.emplace(entity).second)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to create entity");
		}

		return entity;
	}

	bool EcsManager::removeEntity(
		const std::shared_ptr<EcsEntity>& entity) noexcept
	{
		if (!entity)
			return false;

		auto iterator = entities.find(entity);

		if (iterator == entities.end())
			return false;

		entities.erase(iterator);
		return true;
	}
	bool EcsManager::removeSystem(
		const std::shared_ptr<EcsSystem>& system) noexcept
	{
		if (!system)
			return false;

		for (auto i = systems.begin(); i != systems.end(); i++)
		{
			if (system == *i)
			{
				systems.erase(i);
				return true;
			}
		}

		return false;
	}

	bool EcsManager::containsEntity(
		const std::shared_ptr<EcsEntity>& entity) const noexcept
	{
		if (!entity)
			return false;

		return entities.find(entity) != entities.end();
	}
	bool EcsManager::containsSystem(
		const std::shared_ptr<EcsSystem>& system) const noexcept
	{
		if (system == nullptr)
			return false;

		for (auto i = systems.begin(); i != systems.end(); i++)
		{
			if (system == *i)
				return true;
		}

		return false;
	}

	void EcsManager::removeEntities() noexcept
	{
		entities.clear();
	}
	void EcsManager::removeSystems() noexcept
	{
		systems.clear();
	}
}
