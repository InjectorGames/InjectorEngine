#pragma once
#include "Injector/Graphics/Window.hpp"
#include "Injector/Mathematics/TransformComponent.hpp"

namespace Injector
{
	class FlyTransformSystem : public System
	{
	 protected:
		std::shared_ptr<Window> window;
		bool rotating;
		Vector3 eulerAngles;
		Vector2 lastMousePosition;
	 public:
		std::shared_ptr<Entity> transform;
		float speed;
		float sensitivity;

		FlyTransformSystem(
			const std::shared_ptr<Window>& window);
		virtual ~FlyTransformSystem();

		void update() override;
	};
}