#pragma once
#include "Injector/Graphics/GpuImageFormat.hpp"
#include "Injector/Exception/Exception.hpp"
#include "Injector/Graphics/GlfwDefines.hpp"

namespace Injector
{
	static GLenum toGlGpuImageFormat(
		GpuImageFormat format)
	{
		switch (format)
		{
		case GpuImageFormat::R8:
			return GL_R8;
		case GpuImageFormat::R8U:
			return GL_R8UI;
		case GpuImageFormat::R8I:
			return GL_R8I;
		case GpuImageFormat::RG8:
			return GL_RG8;
		case GpuImageFormat::RG8U:
			return GL_RG8UI;
		case GpuImageFormat::RG8I:
			return GL_RG8I;
		case GpuImageFormat::RGB8:
			return GL_RGB8;
		case GpuImageFormat::RGB8U:
			return GL_RGB8UI;
		case GpuImageFormat::RGB8I:
			return GL_RGB8I;
		case GpuImageFormat::RGBA8:
			return GL_RGBA8;
		case GpuImageFormat::RGBA8U:
			return GL_RGBA8UI;
		case GpuImageFormat::RGBA8I:
			return GL_RGBA8I;
		case GpuImageFormat::R16F:
			return GL_R16F;
		case GpuImageFormat::R16U:
			return GL_R16UI;
		case GpuImageFormat::R16I:
			return GL_R16I;
		case GpuImageFormat::RG16F:
			return GL_RG16F;
		case GpuImageFormat::RG16U:
			return GL_RG16UI;
		case GpuImageFormat::RG16I:
			return GL_RG16I;
		case GpuImageFormat::RGB16F:
			return GL_RGB16F;
		case GpuImageFormat::RGB16U:
			return GL_RGB16UI;
		case GpuImageFormat::RGB16I:
			return GL_RGB16I;
		case GpuImageFormat::RGBA16F:
			return GL_RGBA16F;
		case GpuImageFormat::RGBA16U:
			return GL_RGBA16UI;
		case GpuImageFormat::RGBA16I:
			return GL_RGBA16I;
		case GpuImageFormat::R32F:
			return GL_R32F;
		case GpuImageFormat::R32U:
			return GL_R32UI;
		case GpuImageFormat::R32I:
			return GL_R32I;
		case GpuImageFormat::RG32F:
			return GL_RG32F;
		case GpuImageFormat::RG32U:
			return GL_RG32UI;
		case GpuImageFormat::RG32I:
			return GL_RG32I;
		case GpuImageFormat::RGB32F:
			return GL_RGB32F;
		case GpuImageFormat::RGB32U:
			return GL_RGB32UI;
		case GpuImageFormat::RGB32I:
			return GL_RGB32I;
		case GpuImageFormat::RGBA32F:
			return GL_RGBA32F;
		case GpuImageFormat::RGBA32U:
			return GL_RGBA32UI;
		case GpuImageFormat::RGBA32I:
			return GL_RGBA32I;
		case GpuImageFormat::D16:
			return GL_DEPTH_COMPONENT16;
		case GpuImageFormat::D32:
			return GL_DEPTH_COMPONENT32F;
		case GpuImageFormat::D24S8:
			return GL_DEPTH24_STENCIL8;
		case GpuImageFormat::D32S8:
			return GL_DEPTH32F_STENCIL8;
		default:
			throw Exception(
				"",
				"toGlGpuImageFormat",
				"Unsupported image format");
		}
	}
}
