#pragma once
#include <injector/manager.hpp>
#include <injector/camera_component.hpp>

namespace INJECTOR_NAMESPACE
{
	class CameraSystem final : public System
	{
	private:
		IntVector2 newWindowSize;
		std::set<EntityHandle> cameras;
	public:
		EntityHandle window;

		CameraSystem(const EntityHandle& window = nullptr);

		void update() override;

		bool addCamera(const EntityHandle& entity) noexcept;
		bool removeCamera(const EntityHandle& entity) noexcept;
		void removeCameras() noexcept;
		size_t getCameraCount() const noexcept;
	};
}
