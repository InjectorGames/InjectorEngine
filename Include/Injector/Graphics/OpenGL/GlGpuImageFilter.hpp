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
						"std::string(typeid(*this).name())",
						std::string(__func__),
						std::to_string(__LINE__),
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
					"",
					std::string(__func__),
					std::to_string(__LINE__),
					"Unsupported mipmap filter");
			}
		}
		else
		{
			throw Exception(
				"",
				std::string(__func__),
				std::to_string(__LINE__),
				"Unsupported image filter");
		}
	}
}
