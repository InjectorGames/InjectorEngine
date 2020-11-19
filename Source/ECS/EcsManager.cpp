#include "Injector/ECS/EcsManager.hpp"
#include "Injector/Exception/Exception.hpp"

namespace Injector
{
	EcsManager::EcsManager(bool _active) noexcept :
		active(_active),
		systems()
	{
	}

	void EcsManager::onUpdate()
	{
		for (auto system : systems)
			system->onUpdate();
	}

	bool EcsManager::isActive() const noexcept
	{
		return active;
	}

	const std::vector<std::shared_ptr<EcsSystem>>&
		EcsManager::getSystems() const noexcept
	{
		return systems;
	}

	bool EcsManager::removeSystem(
		const std::shared_ptr<EcsSystem>& system) noexcept
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
	bool EcsManager::containsSystem(
		const std::shared_ptr<EcsSystem>& system) const noexcept
	{
		if (system == nullptr)
			return false;

		for (auto& i : systems)
		{
			if (system == i)
				return true;
		}

		return false;
	}
	void EcsManager::removeSystems() noexcept
	{
		systems.clear();
	}

	bool EcsManager::removeEntity(
		const std::shared_ptr<EcsEntity>& entity) noexcept
	{
		bool anyRemove = false;

		for (auto& i : systems)
		{
			if(i->removeEntity(entity))
				anyRemove = true;
		}

		return anyRemove;
	}
}
