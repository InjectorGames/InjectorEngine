#include "Injector/Graphics/CameraSystem.hpp"

namespace Injector
{
	void CameraSystem::updateAspectRatio(float aspectRatio)
	{
		if (lastAspectRatio != aspectRatio)
		{
			lastAspectRatio = aspectRatio;

			for (auto& camera : cameras)
			{
				CameraComponent* cameraComponent;

				if (!camera->getComponent(cameraComponent))
					continue;

				if (cameraComponent->updateAspect)
					cameraComponent->aspectRatio = aspectRatio;
			}
		}
	}

	CameraSystem::CameraSystem() noexcept :
		cameras(),
		lastAspectRatio()
	{
	}
	CameraSystem::CameraSystem(
		const CameraSystem& system) noexcept
	{
		lastAspectRatio = system.lastAspectRatio;
		cameras = system.cameras;
	}
	CameraSystem::CameraSystem(
		CameraSystem&& system) noexcept
	{
		lastAspectRatio = system.lastAspectRatio;
		cameras = std::move(system.cameras);
	}

	size_t CameraSystem::getCameraCount() const noexcept
	{
		return cameras.size();
	}

	bool CameraSystem::addCamera(
		const std::shared_ptr<Entity>& entity) noexcept
	{
		if (!entity)
			return false;

		return cameras.emplace(entity).second;
	}
	bool CameraSystem::removeCamera(
		const std::shared_ptr<Entity>& entity) noexcept
	{
		if (!entity)
			return false;

		auto iterator = cameras.find(entity);

		if (iterator == cameras.end())
			return false;

		cameras.erase(iterator);
		return true;
	}
	void CameraSystem::removeCameras() noexcept
	{
		cameras.clear();
	}

	CameraSystem& CameraSystem::operator=(
		const CameraSystem& system) noexcept
	{
		if(this != &system)
		{
			lastAspectRatio = system.lastAspectRatio;
			cameras = system.cameras;
		}

		return *this;
	}
	CameraSystem& CameraSystem::operator=(
		CameraSystem&& system) noexcept
	{
		if(this != &system)
		{
			lastAspectRatio = system.lastAspectRatio;
			cameras = std::move(system.cameras);
		}

		return *this;
	}
}
