#pragma once
#include "Injector/Graphics/GpuImageType.hpp"
#include "Injector/Exception/Exception.hpp"

#include "vulkan/vulkan.hpp"

namespace Injector
{
	static vk::ImageType toVkGpuImageType(
		GpuImageType type)
	{
		if(type == GpuImageType::Image1D)
		{
			return vk::ImageType::e1D;
		}
		else if(type == GpuImageType::Image2D)
		{
			return vk::ImageType::e2D;
		}
		else if(type == GpuImageType::Image3D)
		{
			return vk::ImageType::e3D;
		}
		else
		{
			throw Exception(
				"",
				"toVkGpuImageType",
				"Unsupported image type");
		}
	}
}
