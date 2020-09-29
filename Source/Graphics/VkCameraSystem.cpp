#include "Injector/Graphics/VkCameraSystem.hpp"

namespace Injector
{
	VkCameraSystem::VkCameraSystem(
		VkWindow& _window) :
		window(_window)
	{
	}

	void VkCameraSystem::update()
	{
		auto windowSize = window.getSize();
		updateAspectRatio(windowSize.x / float(windowSize.y));

		for (auto& camera : cameras)
		{
			CameraComponent* cameraComponent;

			if (!camera->getComponent(cameraComponent))
				continue;

			if (cameraComponent->type == CameraType::Perspective)
			{
				cameraComponent->matrix = Matrix4::createPerspectiveVk(
					cameraComponent->fieldOfView,
					cameraComponent->aspectRatio,
					cameraComponent->clipPlane.x,
					cameraComponent->clipPlane.y);
			}
			else if(cameraComponent->type == CameraType::Orthographic)
			{
				cameraComponent->matrix = Matrix4::createOrthographicGl(
					cameraComponent->frustum.x,
					cameraComponent->frustum.y,
					cameraComponent->frustum.z,
					cameraComponent->frustum.w,
					cameraComponent->clipPlane.x,
					cameraComponent->clipPlane.y);
			}
		}
	}
}