#pragma once
#include <injector/graphics/window.hpp>
#include <injector/mathematics/camera_component.hpp>

namespace INJECTOR_NAMESPACE
{

	// TODO: make gl and vk system to use different camera perspective funstions


	class CameraSystem : public System
	{
	protected:
		WindowHandle window;
		IntVector2 lastWindowSize;
		std::set<EntityHandle> cameras;
	public:
		CameraSystem(const WindowHandle& _window);
		virtual ~CameraSystem();

		void update() override;

		bool addCamera(const EntityHandle& entity) noexcept;
		bool removeCamera(const EntityHandle& entity) noexcept;
		void removeCameras() noexcept;
		size_t getCameraCount() const noexcept;
		
		static std::shared_ptr<CameraSystem> create(const WindowHandle& window);
	};

	using CameraSystemHandle = std::shared_ptr<CameraSystem>;
}
