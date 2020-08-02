#pragma once
#include <injector/manager.hpp>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	Manager::Manager() :
		entities(),
		systems()
	{}
	Manager::~Manager()
	{
		for (auto system : systems)
			delete system;
	}

	void Manager::update()
	{
		for (auto system : systems)
			system->update();
	}

	EntityHandle Manager::createEntity()
	{
		auto entity = std::make_shared<Entity>();

		if (!entities.emplace(entity).second)
			throw std::runtime_error("Failed to create manager entity");

		return entity;
	}
	bool Manager::createEntity(EntityHandle& _entity) noexcept
	{
		auto entity = std::make_shared<Entity>();

		if (!entities.emplace(entity).second)
			return false;

		_entity = entity;
		return true;
	}
	bool Manager::addEntity(const EntityHandle& entity) noexcept
	{
		if (entity == nullptr)
			return false;

		return entities.emplace(entity).second;
	}
	bool Manager::removeEntity(const EntityHandle& entity) noexcept
	{
		if (entity == nullptr)
			return false;

		auto iterator = entities.find(entity);

		if (iterator == entities.end())
			return false;

		entities.erase(iterator);
		return true;
	}
	bool Manager::containsEntity(const EntityHandle& entity) const noexcept
	{
		if (entity == nullptr)
			return false;

		return entities.find(entity) != entities.end();
	}
	void Manager::removeEntities() noexcept
	{
		entities.clear();
	}
	size_t Manager::getEntityCount() const noexcept
	{
		return entities.size();
	}

	bool Manager::removeSystem(const System* system) noexcept
	{
		if (system == nullptr)
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
	bool Manager::containsSystem(const System* system) noexcept
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
	void Manager::removeSystems() noexcept
	{
		for (auto system : systems)
			delete system;

		systems.clear();
	}
	size_t Manager::getSystemCount() const noexcept
	{
		return systems.size();
	}
}
