#pragma once
#include "Injector/Graphics/GpuImageType.hpp"
#include "Injector/Exception/Exception.hpp"
#include "Injector/Graphics/GlfwDefines.hpp"

namespace Injector
{
	static GLenum toGlGpuImageType(
		GpuImageType type)
	{
		if (type == GpuImageType::Image1D)
		{
			return GL_TEXTURE_1D;
		}
		else if (type == GpuImageType::Image2D)
		{
			return GL_TEXTURE_2D;
		}
		else if (type == GpuImageType::Image3D)
		{
			return GL_TEXTURE_3D;
		}
		else
		{
			throw Exception(
				"",
				"toGlGpuImageType",
				"Unsupported image type");
		}
	}
}
