#include "Injector/Graphics/GpuFramebuffer.hpp"
#include "Injector/Exception/NullException.hpp"

namespace Injector
{
	GpuFramebuffer::GpuFramebuffer(
		const std::shared_ptr<GpuImage>& _colorImage,
		const std::shared_ptr<GpuImage>& _depthImage,
		const std::shared_ptr<GpuImage>& _stencilImage) :
		colorImage(_colorImage),
		depthImage(_depthImage),
		stencilImage(_stencilImage)
	{
		if(!_colorImage)
		{
			throw NullException(
				std::string(typeid(GpuFramebuffer).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"colorImage");
		}
	}

	std::shared_ptr<GpuImage> GpuFramebuffer::getColorImage() const noexcept
	{
		return colorImage;
	}
	std::shared_ptr<GpuImage> GpuFramebuffer::getDepthImage() const noexcept
	{
		return depthImage;
	}
	std::shared_ptr<GpuImage> GpuFramebuffer::getStencilImage() const noexcept
	{
		return stencilImage;
	}
}
