#include "Injector/ECS/EcsEntity.hpp"

namespace Injector
{
	EcsEntity::EcsEntity() noexcept :
		components()
	{
	}
	EcsEntity::~EcsEntity()
	{
		destroyComponents();
	}

	void EcsEntity::destroyComponents() noexcept
	{
		for (auto pair : components)
			delete pair.second;

		components.clear();
	}
	size_t EcsEntity::getComponentCount() const noexcept
	{
		return components.size();
	}
}
