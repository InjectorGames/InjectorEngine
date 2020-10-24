#pragma once
#include "Injector/Graphics/GpuWindow.hpp"
#include "Injector/Graphics/CameraEcsComponent.hpp"

#include <set>

namespace Injector
{
	// Camera aspect ratio ECS system
	class AspectRatioEcsSystem : public EcsSystem
	{
	 protected:
		// System window value
		std::shared_ptr<GpuWindow> window;
		// System update camera container
		std::set<std::shared_ptr<EcsEntity>> cameras;
	 public:
		// Creates a new camera aspect ratio ECS system
		explicit AspectRatioEcsSystem(
			const std::shared_ptr<GpuWindow>& window);

		// Returns update camera count
		size_t getCameraCount() const noexcept;

		// Updates camera aspect ratio value
		void update() override;

		// Returns true if camera was added
		bool addCamera(
			const std::shared_ptr<EcsEntity>& entity) noexcept;
		// Returns true if camera was removed
		bool removeCamera(
			const std::shared_ptr<EcsEntity>& entity) noexcept;
		// Removes all cameras
		void removeCameras() noexcept;
	};
}
