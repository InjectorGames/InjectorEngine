#pragma once
#include <injector/manager.hpp>
#include <injector/render_component.hpp>
#include <injector/window_component.hpp>
#include <injector/camera_component.hpp>
#include <injector/transform_component.hpp>

namespace INJECTOR_NAMESPACE
{
	class RenderSystem : public System
	{
	protected:
		std::set<EntityHandle> cameras;
		std::set<EntityHandle> renders;
	public:
		EntityHandle window;

		RenderSystem(const EntityHandle& window = nullptr);
		virtual ~RenderSystem();

		void update() override;

		bool addCamera(const EntityHandle& entity) noexcept;
		bool removeCamera(const EntityHandle& entity) noexcept;
		void removeCameras() noexcept;
		size_t getCameraCount() const noexcept;

		bool addRender(const EntityHandle& entity) noexcept;
		bool removeRender(const EntityHandle& entity) noexcept;
		void removeRenders() noexcept;
		size_t getRenderCount() const noexcept;
	};
}
