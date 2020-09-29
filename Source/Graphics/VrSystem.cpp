#include "Injector/Graphics/VrSystem.hpp"
#include "Injector/Engine.hpp"

namespace Injector
{
	void VrSystem::update()
	{
		CameraComponent* cameraComponent;

		if(!hmd || !hmd->getComponent(cameraComponent))
			return;

		cameraComponent->matrix =
			Engine::getLeftEyeProjMatrix() *
			Engine::getLeftEyeModelMatrix() *
			Engine::getHmdModelMatrix() *
			// TMP:
			Matrix4::identity.getTranslated(Vector3(4.0f, 0.0f, 4.0f));
	}
}
