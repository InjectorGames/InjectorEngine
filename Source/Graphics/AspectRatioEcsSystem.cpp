#include "Injector/Graphics/AspectRatioEcsSystem.hpp"
#include "Injector/Exception/NullException.hpp"

namespace Injector
{
	AspectRatioEcsSystem::AspectRatioEcsSystem(
		const std::shared_ptr<GpuWindow>& _window) :
		window(_window),
		cameras()
	{
		if (!_window)
		{
			throw NullException(
				THIS_FUNCTION_NAME,
				"window");
		}
	}

	const std::shared_ptr<GpuWindow>&
	    AspectRatioEcsSystem::getWindow() const noexcept
	{
		return window;
	}
	const std::set<std::shared_ptr<EcsEntity>>&
		AspectRatioEcsSystem::getCameras() const noexcept
	{
		return cameras;
	}

	void AspectRatioEcsSystem::onUpdate()
	{
		auto windowSize = window->getSize();
		auto aspectRatio = windowSize.x / float(windowSize.y);

		for (auto& camera : cameras)
		{
			CameraEcsComponent* cameraComponent;

			if (!camera->getComponent(cameraComponent))
				continue;

			cameraComponent->aspectRatio = aspectRatio;
		}
	}

	bool AspectRatioEcsSystem::removeEntity(
		const std::shared_ptr<EcsEntity>& entity)
	{
		return removeCamera(entity);
	}

	bool AspectRatioEcsSystem::addCamera(
		const std::shared_ptr<EcsEntity>& entity) noexcept
	{
		if (!entity)
			return false;

		return cameras.emplace(entity).second;
	}
	bool AspectRatioEcsSystem::removeCamera(
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
	void AspectRatioEcsSystem::removeCameras() noexcept
	{
		cameras.clear();
	}
}