#pragma once
#include <injector/graphics/window.hpp>
#include <injector/graphics/render_component.hpp>
#include <injector/mathematics/camera_component.hpp>
#include <injector/mathematics/transform_component.hpp>

#include <set>

namespace INJECTOR_NAMESPACE
{
	class RenderSystem : public System
	{
	protected:
		std::set<EntityHandle> cameras;
		std::set<EntityHandle> renders;
	public:
		virtual ~RenderSystem();

		virtual WindowHandle getWindow() const;

		size_t getCameraCount() const noexcept;
		size_t getRenderCount() const noexcept;

		bool addCamera(const EntityHandle& entity) noexcept;
		bool addRender(const EntityHandle& entity) noexcept;

		bool removeCamera(const EntityHandle& entity) noexcept;
		bool removeRender(const EntityHandle& entity) noexcept;

		void removeCameras() noexcept;
		void removeRenders() noexcept;

		static std::shared_ptr<RenderSystem> create(const WindowHandle& window);
	};

	using RenderSystemHandle = std::shared_ptr<RenderSystem>;
}
