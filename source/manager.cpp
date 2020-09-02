#include <injector/manager.hpp>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	Manager::Manager(bool _active) :
		active(_active),
		entities(), 
		systems()
	{}
	Manager::~Manager()
	{}

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

	EntityHandle Manager::createEntity()
	{
		auto entity = std::make_shared<Entity>();

		if (!entities.emplace(entity).second)
			throw std::runtime_error("Failed to create manager entity");

		return entity;
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
	bool Manager::destroySystem(const SystemHandle& system) noexcept
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

	bool Manager::containsEntity(const EntityHandle& entity) const noexcept
	{
		if (entity == nullptr)
			return false;

		return entities.find(entity) != entities.end();
	}
	bool Manager::containsSystem(const SystemHandle& system) noexcept
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
