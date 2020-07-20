#include <injector/entity.hpp>

namespace INJECTOR_NAMESPACE
{
	Entity::Entity() :
		components()
	{}
	Entity::~Entity()
	{
		for (auto pair : components)
			delete pair.second;
	}

	void Entity::destroyComponents() noexcept
	{
		for (auto pair : components)
			delete pair.second;

		components.clear();
	}
	size_t Entity::getComponentCount() const noexcept
	{
		return components.size();
	}
}
