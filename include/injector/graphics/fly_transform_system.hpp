#pragma once
#include <injector/graphics/window.hpp>
#include <injector/mathematics/transform_component.hpp>

namespace INJECTOR_NAMESPACE
{
	class FlyTransformSystem : public System
	{
	protected:
		WindowHandle window;
		bool rotating;
		Vector3 eulerAngles;
		Vector3 translation;
		Vector3 rotation;
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