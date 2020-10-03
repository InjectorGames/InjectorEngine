#pragma once
#include "Injector/System.hpp"
#include "Injector/Entity.hpp"
#include "Injector/Graphics/CameraComponent.hpp"

#include <set>

namespace Injector
{
	class CameraSystem : public System
	{
	 protected:
		float lastAspectRatio;
		std::set<std::shared_ptr<Entity>> cameras;

		void updateAspectRatio(float aspectRatio);
	 public:
		CameraSystem() noexcept;

		size_t getCameraCount() const noexcept;

		bool addCamera(
			const std::shared_ptr<Entity>& entity) noexcept;
		bool removeCamera(
			const std::shared_ptr<Entity>& entity) noexcept;
		void removeCameras() noexcept;
	};
}
