#pragma once
//#include <inject/keyboard_event.hpp>
//#include <inject/mouse_motion_event.hpp>
//#include <inject/mouse_button_event.hpp>
#include <injector/system.hpp>
#include <injector/entity.hpp>
#include <injector/graphics/camera_component.hpp>
#include <injector/mathematics/transform_component.hpp>


namespace INJECTOR_NAMESPACE
{
	class FlyCameraSystem : public System
	{
	private:
		bool rotating;
		Vector3 eulerAngles;
		Vector3 translation;
		Vector3 rotation;
	public:
		bool clampPitch;
		float speed;
		float sensitivity;
		EntityHandle camera;

		FlyCameraSystem();
		virtual ~FlyCameraSystem();

		void update() override;
	};
}