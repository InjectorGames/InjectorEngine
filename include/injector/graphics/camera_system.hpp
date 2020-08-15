#pragma once
#include <injector/system.hpp>
#include <injector/entity.hpp>
#include <injector/graphics/camera_component.hpp>

#include <set>

namespace INJECTOR_NAMESPACE
{
	class CameraSystem : public System
	{
	protected:
		float lastAspectRatio;
		std::set<EntityHandle> cameras;
	public:
		CameraSystem();
		virtual ~CameraSystem();

		void updateAspecRatio(float aspectRatio);

		bool addCamera(const EntityHandle& entity) noexcept;
		bool removeCamera(const EntityHandle& entity) noexcept;
		void removeCameras() noexcept;
		size_t getCameraCount() const noexcept;
	};

	using CameraSystemHandle = std::shared_ptr<CameraSystem>;
}
