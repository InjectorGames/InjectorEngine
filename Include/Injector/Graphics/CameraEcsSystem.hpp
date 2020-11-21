#pragma once
#include "Injector/ECS/EcsSystem.hpp"
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
		// Target graphics API perspective function pointer
		FloatMatrix4 (*perspectivePointer)(
			float, float, float, float);
		// Target graphics API orthographic function pointer
		FloatMatrix4 (*orthographicPointer)(
			float, float, float, float, float, float);
	 public:
		// Creates a new camera ECS system
		CameraEcsSystem();

		// Returns camera container
		const std::set<std::shared_ptr<EcsEntity>>&
			getCameras() const noexcept;

		// Updates camera matrices
		void onUpdate() override;

		// Returns true if entity removed from the system
		bool removeEntity(
			const std::shared_ptr<EcsEntity>& entity) override;

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
