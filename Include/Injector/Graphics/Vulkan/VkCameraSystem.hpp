#pragma once
#include "Injector/Graphics/CameraEcsSystem.hpp"
#include "Injector/Graphics/Vulkan/VkGpuWindow.hpp"

namespace Injector
{
	class VkCameraSystem : public CameraEcsSystem
	{
	 public:
		void update() override;
	};
}
