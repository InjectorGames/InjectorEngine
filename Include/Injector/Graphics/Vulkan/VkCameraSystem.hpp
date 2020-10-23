#pragma once
#include "Injector/Graphics/CameraSystem.hpp"
#include "Injector/Graphics/Vulkan/VkWindow.hpp"

namespace Injector
{
	class VkCameraSystem : public CameraSystem
	{
	 protected:
		std::shared_ptr<VkWindow> window;
	 public:
		explicit VkCameraSystem(
			const std::shared_ptr<VkWindow>& window);

		void update() override;
	};
}
