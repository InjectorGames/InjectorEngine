#pragma once
#include "Injector/Graphics/CameraEcsSystem.hpp"
#include "Injector/Graphics/OpenGL/GlGpuWindow.hpp"

namespace Injector
{
	class GlCameraEcsSystem : public CameraEcsSystem
	{
	 public:
		void update() override;
	};
}
