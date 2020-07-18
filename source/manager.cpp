#pragma once
#include <injector/manager.hpp>

namespace INJECTOR_NAMESPACE
{
	Manager::Manager(size_t _id) :
		id(_id),
		freeEntityID(0),
		systems(),
		entities()
	{}
	Manager::~Manager()
	{
		destroyEntities();
		destroySystems();
	}

	void Manager::update()
	{
		for (auto& pair : systems)
			pair.second->update();
	}

	size_t Manager::getID() const noexcept
	{
		return id;
	}
	size_t Manager::getFreeEntityID() const noexcept
	{
		return freeEntityID;
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
	bool Manager::destroyEntity(size_t id) noexcept
	{
		auto iterator = entities.find(id);

		if (iterator == entities.end())
			return false;

		auto components = iterator->second;

		for (auto& pair : components)
			delete pair.second;

		entities.erase(iterator);
		return true;
	}
	void Manager::destroyEntities() noexcept
	{
		for (auto& pair : entities)
		{
			auto& components = pair.second;

			for (auto& pair : components)
				delete pair.second;
		}

		entities.clear();
	}
	size_t Manager::getEntityCount() const noexcept
	{
		return entities.size();
	}
	bool Manager::containsEntity(size_t id) const noexcept
	{
		return entities.find(id) != entities.end();
	}

	size_t Manager::getComponentCount(size_t id) const
	{
		return entities.at(id).size();
	}
	bool Manager::getComponentCount(size_t id, size_t& count) const noexcept
	{
		auto iterator = entities.find(id);

		if (iterator == entities.end())
			return false;

		count = iterator->second.size();
		return true;
	}
	bool Manager::destroyComponents(size_t id) noexcept
	{
		auto iterator = entities.find(id);

		if (iterator == entities.end())
			return false;

		auto& components = iterator->second;

		for (auto& pair : components)
			delete pair.second;

		components.clear();
		return true;
	}

	size_t Manager::getSystemCount() const noexcept
	{
		return systems.size();
	}
	void Manager::destroySystems() noexcept
	{
		for (auto& pair : systems)
			delete pair.second;

		systems.clear();
	}

	bool Manager::operator==(const Manager& other)
	{
		return id == other.id;
	}
	bool Manager::operator!=(const Manager& other)
	{
		return id != other.id;
	}
	bool Manager::operator<(const Manager& other)
	{
		return id < other.id;
	}
	bool Manager::operator>(const Manager& other)
	{
		return id > other.id;
	}
	bool Manager::operator<=(const Manager& other)
	{
		return id <= other.id;
	}
	bool Manager::operator>=(const Manager& other)
	{
		return id >= other.id;
	}
}
