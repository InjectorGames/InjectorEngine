#pragma once
#include "Injector/Graphics/GpuShaderStage.hpp"
#include "Injector/Exception/Exception.hpp"

#include "vulkan/vulkan.hpp"

namespace Injector
{
	static vk::ShaderStageFlagBits toVkGpuShaderStage(
		GpuShaderStage stage)
	{
		switch (stage)
		{
		case GpuShaderStage::Vertex:
			return vk::ShaderStageFlagBits::eVertex;
		case GpuShaderStage::TesselationControl:
			return vk::ShaderStageFlagBits::eTessellationControl;
		case GpuShaderStage::TesselationEvaluation:
			return vk::ShaderStageFlagBits::eTessellationEvaluation;
		case GpuShaderStage::Geometry:
			return vk::ShaderStageFlagBits::eGeometry;
		case GpuShaderStage::Fragment:
			return vk::ShaderStageFlagBits::eFragment;
		case GpuShaderStage::Compute:
			return vk::ShaderStageFlagBits::eCompute;
		case GpuShaderStage::Raygen:
			return vk::ShaderStageFlagBits::eRaygenKHR;
		case GpuShaderStage::AnyHit:
			return vk::ShaderStageFlagBits::eAnyHitKHR;
		case GpuShaderStage::ClosestHit:
			return vk::ShaderStageFlagBits::eClosestHitKHR;
		case GpuShaderStage::Miss:
			return vk::ShaderStageFlagBits::eMissKHR;
		case GpuShaderStage::Intersection:
			return vk::ShaderStageFlagBits::eIntersectionKHR;
		case GpuShaderStage::Callable:
			return vk::ShaderStageFlagBits::eCallableKHR;
		case GpuShaderStage::Task:
			return vk::ShaderStageFlagBits::eTaskNV;
		case GpuShaderStage::Mesh:
			return vk::ShaderStageFlagBits::eMeshNV;
		default:
			throw Exception(
				"",
				"toVkGpuShaderStage",
				"Unsupported shader stage");
		}
	}
}
