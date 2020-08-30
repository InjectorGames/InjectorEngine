#pragma once
#include <injector/system.hpp>
#include <injector/entity.hpp>
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
	public:
		virtual ~RenderSystem();

		size_t getCameraCount() const noexcept;
		bool addCamera(const EntityHandle& entity) noexcept;
		bool removeCamera(const EntityHandle& entity) noexcept;
		void removeCameras() noexcept;
	};

	using RenderSystemHandle = std::shared_ptr<RenderSystem>;
}
