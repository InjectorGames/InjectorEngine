#pragma once
#include "Injector/Graphics/CameraEcsSystem.hpp"
#include "Injector/Graphics/Vulkan/VkGpuWindow.hpp"

namespace Injector
{
	// Vulkan camera ECS system class
	class VkCameraEcsSystem : public CameraEcsSystem
	{
	 public:
		// Updates Vulkan camera view and projection matrices
		void update() override;
	};
}
