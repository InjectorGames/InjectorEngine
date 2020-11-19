#include "Injector/Graphics/CameraEcsSystem.hpp"

namespace Injector
{
	CameraEcsSystem::CameraEcsSystem() noexcept :
		cameras()
	{
	}

	const std::set<std::shared_ptr<EcsEntity>>&
		CameraEcsSystem::getCameras() const noexcept
	{
		return cameras;
	}

	bool CameraEcsSystem::removeEntity(
		const std::shared_ptr<EcsEntity>& entity)
	{
		return removeCamera(entity);
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
