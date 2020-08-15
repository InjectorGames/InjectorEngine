#pragma once
#include <injector/graphics/camera_system.hpp>
#include <injector/graphics/vk_window.hpp>

namespace INJECTOR_NAMESPACE
{
	class VkCameraSystem : public CameraSystem
	{
	protected:
		VkWindow& window;
	public:
		VkCameraSystem(VkWindow& window);
		virtual ~VkCameraSystem();

		void update() override;
	};
}
