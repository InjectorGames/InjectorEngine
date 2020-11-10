#pragma once
#include "Injector/ECS/EcsSystem.hpp"
#include "Injector/ECS/EcsEntity.hpp"
#include "Injector/Graphics/CameraEcsComponent.hpp"

#include <set>

namespace Injector
{
	// Camera ECS system class
	class CameraEcsSystem : public EcsSystem
	{
	 protected:
		// Update camera container
		std::set<std::shared_ptr<EcsEntity>> cameras;
	 public:
		// Creates a new camera ECS system
		CameraEcsSystem() noexcept;

		// Returns camera container
		const std::set<std::shared_ptr<EcsEntity>>&
			getCameras() const noexcept;

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
