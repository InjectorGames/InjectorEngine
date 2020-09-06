#pragma once
#include "Injector/Graphics/RenderSystem.hpp"
#include "Injector/Graphics/GlWindow.hpp"

namespace Injector::Graphics
{
	class GlRenderSystem : public RenderSystem
	{
	protected:
		GlWindow& window;
	public:
		GlRenderSystem(GlWindow& window);
		virtual ~GlRenderSystem();

		void update() override;
	};
}
