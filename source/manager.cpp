#pragma once
#include <injector/manager.hpp>

namespace INJECTOR_NAMESPACE
{
	Manager::Manager(size_t _id, bool _active) :
		id(_id),
		active(_active),
		initialized(false),
		freeEntityID(0),
		systems(),
		entities()
	{}
	Manager::~Manager()
	{
		removeEntities();

		for (const auto& pair : systems)
			delete pair.second;

		systems.clear();
	}

	size_t Manager::getID() const noexcept
	{
		return id;
	}
	bool Manager::getActive() const noexcept
	{
		return active;
	}

	bool Manager::getInitialized() const noexcept
	{
		return initialized;
	}
	size_t Manager::getFreeEntityID() const noexcept
	{
		return freeEntityID;
	}

	void Manager::initialize()
	{
		if (initialized)
			throw std::runtime_error("Manager is already initialized");

		for (auto& pair : systems)
			pair.second->initialize();

		initialized = true;
	}
	void Manager::terminate()
	{
		if (!initialized)
			throw std::runtime_error("Manager is already terminated");

		for (auto& pair : systems)
			pair.second->terminate();

		initialized = false;
	}

	Entity Manager::createEntity()
	{
		if (freeEntityID == SIZE_MAX)
		{
			// TODO: reorder map
		}

		if (!entities.emplace(freeEntityID, Components()).second)
			throw std::runtime_error("Failed to create manager entity");

		return Entity(freeEntityID++, *this);
	}
	size_t Manager::getEntityCount() const noexcept
	{
		return entities.size();
	}
	bool Manager::isContainsEntity(size_t id) const noexcept
	{
		return entities.find(id) != entities.end();
	}

	bool Manager::removeEntity(size_t id) noexcept
	{
		auto iterator = entities.find(id);

		if (iterator == entities.end())
			return false;

		auto components = iterator->second;

		for (const auto& pair : components)
			delete pair.second;

		entities.erase(iterator);
		return true;
	}
	bool Manager::removeEntities() noexcept
	{
		for (const auto& pair : entities)
		{
			const auto& components = pair.second;

			for (const auto& pair : components)
				delete pair.second;
		}

		entities.clear();
	}
}
