#include "Injector/Graphics/GpuImage.hpp"
#include "Injector/Exception/Exception.hpp"

namespace Injector
{
	GpuImage::GpuImage(
		GpuImageType _type,
		GpuImageFormat _format,
		const SizeVector3& _size,
		bool _useMipmap) :
		type(_type),
		format(_format),
		size(_size),
		useMipmap(_useMipmap)
	{
		if(size.x == 0 || size.y == 0 || size.z == 0)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Size x|y|z has zero value");
		}
	}

	GpuImageType GpuImage::getType() const noexcept
	{
		return type;
	}
	GpuImageFormat GpuImage::getFormat() const noexcept
	{
		return format;
	}
	const SizeVector3& GpuImage::getSize() const noexcept
	{
		return size;
	}
	bool GpuImage::isUseMipmap() const noexcept
	{
		return useMipmap;
	}
}
