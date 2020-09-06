#include "Injector/Graphics/CameraSystem.hpp"

namespace Injector::Graphics
{
	CameraSystem::CameraSystem() :
		lastAspectRatio()
	{}
	CameraSystem::~CameraSystem()
	{}

	void CameraSystem::updateAspecRatio(float aspectRatio)
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
				{
					cameraComponent->aspectRatio = aspectRatio;
					cameraComponent->changed = true;
				}
			}
		}
	}

	bool CameraSystem::addCamera(const shared_ptr<Entity>& entity) noexcept
	{
		return cameras.emplace(entity).second;
	}
	bool CameraSystem::removeCamera(const shared_ptr<Entity>& entity) noexcept
	{
		if (entity == nullptr)
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
	size_t CameraSystem::getCameraCount() const noexcept
	{
		return cameras.size();
	}
}
