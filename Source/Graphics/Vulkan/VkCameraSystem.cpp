#include "Injector/Graphics/Vulkan/VkCameraSystem.hpp"
#include "Injector/Exception/NullException.hpp"

namespace Injector
{
	VkCameraSystem::VkCameraSystem(
		const std::shared_ptr<VkWindow>& _window) :
		window(_window)
	{
		if(!_window)
		{
			throw NullException(
				"VkCameraSystem",
				"VkCameraSystem",
				"window");
		}
	}

	void VkCameraSystem::update()
	{
		auto windowSize = window->getSize();
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