#include "Injector/Graphics/GpuImage.hpp"

namespace Injector
{
	GpuImage::GpuImage(
		GpuImageType _type,
		GpuImageFormat _format,
		const IntVector3& _size,
		bool _useMipmap) :
		type(_type),
		format(_format),
		size(_size),
		useMipmap(_useMipmap)
	{
	}

	GpuImageType GpuImage::getType() const noexcept
	{
		return type;
	}
	GpuImageFormat GpuImage::getFormat() const noexcept
	{
		return format;
	}
	const IntVector3& GpuImage::getSize() const noexcept
	{
		return size;
	}
	bool GpuImage::isUseMipmap() const noexcept
	{
		return useMipmap;
	}
}
