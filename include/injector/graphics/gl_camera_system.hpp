#pragma once
#include <injector/graphics/camera_system.hpp>
#include <injector/graphics/gl_window.hpp>

namespace injector::graphics
{
	class GlCameraSystem : public CameraSystem
	{
	protected:
		GlWindow& window;
	public:
		GlCameraSystem(GlWindow& window);
		virtual ~GlCameraSystem();

		void update() override;
	};
}
