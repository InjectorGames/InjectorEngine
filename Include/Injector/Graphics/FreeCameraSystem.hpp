#pragma once
#include "Injector/Graphics/Window.hpp"
#include "Injector/Mathematics/TransformComponent.hpp"

namespace Injector
{
	class FreeCameraSystem : public System
	{
	 protected:
		std::shared_ptr<Window> window;
		bool rotating;
		Vector3 eulerAngles;
		Vector2 lastMousePosition;
	 public:
		std::shared_ptr<Entity> camera;

		float speed;
		float sensitivity;

		explicit FreeCameraSystem(
			const std::shared_ptr<Window>& window);

		void update() override;
	};
}