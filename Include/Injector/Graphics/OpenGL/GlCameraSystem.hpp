#pragma once
#include "Injector/Graphics/CameraSystem.hpp"
#include "Injector/Graphics/OpenGL/GlWindow.hpp"

namespace Injector
{
	class GlCameraSystem : public CameraSystem
	{
	 protected:
		std::shared_ptr<GlWindow> window;
	 public:
		explicit GlCameraSystem(
			const std::shared_ptr<GlWindow>& window);

		void update() override;
	};
}
