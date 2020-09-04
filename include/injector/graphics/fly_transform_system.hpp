#pragma once
#include <injector/graphics/window.hpp>
#include <injector/mathematics/transform_component.hpp>

namespace injector::graphics
{
	class FlyTransformSystem : public System
	{
	protected:
		WindowHandle window;
		bool rotating;
		Vector3 eulerAngles;
	public:
		EntityHandle transform;
		float speed;
		float sensitivity;

		FlyTransformSystem(
			const WindowHandle& window);
		virtual ~FlyTransformSystem();

		void update() override;
	};
}