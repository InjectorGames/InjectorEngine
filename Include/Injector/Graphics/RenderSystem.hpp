#pragma once
#include "Injector/System.hpp"
#include "Injector/Entity.hpp"
#include "Injector/Graphics/RenderComponent.hpp"
#include "Injector/Graphics/CameraComponent.hpp"
#include "Injector/Mathematics/TransformComponent.hpp"

#include <set>

namespace Injector::Graphics
{
	class RenderSystem : public System
	{
	protected:
		set<shared_ptr<Entity>> cameras;
	public:
		virtual ~RenderSystem();

		size_t getCameraCount() const noexcept;
		bool addCamera(const shared_ptr<Entity>& entity) noexcept;
		bool removeCamera(const shared_ptr<Entity>& entity) noexcept;
		void removeCameras() noexcept;
	};
}
