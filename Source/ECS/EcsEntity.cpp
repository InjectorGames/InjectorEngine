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

	const std::map<std::type_index, EcsComponent *>&
	    EcsEntity::getComponents() const noexcept
	{
		return components;
	}

	void EcsEntity::destroyComponents() noexcept
	{
		for (auto pair : components)
			delete pair.second;

		components.clear();
	}

	std::shared_ptr<EcsEntity> EcsEntity::create() noexcept
	{
		return std::make_shared<EcsEntity>();
	}
}
