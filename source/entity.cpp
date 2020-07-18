#include <injector/entity.hpp>
#include <injector/manager.hpp>

#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	Entity::Entity(size_t _id, Manager& _manager) :
		id(_id), manager(_manager)
	{}

	bool Entity::destroy() noexcept
	{
		return manager.destroyEntity(id);
	}
	bool Entity::isValid() const noexcept
	{
		if (id == 0)
			return false;

		return manager.containsEntity(id);
	}

	size_t Entity::getComponentCount() const noexcept
	{
		return manager.getComponentCount(id);
	}
	bool Entity::getComponentCount(size_t& count) const noexcept
	{
		return manager.getComponentCount(count);
	}
	bool Entity::destroyComponents() noexcept
	{
		return manager.destroyComponents(id);
	}

	bool Entity::operator==(const Entity& other)
	{
		return id == other.id && manager == other.manager;
	}
	bool Entity::operator!=(const Entity& other)
	{
		return id != other.id && manager != other.manager;
	}
}
