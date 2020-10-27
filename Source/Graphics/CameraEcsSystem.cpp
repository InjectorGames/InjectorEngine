#include "Injector/Graphics/CameraEcsSystem.hpp"

namespace Injector
{
	CameraEcsSystem::CameraEcsSystem() noexcept :
		cameras()
	{
	}

	size_t CameraEcsSystem::getCameraCount() const noexcept
	{
		return cameras.size();
	}

	bool CameraEcsSystem::addCamera(
		const std::shared_ptr<EcsEntity>& entity) noexcept
	{
		if (!entity)
			return false;

		return cameras.emplace(entity).second;
	}
	bool CameraEcsSystem::removeCamera(
		const std::shared_ptr<EcsEntity>& entity) noexcept
	{
		if (!entity)
			return false;

		auto iterator = cameras.find(entity);

		if (iterator == cameras.end())
			return false;

		cameras.erase(iterator);
		return true;
	}
	void CameraEcsSystem::removeCameras() noexcept
	{
		cameras.clear();
	}
}
