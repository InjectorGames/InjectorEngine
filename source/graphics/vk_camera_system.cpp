#include <injector/graphics/vk_camera_system.hpp>

namespace INJECTOR_NAMESPACE
{
	VkCameraSystem::VkCameraSystem(VkWindow& _window) :
		window(_window)
	{}
	VkCameraSystem::~VkCameraSystem()
	{}

	void VkCameraSystem::update()
	{
		auto windowSize = window.getSize();
		updateAspecRatio(windowSize.x / float(windowSize.y));

		for (auto& camera : cameras)
		{
			CameraComponent* cameraComponent;

			if (!camera->getComponent(cameraComponent) || !cameraComponent->changed)
				continue;

			if (cameraComponent->type == CameraComponent::Type::Perspective)
			{
				cameraComponent->matrix = Matrix4::createPerspectiveZO(
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
	}
}