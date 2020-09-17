#include "Injector/Graphics/GlCameraSystem.hpp"

namespace Injector
{
	GlCameraSystem::GlCameraSystem(GlWindow& _window) :
		window(_window)
	{}
	GlCameraSystem::~GlCameraSystem()
	{}

	void GlCameraSystem::update()
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
				cameraComponent->matrix = Matrix4::createPerspectiveGl(
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
