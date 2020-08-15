#pragma once
#include <injector/system.hpp>
#include <injector/graphics/render_component.hpp>
#include <injector/graphics/camera_component.hpp>
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

		size_t getCameraCount() const noexcept;
		size_t getRenderCount() const noexcept;

		bool addCamera(const EntityHandle& entity) noexcept;
		bool addRender(const EntityHandle& entity) noexcept;

		bool removeCamera(const EntityHandle& entity) noexcept;
		bool removeRender(const EntityHandle& entity) noexcept;

		void removeCameras() noexcept;
		void removeRenders() noexcept;
	};

	using RenderSystemHandle = std::shared_ptr<RenderSystem>;
}
