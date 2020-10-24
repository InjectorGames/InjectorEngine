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
				"AspectRatioSystem",
				"AspectRatioSystem",
				"window");
		}
	}

	size_t AspectRatioEcsSystem::getCameraCount() const noexcept
	{
		return cameras.size();
	}

	void AspectRatioEcsSystem::update()
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