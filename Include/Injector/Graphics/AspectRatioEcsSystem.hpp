#pragma once
#include "Injector/Graphics/GpuWindow.hpp"
#include "Injector/Graphics/CameraEcsComponent.hpp"

#include <set>

namespace Injector
{
	class AspectRatioEcsSystem : public EcsSystem
	{
	 protected:
		std::shared_ptr<GpuWindow> window;
		std::set<std::shared_ptr<EcsEntity>> cameras;
	 public:
		explicit AspectRatioEcsSystem(
			const std::shared_ptr<GpuWindow>& window);

		size_t getCameraCount() const noexcept;

		void update() override;

		bool addCamera(
			const std::shared_ptr<EcsEntity>& entity) noexcept;
		bool removeCamera(
			const std::shared_ptr<EcsEntity>& entity) noexcept;
		void removeCameras() noexcept;
	};
}
