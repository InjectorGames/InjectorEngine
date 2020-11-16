#include "Injector/Graphics/RenderEcsSystem.hpp"
#include "Injector/Engine.hpp"

#include <stdexcept>

namespace Injector
{
	RenderEcsSystem::RenderEcsSystem() noexcept :
		cameras()
	{
	}

	const std::set<std::shared_ptr<EcsEntity>>&
		RenderEcsSystem::getCameras() const noexcept
	{
		return cameras;
	}

	bool RenderEcsSystem::addCamera(
		const std::shared_ptr<EcsEntity>& entity) noexcept
	{
		if (entity == nullptr)
			return false;

		return cameras.emplace(entity).second;
	}
	bool RenderEcsSystem::removeCamera(
		const std::shared_ptr<EcsEntity>& entity) noexcept
	{
		if (entity == nullptr)
			return false;

		auto iterator = cameras.find(entity);

		if (iterator == cameras.end())
			return false;

		cameras.erase(iterator);
		return true;
	}

	void RenderEcsSystem::removeCameras() noexcept
	{
		cameras.clear();
	}
}
