#pragma once
#include "Injector/Graphics/CameraEcsSystem.hpp"
#include "Injector/Graphics/OpenGL/GlGpuWindow.hpp"

namespace Injector
{
	// OpenGL camera ECS system class
	class GlCameraEcsSystem : public CameraEcsSystem
	{
	 public:
		// Updates OpenGL camera view and projection matrices
		void update() override;
	};
}
