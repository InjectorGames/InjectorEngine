#pragma once
#include "Injector/Graphics/GpuImageWrap.hpp"
#include "Injector/Exception/Exception.hpp"

#include "vulkan/vulkan.hpp"

namespace Injector
{
	static vk::SamplerAddressMode toVkGpuImageWrap(
		GpuImageWrap wrap)
	{
		switch (wrap)
		{
		case GpuImageWrap::Repeat:
			return vk::SamplerAddressMode::eRepeat;
		case GpuImageWrap::MirroredRepeat:
			return vk::SamplerAddressMode::eMirroredRepeat;
		case GpuImageWrap::ClampToEdge:
			return vk::SamplerAddressMode::eClampToEdge;
		case GpuImageWrap::ClampToBorder:
			return vk::SamplerAddressMode::eClampToBorder;
		case GpuImageWrap::MirrorClampToEdge:
			return vk::SamplerAddressMode::eMirrorClampToEdge;
		default:
			throw Exception(
				THIS_FUNCTION_NAME,
				"Unsupported image wrap");
		}
	}
}
