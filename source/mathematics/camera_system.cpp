#include <injector/mathematics/camera_system.hpp>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	CameraSystem::CameraSystem(const WindowHandle& _window) :
		window(_window),
		lastWindowSize()
	{
		if (!window)
			throw std::runtime_error("Camera system window is null");
	}
	CameraSystem::~CameraSystem()
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

		auto windowSize = window->getSize(); 

		if (lastWindowSize != windowSize)
		{
			auto aspectRatio = windowSize.x / float(windowSize.y);
			lastWindowSize = windowSize;

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

	std::shared_ptr<CameraSystem> CameraSystem::create(const WindowHandle& window)
	{
		return window->createSystem<CameraSystem>(window);
	}
}
