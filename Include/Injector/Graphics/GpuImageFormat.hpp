#pragma once
#include "Injector/Exception/Exception.hpp"
namespace Injector
{
	enum class GpuImageFormat
	{
		R8SRGB,
		R8UNORM,
		R8SNORM,
		R8UINT,
		R8SINT,
		R8G8SRGB,
		R8G8UNORM,
		R8G8SNORM,
		R8G8UINT,
		R8G8SINT,
		R8G8B8SRGB,
		R8G8B8UNORM,
		R8G8B8SNORM,
		R8G8B8UINT,
		R8G8B8SINT,
		R8G8B8A8SRGB,
		R8G8B8A8UNORM,
		R8G8B8A8SNORM,
		R8G8B8A8UINT,
		R8G8B8A8SINT,
		R16SFLOAT,
		R16UNORM,
		R16SNORM,
		R16UINT,
		R16SINT,
		R16G16SFLOAT,
		R16G16UNORM,
		R16G16SNORM,
		R16G16UINT,
		R16G16SINT,
		R16G16B16SFLOAT,
		R16G16B16UNORM,
		R16G16B16SNORM,
		R16G16B16UINT,
		R16G16B16SINT,
		R16G16B16A16SFLOAT,
		R16G16B16A16UNORM,
		R16G16B16A16SNORM,
		R16G16B16A16UINT,
		R16G16B16A16SINT,
		R32SFLOAT,
		R32UINT,
		R32SINT,
		R32G32SFLOAT,
		R32G32UINT,
		R32G32SINT,
		R32G32B32SFLOAT,
		R32G32B32UINT,
		R32G32B32SINT,
		R32G32B32A32SFLOAT,
		R32G32B32A32UINT,
		R32G32B32A32SINT,
		R64SFLOAT,
		R64UINT,
		R64SINT,
		R64G64SFLOAT,
		R64G64UINT,
		R64G64SINT,
		R64G64B64SFLOAT,
		R64G64B64UINT,
		R64G64B64SINT,
		R64G64B64A64SFLOAT,
		R64G64B64A64UINT,
		R64G64B64A64SINT,
		D16,
		D32,
		D16S8,
		D24S8,
		D32S8,
	};

	static size_t getImageFormatComponentCount(
		GpuImageFormat format)
	{
		switch (format)
		{
		case GpuImageFormat::R8SRGB:
		case GpuImageFormat::R8UNORM:
		case GpuImageFormat::R8SNORM:
		case GpuImageFormat::R8UINT:
		case GpuImageFormat::R8SINT:
		case GpuImageFormat::R16SFLOAT:
		case GpuImageFormat::R16UNORM:
		case GpuImageFormat::R16SNORM:
		case GpuImageFormat::R16UINT:
		case GpuImageFormat::R16SINT:
		case GpuImageFormat::R32SFLOAT:
		case GpuImageFormat::R32UINT:
		case GpuImageFormat::R32SINT:
		case GpuImageFormat::R64SFLOAT:
		case GpuImageFormat::R64UINT:
		case GpuImageFormat::R64SINT:
			return 1;
		case GpuImageFormat::R8G8SRGB:
		case GpuImageFormat::R8G8UNORM:
		case GpuImageFormat::R8G8SNORM:
		case GpuImageFormat::R8G8UINT:
		case GpuImageFormat::R8G8SINT:
		case GpuImageFormat::R16G16SFLOAT:
		case GpuImageFormat::R16G16UNORM:
		case GpuImageFormat::R16G16SNORM:
		case GpuImageFormat::R16G16UINT:
		case GpuImageFormat::R16G16SINT:
		case GpuImageFormat::R32G32SFLOAT:
		case GpuImageFormat::R32G32UINT:
		case GpuImageFormat::R32G32SINT:
		case GpuImageFormat::R64G64SFLOAT:
		case GpuImageFormat::R64G64UINT:
		case GpuImageFormat::R64G64SINT:
			return 2;
		case GpuImageFormat::R8G8B8SRGB:
		case GpuImageFormat::R8G8B8UNORM:
		case GpuImageFormat::R8G8B8SNORM:
		case GpuImageFormat::R8G8B8UINT:
		case GpuImageFormat::R8G8B8SINT:
		case GpuImageFormat::R16G16B16SFLOAT:
		case GpuImageFormat::R16G16B16UNORM:
		case GpuImageFormat::R16G16B16SNORM:
		case GpuImageFormat::R16G16B16UINT:
		case GpuImageFormat::R16G16B16SINT:
		case GpuImageFormat::R32G32B32SFLOAT:
		case GpuImageFormat::R32G32B32UINT:
		case GpuImageFormat::R32G32B32SINT:
		case GpuImageFormat::R64G64B64SFLOAT:
		case GpuImageFormat::R64G64B64UINT:
		case GpuImageFormat::R64G64B64SINT:
			return 3;
		case GpuImageFormat::R8G8B8A8SRGB:
		case GpuImageFormat::R8G8B8A8UNORM:
		case GpuImageFormat::R8G8B8A8SNORM:
		case GpuImageFormat::R8G8B8A8UINT:
		case GpuImageFormat::R8G8B8A8SINT:
		case GpuImageFormat::R16G16B16A16SFLOAT:
		case GpuImageFormat::R16G16B16A16UNORM:
		case GpuImageFormat::R16G16B16A16SNORM:
		case GpuImageFormat::R16G16B16A16UINT:
		case GpuImageFormat::R16G16B16A16SINT:
		case GpuImageFormat::R32G32B32A32SFLOAT:
		case GpuImageFormat::R32G32B32A32UINT:
		case GpuImageFormat::R32G32B32A32SINT:
		case GpuImageFormat::R64G64B64A64SFLOAT:
		case GpuImageFormat::R64G64B64A64UINT:
		case GpuImageFormat::R64G64B64A64SINT:
			return 4;
		default:
			throw Exception(
				THIS_FUNCTION_NAME,
				"Unsupported image format");
		}
	}
	static size_t getImageFormatComponentSize(
		GpuImageFormat format)
	{
		switch (format)
		{
		case GpuImageFormat::R8SRGB:
		case GpuImageFormat::R8UNORM:
		case GpuImageFormat::R8SNORM:
		case GpuImageFormat::R8UINT:
		case GpuImageFormat::R8SINT:
		case GpuImageFormat::R8G8SRGB:
		case GpuImageFormat::R8G8UNORM:
		case GpuImageFormat::R8G8SNORM:
		case GpuImageFormat::R8G8UINT:
		case GpuImageFormat::R8G8SINT:
		case GpuImageFormat::R8G8B8SRGB:
		case GpuImageFormat::R8G8B8UNORM:
		case GpuImageFormat::R8G8B8SNORM:
		case GpuImageFormat::R8G8B8UINT:
		case GpuImageFormat::R8G8B8SINT:
		case GpuImageFormat::R8G8B8A8SRGB:
		case GpuImageFormat::R8G8B8A8UNORM:
		case GpuImageFormat::R8G8B8A8SNORM:
		case GpuImageFormat::R8G8B8A8UINT:
		case GpuImageFormat::R8G8B8A8SINT:
			return 1;
		case GpuImageFormat::R16SFLOAT:
		case GpuImageFormat::R16UNORM:
		case GpuImageFormat::R16SNORM:
		case GpuImageFormat::R16UINT:
		case GpuImageFormat::R16SINT:
		case GpuImageFormat::R16G16SFLOAT:
		case GpuImageFormat::R16G16UNORM:
		case GpuImageFormat::R16G16SNORM:
		case GpuImageFormat::R16G16UINT:
		case GpuImageFormat::R16G16SINT:
		case GpuImageFormat::R16G16B16SFLOAT:
		case GpuImageFormat::R16G16B16UNORM:
		case GpuImageFormat::R16G16B16SNORM:
		case GpuImageFormat::R16G16B16UINT:
		case GpuImageFormat::R16G16B16SINT:
		case GpuImageFormat::R16G16B16A16SFLOAT:
		case GpuImageFormat::R16G16B16A16UNORM:
		case GpuImageFormat::R16G16B16A16SNORM:
		case GpuImageFormat::R16G16B16A16UINT:
		case GpuImageFormat::R16G16B16A16SINT:
			return 2;
		case GpuImageFormat::R32SFLOAT:
		case GpuImageFormat::R32UINT:
		case GpuImageFormat::R32SINT:
		case GpuImageFormat::R32G32SFLOAT:
		case GpuImageFormat::R32G32UINT:
		case GpuImageFormat::R32G32SINT:
		case GpuImageFormat::R32G32B32SFLOAT:
		case GpuImageFormat::R32G32B32UINT:
		case GpuImageFormat::R32G32B32SINT:
		case GpuImageFormat::R32G32B32A32SFLOAT:
		case GpuImageFormat::R32G32B32A32UINT:
		case GpuImageFormat::R32G32B32A32SINT:
			return 4;
		case GpuImageFormat::R64SFLOAT:
		case GpuImageFormat::R64UINT:
		case GpuImageFormat::R64SINT:
		case GpuImageFormat::R64G64SFLOAT:
		case GpuImageFormat::R64G64UINT:
		case GpuImageFormat::R64G64SINT:
		case GpuImageFormat::R64G64B64SFLOAT:
		case GpuImageFormat::R64G64B64UINT:
		case GpuImageFormat::R64G64B64SINT:
		case GpuImageFormat::R64G64B64A64SFLOAT:
		case GpuImageFormat::R64G64B64A64UINT:
		case GpuImageFormat::R64G64B64A64SINT:
			return 8;
		default:
			throw Exception(
				THIS_FUNCTION_NAME,
				"Unsupported image format");
		}
	}
}
