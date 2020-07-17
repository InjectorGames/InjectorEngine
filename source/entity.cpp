#include <injector/entity.hpp>
#include <injector/manager.hpp>

#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	Entity::Entity(size_t _id, Manager& _manager) :
		id(_id),
		manager(_manager)
	{}

	size_t Entity::getID() const noexcept
	{
		return id;
	}
	Manager& Entity::getManager() const noexcept
	{
		return manager;
	}

	bool Entity::isValid() const noexcept
	{
		auto& entities = manager.entities;
		return entities.find(id) != entities.end();
	}

	size_t Entity::getComponentCount() const noexcept
	{
		return manager.entities.size();
	}
	bool Entity::removeComponents() noexcept
	{
		auto& entities = manager.entities;
		auto iterator = entities.find(id);

		if (iterator == entities.end())
			return false;

		auto& components = iterator->second;

		for (const auto& pair : components)
			delete pair.second;

		components.clear();
		return true;
	}
}
