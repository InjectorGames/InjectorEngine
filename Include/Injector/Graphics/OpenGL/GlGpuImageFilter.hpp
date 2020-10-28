#pragma once
#include "Injector/Graphics/GpuImageFilter.hpp"
#include "Injector/Exception/Exception.hpp"
#include "Injector/Graphics/GlfwDefines.hpp"

namespace Injector
{
	static GLint toGlGpuImageFilter(
		GpuImageFilter imageFilter,
		bool useMipmap,
		GpuImageFilter mipmapFilter)
	{
		if (imageFilter == GpuImageFilter::Nearest)
		{
			if (useMipmap)
			{
				if(mipmapFilter == GpuImageFilter::Nearest)
				{
					return GL_NEAREST_MIPMAP_NEAREST;
				}
				else if(mipmapFilter == GpuImageFilter::Linear)
				{
					return GL_NEAREST_MIPMAP_LINEAR;
				}
				else
				{
					throw Exception(
						THIS_FUNCTION_NAME,
						"Unsupported mipmap filter");
				}
			}
			else
			{
				return GL_NEAREST;
			}
		}
		else if (imageFilter == GpuImageFilter::Linear)
		{
			if(mipmapFilter == GpuImageFilter::Nearest)
			{
				return GL_LINEAR_MIPMAP_NEAREST;
			}
			else if(mipmapFilter == GpuImageFilter::Linear)
			{
				return GL_LINEAR_MIPMAP_LINEAR;
			}
			else
			{
				throw Exception(
					THIS_FUNCTION_NAME,
					"Unsupported mipmap filter");
			}
		}
		else
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Unsupported image filter");
		}
	}
}
