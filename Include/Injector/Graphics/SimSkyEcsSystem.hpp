#pragma once
#include "Injector/ECS/EcsSystem.hpp"
#include "Injector/Graphics/GpuWindow.hpp"

namespace Injector
{
	class SimSkyEcsSystem : public EcsSystem
	{
	 protected:
		std::shared_ptr<GpuWindow> window;

	 public:
		explicit SimSkyEcsSystem(
			const std::shared_ptr<GpuWindow>& window);

		void update() override;
	};
}
