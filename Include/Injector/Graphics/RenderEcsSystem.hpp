#pragma once
#include "Injector/ECS/EcsSystem.hpp"
#include "Injector/ECS/EcsEntity.hpp"
#include "Injector/Graphics/GuiEcsComponent.hpp"
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
		std::set<std::shared_ptr<EcsEntity>> guis;
	 public:
		RenderEcsSystem() noexcept;

		const std::set<std::shared_ptr<EcsEntity>>&
			getCameras() const noexcept;
		const std::set<std::shared_ptr<EcsEntity>>&
			getGuis() const noexcept;

		bool addCamera(
			const std::shared_ptr<EcsEntity>& entity) noexcept;
		bool removeCamera(
			const std::shared_ptr<EcsEntity>& entity) noexcept;

		bool addGui(
			const std::shared_ptr<EcsEntity>& entity) noexcept;
		bool removeGui(
			const std::shared_ptr<EcsEntity>& entity) noexcept;

		void removeCameras() noexcept;
		void removeGuis() noexcept;
	};
}
