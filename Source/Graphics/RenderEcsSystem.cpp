#include "Injector/Graphics/RenderEcsSystem.hpp"
#include "Injector/Engine.hpp"

#include <stdexcept>

namespace Injector
{
	RenderEcsSystem::RenderEcsSystem() :
		cameras()
	{
	}

	size_t RenderEcsSystem::getCameraCount() const noexcept
	{
		return cameras.size();
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
