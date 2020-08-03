#include <injector/camera_system.hpp>

namespace INJECTOR_NAMESPACE
{
	CameraSystem::CameraSystem(
		const EntityHandle& _window) :
		window(_window),
		newWindowSize()
	{}

	void CameraSystem::update()
	{
		for (auto& camera : cameras)
		{
			CameraComponent* cameraComponent;

			if (!camera->getComponent(cameraComponent) || !cameraComponent->changed)
				continue;

			if (cameraComponent->type == CameraComponent::Type::Perspective)
			{
				cameraComponent->matrix = Matrix4::createPerspectiveNO(
					cameraComponent->fieldOfView, cameraComponent->aspectRatio,
					cameraComponent->clipPlane.x, cameraComponent->clipPlane.y);
				cameraComponent->changed = false;
			}
			else
			{
				/*cameraComponent->matrix = glm::ortho(
					camera.frustum.x, camera.frustum.y,
					camera.frustum.z, camera.frustum.w,
					camera.clipPlane.x, camera.clipPlane.y);*/
				cameraComponent->changed = false;
			}
		}

		/*if (newAspectRatio != 0.0f)
		{
			auto aspectRatio = newAspectRatio;
			newAspectRatio = 0.0f;

			entities.each<PerspCameraComponent>(
				[aspectRatio](entityx::Entity entity, PerspCameraComponent& camera)
				{
					if (camera.updateAspectRatio)
					{
						camera.aspectRatio = aspectRatio;
						camera.changed = true;
					}
				});
		}*/
	}

	void receive()
	{
		//newAspectRatio = event.size.x / float(event.size.y);
	}

	bool CameraSystem::addCamera(const EntityHandle& entity) noexcept
	{
		if (entity == nullptr || !entity->containsComponent<CameraComponent>())
			return false;

		return cameras.emplace(entity).second;
	}
	bool CameraSystem::removeCamera(const EntityHandle& entity) noexcept
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
