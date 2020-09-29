#pragma once
#include "Injector/Graphics/RenderSystem.hpp"
#include "Injector/Graphics/GlWindow.hpp"

// TMP:
#include "Injector/Graphics/GlGpuFramebuffer.hpp"
#include "openvr.h"

namespace Injector
{
	class GlRenderSystem : public RenderSystem
	{
	 protected:
		GlWindow& window;

		// TMP:
		std::shared_ptr<GlGpuFramebuffer> leftFramebuffer;
		std::shared_ptr<GlGpuFramebuffer> rightFramebuffer;
		GLuint leftTexture;
		GLuint rightTexture;
	 public:
		GlRenderSystem(GlWindow& window);
		virtual ~GlRenderSystem();

		void draw();
		void update() override;
	};
}
