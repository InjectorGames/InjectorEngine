#include "Injector/Graphics/CameraEcsSystem.hpp"
#include "Injector/Engine.hpp"
#include "Injector/Exception/Exception.hpp"

namespace Injector
{
	CameraEcsSystem::CameraEcsSystem() :
		cameras()
	{
		auto graphicsAPI = Engine::getGraphicsAPI();

		if(graphicsAPI == GraphicsAPI::Vulkan)
		{
			perspectivePointer = vkCreatePerspectiveMatrix;
			orthographicPointer = vkCreateOrthographicMatrix;
		}
		else if(graphicsAPI == GraphicsAPI::OpenGL ||
			graphicsAPI == GraphicsAPI::OpenGLES)
		{
			perspectivePointer = glCreatePerspectiveMatrix;
			orthographicPointer = glCreateOrthographicMatrix;
		}
		else
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Unsupported graphics API");
		}
	}

	const std::set<std::shared_ptr<EcsEntity>>&
		CameraEcsSystem::getCameras() const noexcept
	{
		return cameras;
	}

	void CameraEcsSystem::onUpdate()
	{
		for (auto& camera : cameras)
		{
			CameraEcsComponent* cameraComponent;

			if (!camera->getComponent(cameraComponent))
				continue;

			if (cameraComponent->type == CameraType::Perspective)
			{
				cameraComponent->matrix = perspectivePointer(
					cameraComponent->fieldOfView,
					cameraComponent->aspectRatio,
					cameraComponent->clipPlane.x,
					cameraComponent->clipPlane.y);
			}
			else if(cameraComponent->type == CameraType::Orthographic)
			{
				cameraComponent->matrix = orthographicPointer(
					cameraComponent->frustum.x * cameraComponent->aspectRatio,
					cameraComponent->frustum.y * cameraComponent->aspectRatio,
					cameraComponent->frustum.z,
					cameraComponent->frustum.w,
					cameraComponent->clipPlane.x,
					cameraComponent->clipPlane.y);
			}
		}
	}

	bool CameraEcsSystem::removeEntity(
		const std::shared_ptr<EcsEntity>& entity)
	{
		return removeCamera(entity);
	}

	bool CameraEcsSystem::addCamera(
		const std::shared_ptr<EcsEntity>& entity) noexcept
	{
		if (!entity)
			return false;

		return cameras.emplace(entity).second;
	}
	bool CameraEcsSystem::removeCamera(
		const std::shared_ptr<EcsEntity>& entity) noexcept
	{
		if (!entity)
			return false;

		auto iterator = cameras.find(entity);

		if (iterator == cameras.end())
			return false;

		cameras.erase(iterator);
		return true;
	}
	void CameraEcsSystem::removeCameras() noexcept
	{
		cameras.clear();
	}
}
