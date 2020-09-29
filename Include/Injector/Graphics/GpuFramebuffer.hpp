#pragma once
#include "Injector/Graphics/GpuImage.hpp"
#include <memory>

namespace Injector
{
	class GpuFramebuffer
	{
	protected:
		std::shared_ptr<GpuImage> colorImage;
		std::shared_ptr<GpuImage> depthImage;
		std::shared_ptr<GpuImage> stencilImage;
	public:
		GpuFramebuffer(
			const std::shared_ptr<GpuImage>& colorImage,
			const std::shared_ptr<GpuImage>& depthImage,
			const std::shared_ptr<GpuImage>& stencilImage);
		virtual ~GpuFramebuffer() = default;

		std::shared_ptr<GpuImage> getColorImage() const noexcept;
		std::shared_ptr<GpuImage> getDepthImage() const noexcept;
		std::shared_ptr<GpuImage> getStencilImage() const noexcept;
	};
}
