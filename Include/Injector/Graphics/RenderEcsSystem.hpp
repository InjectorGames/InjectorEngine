#pragma once
#include "Injector/ECS/EcsSystem.hpp"
#include "Injector/Graphics/CameraEcsComponent.hpp"
#include "Injector/Graphics/RenderEcsComponent.hpp"
#include "Injector/Mathematics/TransformEcsComponent.hpp"

#include <set>

namespace Injector
{
	class RenderEcsSystem : public EcsSystem
	{
	 protected:
		std::set<std::shared_ptr<EcsEntity>> cameras;
	 public:
		RenderEcsSystem() noexcept;

		const std::set<std::shared_ptr<EcsEntity>>&
			getCameras() const noexcept;

		bool addCamera(
			const std::shared_ptr<EcsEntity>& entity) noexcept;
		bool removeCamera(
			const std::shared_ptr<EcsEntity>& entity) noexcept;

		void removeCameras() noexcept;
	};
}
