#include "Injector/Graphics/VirtualRealityEcsSystem.hpp"
#include "Injector/Engine.hpp"

namespace Injector
{
	void VirtualRealityEcsSystem::onUpdate()
	{
		CameraEcsComponent* cameraComponent;

		if(!hmd || !hmd->getComponent(cameraComponent))
			return;

		cameraComponent->matrix =
			Engine::getLeftEyeProjMatrix() *
			Engine::getLeftEyeModelMatrix() *
			Engine::getHmdModelMatrix() *
			// TMP:
			FloatMatrix4().getTranslated(Vector3(4.0f, 0.0f, 4.0f));
	}
}
