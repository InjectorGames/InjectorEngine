#pragma once
#include "Injector/Graphics/GpuWindow.hpp"
#include "Injector/Mathematics/TransformEcsComponent.hpp"

namespace Injector
{
	class FreeCameraEcsSystem : public EcsSystem
	{
	 protected:
		std::shared_ptr<GpuWindow> window;
		// TODO: remove mouse capture
		bool rotating;
		Vector3 eulerAngles;
		Vector2 lastMousePosition;
	 public:
		std::shared_ptr<EcsEntity> camera;

		float speed;
		float sensitivity;

		explicit FreeCameraEcsSystem(
			const std::shared_ptr<GpuWindow>& window);

		void update() override;
	};
}