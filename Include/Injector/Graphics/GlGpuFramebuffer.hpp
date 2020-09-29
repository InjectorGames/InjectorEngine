#pragma once
#include "Injector/Graphics/GpuFramebuffer.hpp"
#include "Injector/Graphics/GlGpuImage.hpp"

namespace Injector
{
	class GlGpuFramebuffer : public GpuFramebuffer
	{
	protected:
		GLuint framebuffer;
	public:
		GlGpuFramebuffer(
			const std::shared_ptr<GlGpuImage>& colorImage,
			const std::shared_ptr<GlGpuImage>& depthImage = nullptr,
			const std::shared_ptr<GlGpuImage>& stencilImage = nullptr);
		~GlGpuFramebuffer() override;

		GLuint getFramebuffer() const noexcept;

		void bind() noexcept;
		void unbind() noexcept;
	};
}
