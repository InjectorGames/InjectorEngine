#pragma once
#include "Injector/Graphics/GpuWindow.hpp"
#include "Injector/Mathematics/TransformEcsComponent.hpp"

namespace Injector
{
	// Free view camera ECS system class
	class FreeCameraEcsSystem : public EcsSystem
	{
	 protected:
		// System window value
		std::shared_ptr<GpuWindow> window;
		// TODO: remove mouse capture
		bool rotating;
		// Camera euler angles value
		Vector3 eulerAngles;
		// Camera last mouse position value
		Vector2 lastMousePosition;
	 public:
		// Update camera value
		std::shared_ptr<EcsEntity> camera;

		// Camera translation speed
		float speed;
		// Camera rotation sensitivity
		float sensitivity;

		// Creates a new free camera ECs system
		explicit FreeCameraEcsSystem(
			const std::shared_ptr<GpuWindow>& window);

		// Returns system window value
		const std::shared_ptr<GpuWindow>&
			getWindow() const noexcept;

		// Updates camera translation and rotation
		void onUpdate() override;
	};
}