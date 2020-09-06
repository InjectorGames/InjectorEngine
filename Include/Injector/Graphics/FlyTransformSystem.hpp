#pragma once
#include "Injector/Graphics/Window.hpp"
#include "Injector/Mathematics/TransformComponent.hpp"

namespace Injector::Graphics
{
	class FlyTransformSystem : public System
	{
	protected:
		shared_ptr<Window> window;
		bool rotating;
		Vector3 eulerAngles;
	public:
		shared_ptr<Entity> transform;
		float speed;
		float sensitivity;

		FlyTransformSystem(const shared_ptr<Window>& window);
		virtual ~FlyTransformSystem();

		void update() override;
	};
}