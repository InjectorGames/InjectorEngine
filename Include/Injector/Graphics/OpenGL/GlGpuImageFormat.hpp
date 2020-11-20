#pragma once
#include "Injector/Graphics/GpuImageFormat.hpp"
#include "Injector/Exception/Exception.hpp"
#include "Injector/GlfwDefines.hpp"

namespace Injector
{
	static GLenum toGlGpuImageFormat(
		GpuImageFormat format)
	{
		switch (format)
		{
		case GpuImageFormat::R8UNORM:
			return GL_R8;
		case GpuImageFormat::R8SNORM:
			return GL_R8_SNORM;
		case GpuImageFormat::R8UINT:
			return GL_R8UI;
		case GpuImageFormat::R8SINT:
			return GL_R8I;
		case GpuImageFormat::R8G8UNORM:
			return GL_RG8;
		case GpuImageFormat::R8G8SNORM:
			return GL_RG8_SNORM;
		case GpuImageFormat::R8G8UINT:
			return GL_RG8UI;
		case GpuImageFormat::R8G8SINT:
			return GL_RG8I;
		case GpuImageFormat::R8G8B8SRGB:
			return GL_SRGB8;
		case GpuImageFormat::R8G8B8UNORM:
			return GL_RGB8;
		case GpuImageFormat::R8G8B8SNORM:
			return GL_RGB8_SNORM;
		case GpuImageFormat::R8G8B8UINT:
			return GL_RGB8UI;
		case GpuImageFormat::R8G8B8SINT:
			return GL_RGB8I;
		case GpuImageFormat::R8G8B8A8SRGB:
			return GL_SRGB8_ALPHA8;
		case GpuImageFormat::R8G8B8A8UNORM:
			return GL_RGBA8;
		case GpuImageFormat::R8G8B8A8SNORM:
			return GL_RGBA8_SNORM;
		case GpuImageFormat::R8G8B8A8UINT:
			return GL_RGBA8UI;
		case GpuImageFormat::R8G8B8A8SINT:
			return GL_RGBA8I;
		case GpuImageFormat::R16SFLOAT:
			return GL_R16F;
		case GpuImageFormat::R16UINT:
			return GL_R16UI;
		case GpuImageFormat::R16SINT:
			return GL_R16I;
		case GpuImageFormat::R16G16SFLOAT:
			return GL_RG16F;
		case GpuImageFormat::R16G16UINT:
			return GL_RG16UI;
		case GpuImageFormat::R16G16SINT:
			return GL_RG16I;
		case GpuImageFormat::R16G16B16SFLOAT:
			return GL_RGB16F;
		case GpuImageFormat::R16G16B16UINT:
			return GL_RGB16UI;
		case GpuImageFormat::R16G16B16SINT:
			return GL_RGB16I;
		case GpuImageFormat::R16G16B16A16SFLOAT:
			return GL_RGBA16F;
		case GpuImageFormat::R16G16B16A16UINT:
			return GL_RGBA16UI;
		case GpuImageFormat::R16G16B16A16SINT:
			return GL_RGBA16I;
		case GpuImageFormat::R32SFLOAT:
			return GL_R32F;
		case GpuImageFormat::R32UINT:
			return GL_R32UI;
		case GpuImageFormat::R32SINT:
			return GL_R32I;
		case GpuImageFormat::R32G32SFLOAT:
			return GL_RG32F;
		case GpuImageFormat::R32G32UINT:
			return GL_RG32UI;
		case GpuImageFormat::R32G32SINT:
			return GL_RG32I;
		case GpuImageFormat::R32G32B32SFLOAT:
			return GL_RGB32F;
		case GpuImageFormat::R32G32B32UINT:
			return GL_RGB32UI;
		case GpuImageFormat::R32G32B32SINT:
			return GL_RGB32I;
		case GpuImageFormat::R32G32B32A32SFLOAT:
			return GL_RGBA32F;
		case GpuImageFormat::R32G32B32A32UINT:
			return GL_RGBA32UI;
		case GpuImageFormat::R32G32B32A32SINT:
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
				THIS_FUNCTION_NAME,
				"Unsupported image format");
		}
	}
}
