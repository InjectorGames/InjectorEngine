#pragma once
#include <injector/manager.hpp>
#include <injector/window.hpp>

namespace INJECTOR_NAMESPACE
{
	class RenderSystem : public System
	{
	public:
		EntityHandle window;

		RenderSystem(Manager& manager, const EntityHandle& window = {});
		virtual ~RenderSystem();

		void update() override;
	};
}
