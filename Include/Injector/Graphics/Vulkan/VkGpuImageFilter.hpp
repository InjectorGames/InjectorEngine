#pragma once
#include "Injector/Graphics/GpuImageFilter.hpp"
#include "Injector/Exception/Exception.hpp"

#include "vulkan/vulkan.hpp"

namespace Injector
{
	static vk::Filter toVkGpuImageFilter(
		GpuImageFilter filter)
	{
		if(filter == GpuImageFilter::Nearest)
		{
			return vk::Filter::eNearest;
		}
		else if(filter == GpuImageFilter::Linear)
		{
			return vk::Filter::eLinear;
		}
		else
		{
			throw Exception(
				"",
				"toVkGpuImageFilter",
				"Unsupported image filter");
		}
	}
	static vk::SamplerMipmapMode toVkGpuMipmapFilter(
		GpuImageFilter filter)
	{
		if(filter == GpuImageFilter::Nearest)
		{
			return vk::SamplerMipmapMode::eNearest;
		}
		else if(filter == GpuImageFilter::Linear)
		{
			return vk::SamplerMipmapMode::eLinear;
		}
		else
		{
			throw Exception(
				"",
				"toVkGpuMipmapFilter",
				"Unsupported mipmap filter");
		}
	}
}
