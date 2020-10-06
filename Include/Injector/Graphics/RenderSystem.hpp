#pragma once
#include "Injector/ECS/System.hpp"
#include "Injector/ECS/Entity.hpp"
#include "Injector/Graphics/RenderComponent.hpp"
#include "Injector/Graphics/CameraComponent.hpp"
#include "Injector/Mathematics/TransformComponent.hpp"

#include <set>

namespace Injector
{
	class RenderSystem : public System
	{
	 protected:
		std::set<std::shared_ptr<Entity>> cameras;
	 public:
		RenderSystem();

		size_t getCameraCount() const noexcept;

		bool addCamera(
			const std::shared_ptr<Entity>& entity) noexcept;
		bool removeCamera(
			const std::shared_ptr<Entity>& entity) noexcept;

		void removeCameras() noexcept;
	};
}
