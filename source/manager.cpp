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

		if (!entities.emplace(freeEntityID, std::map<std::type_index, Component*>()).second)
			throw std::runtime_error("Failed to create manager entity");

		return Entity(freeEntityID++, *this);
	}
}
