#include "Injector/Graphics/GlCameraSystem.hpp"
#include "Injector/Exception/NullException.hpp"

namespace Injector
{
	GlCameraSystem::GlCameraSystem(GlWindow& _window) :
		window(_window)
	{
	}
	GlCameraSystem::~GlCameraSystem()
	{
	}

	void GlCameraSystem::update()
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
				cameraComponent->matrix = Matrix4::createPerspectiveGl(
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
