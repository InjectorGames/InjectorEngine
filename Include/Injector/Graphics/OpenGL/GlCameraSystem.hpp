#pragma once
#include "Injector/Graphics/CameraSystem.hpp"
#include "GlWindow.hpp"

namespace Injector
{
	class GlCameraSystem : public CameraSystem
	{
	 protected:
		GlWindow& window;
	 public:
		explicit GlCameraSystem(
			GlWindow& window);

		void update() override;
	};
}
