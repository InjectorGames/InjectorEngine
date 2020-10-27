#pragma once
#include "Injector/ECS/EcsSystem.hpp"
#include "Injector/ECS/EcsEntity.hpp"
#include "Injector/Graphics/RenderEcsComponent.hpp"
#include "Injector/Graphics/CameraEcsComponent.hpp"
#include "Injector/Mathematics/TransformEcsComponent.hpp"

#include <set>

namespace Injector
{
	class RenderEcsSystem : public EcsSystem
	{
	 protected:
		std::set<std::shared_ptr<EcsEntity>> cameras;
	 public:
		RenderEcsSystem();

		size_t getCameraCount() const noexcept;

		bool addCamera(
			const std::shared_ptr<EcsEntity>& entity) noexcept;
		bool removeCamera(
			const std::shared_ptr<EcsEntity>& entity) noexcept;

		void removeCameras() noexcept;
	};
}
