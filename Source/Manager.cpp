#include "Injector/Manager.hpp"
#include "Injector/Exception/Exception.hpp"

namespace Injector
{
	Manager::Manager(bool _active) noexcept :
		active(_active),
		entities(),
		systems()
	{
	}

	void Manager::update()
	{
		for (auto system : systems)
			system->update();
	}

	bool Manager::isActive() const noexcept
	{
		return active;
	}
	size_t Manager::getEntityCount() const noexcept
	{
		return entities.size();
	}
	size_t Manager::getSystemCount() const noexcept
	{
		return systems.size();
	}

	std::shared_ptr<Entity> Manager::createEntity()
	{
		auto entity = std::make_shared<Entity>();

		if (!entities.emplace(entity).second)
		{
			throw Exception(
				"Manager",
				"createEntity",
				"Failed to create entity");
		}

		return entity;
	}
	bool Manager::addEntity(
		const std::shared_ptr<Entity>& entity) noexcept
	{
		if (!entity)
			return false;

		return entities.emplace(entity).second;
	}

	bool Manager::removeEntity(
		const std::shared_ptr<Entity>& entity) noexcept
	{
		if (!entity)
			return false;

		auto iterator = entities.find(entity);

		if (iterator == entities.end())
			return false;

		entities.erase(iterator);
		return true;
	}
	bool Manager::destroySystem(const std::shared_ptr<System>& system) noexcept
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

	bool Manager::containsEntity(
		const std::shared_ptr<Entity>& entity) const noexcept
	{
		if (!entity)
			return false;

		return entities.find(entity) != entities.end();
	}
	bool Manager::containsSystem(
		const std::shared_ptr<System>& system) noexcept
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

	void Manager::removeEntities() noexcept
	{
		entities.clear();
	}
	void Manager::destroySystems() noexcept
	{
		systems.clear();
	}
}
