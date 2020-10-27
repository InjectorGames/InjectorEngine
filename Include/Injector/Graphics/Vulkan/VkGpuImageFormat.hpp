#pragma once
#include "Injector/Graphics/GpuImageFormat.hpp"
#include "Injector/Exception/Exception.hpp"

#include "vulkan/vulkan.hpp"

namespace Injector
{
	static vk::Format toVkGpuImageFormat(
		GpuImageFormat format)
	{
		switch (format)
		{
		case GpuImageFormat::R8:
			return vk::Format::eR8Srgb;
		case GpuImageFormat::R8U:
			return vk::Format::eR8Uint;
		case GpuImageFormat::R8I:
			return vk::Format::eR8Sint;
		case GpuImageFormat::RG8:
			return vk::Format::eR8G8Srgb;
		case GpuImageFormat::RG8U:
			return vk::Format::eR8G8Uint;
		case GpuImageFormat::RG8I:
			return vk::Format::eR8G8Sint;
		case GpuImageFormat::RGB8:
			return vk::Format::eR8G8B8Srgb;
		case GpuImageFormat::RGB8U:
			return vk::Format::eR8G8B8Uint;
		case GpuImageFormat::RGB8I:
			return vk::Format::eR8G8B8Sint;
		case GpuImageFormat::RGBA8:
			return vk::Format::eR8G8B8A8Srgb;
		case GpuImageFormat::RGBA8U:
			return vk::Format::eR8G8B8A8Uint;
		case GpuImageFormat::RGBA8I:
			return vk::Format::eR8G8B8A8Sint;
		case GpuImageFormat::R16F:
			return vk::Format::eR16Sfloat;
		case GpuImageFormat::R16U:
			return vk::Format::eR16Uint;
		case GpuImageFormat::R16I:
			return vk::Format::eR16Sint;
		case GpuImageFormat::RG16F:
			return vk::Format::eR16G16Sfloat;
		case GpuImageFormat::RG16U:
			return vk::Format::eR16G16Uint;
		case GpuImageFormat::RG16I:
			return vk::Format::eR16G16Sint;
		case GpuImageFormat::RGB16F:
			return vk::Format::eR16G16B16Sfloat;
		case GpuImageFormat::RGB16U:
			return vk::Format::eR16G16B16Uint;
		case GpuImageFormat::RGB16I:
			return vk::Format::eR16G16B16Sint;
		case GpuImageFormat::RGBA16F:
			return vk::Format::eR16G16B16A16Sfloat;
		case GpuImageFormat::RGBA16U:
			return vk::Format::eR16G16B16A16Uint;
		case GpuImageFormat::RGBA16I:
			return vk::Format::eR16G16B16A16Sint;
		case GpuImageFormat::R32F:
			return vk::Format::eR32Sfloat;
		case GpuImageFormat::R32U:
			return vk::Format::eR32Uint;
		case GpuImageFormat::R32I:
			return vk::Format::eR32Sint;
		case GpuImageFormat::RG32F:
			return vk::Format::eR32G32Sfloat;
		case GpuImageFormat::RG32U:
			return vk::Format::eR32G32Uint;
		case GpuImageFormat::RG32I:
			return vk::Format::eR32G32Sint;
		case GpuImageFormat::RGB32F:
			return vk::Format::eR32G32B32Sfloat;
		case GpuImageFormat::RGB32U:
			return vk::Format::eR32G32B32Uint;
		case GpuImageFormat::RGB32I:
			return vk::Format::eR32G32B32Sint;
		case GpuImageFormat::RGBA32F:
			return vk::Format::eR32G32B32A32Sfloat;
		case GpuImageFormat::RGBA32U:
			return vk::Format::eR32G32B32A32Uint;
		case GpuImageFormat::RGBA32I:
			return vk::Format::eR32G32B32A32Sint;
		case GpuImageFormat::R64F:
			return vk::Format::eR64Sfloat;
		case GpuImageFormat::R64U:
			return vk::Format::eR64Uint;
		case GpuImageFormat::R64I:
			return vk::Format::eR64Sint;
		case GpuImageFormat::RG64F:
			return vk::Format::eR64G64Sfloat;
		case GpuImageFormat::RG64U:
			return vk::Format::eR64G64Uint;
		case GpuImageFormat::RG64I:
			return vk::Format::eR64G64Sint;
		case GpuImageFormat::RGB64F:
			return vk::Format::eR64G64B64Sfloat;
		case GpuImageFormat::RGB64U:
			return vk::Format::eR64G64B64Uint;
		case GpuImageFormat::RGB64I:
			return vk::Format::eR64G64B64Sint;
		case GpuImageFormat::RGBA64F:
			return vk::Format::eR64G64B64A64Sfloat;
		case GpuImageFormat::RGBA64U:
			return vk::Format::eR64G64B64A64Uint;
		case GpuImageFormat::RGBA64I:
			return vk::Format::eR64G64B64A64Sint;
		case GpuImageFormat::D16:
			return vk::Format::eD16Unorm;
		case GpuImageFormat::D32:
			return vk::Format::eD32Sfloat;
		case GpuImageFormat::D16S8:
			return vk::Format::eD16UnormS8Uint;
		case GpuImageFormat::D24S8:
			return vk::Format::eD24UnormS8Uint;
		case GpuImageFormat::D32S8:
			return vk::Format::eD32SfloatS8Uint;
		default:
			throw Exception(
				"",
				std::string(__func__),
				std::to_string(__LINE__),
				"Unsupported image format");
		}
	}
}
