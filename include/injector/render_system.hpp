#pragma once
#include <injector/manager.hpp>

namespace INJECTOR_NAMESPACE
{
	class RenderSystem : public System
	{
	public:
		EntityHandle window;

		RenderSystem(const EntityHandle& window = {});
		virtual ~RenderSystem();

		void update() override;


	};
}
