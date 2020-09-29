#include "Injector/Graphics/GpuImage.hpp"

namespace Injector
{
	GpuImage::GpuImage(
		GpuImageType _type,
		IntVector3 _size,
		GpuImageFormat _format,
		GpuImageFilter _minFilter,
		GpuImageFilter _magFilter,
		GpuImageWrap _wrapU,
		GpuImageWrap _wrapV,
		GpuImageWrap _wrapW,
		bool _useMipmap) :
		type(_type),
		size(_size),
		format(_format),
		minFilter(_minFilter),
		magFilter(_magFilter),
		wrapU(_wrapU),
		wrapV(_wrapV),
		wrapW(_wrapW),
		useMipmap(_useMipmap)
	{
	}

	GpuImageType GpuImage::getType() const noexcept
	{
		return type;
	}
	const IntVector3& GpuImage::getSize() const noexcept
	{
		return size;
	}
	GpuImageFilter GpuImage::getMinFilter() const noexcept
	{
		return minFilter;
	}
	GpuImageFilter GpuImage::getMagFilter() const noexcept
	{
		return magFilter;
	}
	GpuImageWrap GpuImage::getWrapU() const noexcept
	{
		return wrapU;
	}
	GpuImageWrap GpuImage::getWrapV() const noexcept
	{
		return wrapV;
	}
	GpuImageWrap GpuImage::getWrapW() const noexcept
	{
		return wrapW;
	}
	bool GpuImage::isUseMipmap() const noexcept
	{
		return useMipmap;
	}
}
