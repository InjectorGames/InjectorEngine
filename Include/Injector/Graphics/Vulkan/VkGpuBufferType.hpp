#pragma once
#include "Injector/Graphics/GpuBufferType.hpp"
#include "Injector/Exception/Exception.hpp"

#include "vulkan/vulkan.hpp"

namespace Injector
{
	static vk::BufferUsageFlagBits toVkGpuBufferType(
		GpuBufferType type)
	{
		switch (type)
		{
		case GpuBufferType::TransferSource:
			return vk::BufferUsageFlagBits::eTransferSrc;
		case GpuBufferType::TransferDestination:
			return vk::BufferUsageFlagBits::eTransferDst;
		case GpuBufferType::UniformTexel:
			return vk::BufferUsageFlagBits::eUniformTexelBuffer;
		case GpuBufferType::StorageTexel:
			return vk::BufferUsageFlagBits::eStorageTexelBuffer;
		case GpuBufferType::Uniform:
			return vk::BufferUsageFlagBits::eUniformBuffer;
		case GpuBufferType::Storage:
			return vk::BufferUsageFlagBits::eStorageBuffer;
		case GpuBufferType::Index:
			return vk::BufferUsageFlagBits::eIndexBuffer;
		case GpuBufferType::Vertex:
			return vk::BufferUsageFlagBits::eVertexBuffer;
		case GpuBufferType::Indirect:
			return vk::BufferUsageFlagBits::eIndirectBuffer;
		case GpuBufferType::TransformFeedback:
			return vk::BufferUsageFlagBits::eTransformFeedbackBufferEXT;
		case GpuBufferType::TransformFeedbackCounter:
			return vk::BufferUsageFlagBits::eTransformFeedbackCounterBufferEXT;
		default:
			throw Exception(
				THIS_FUNCTION_NAME,
				"Unsupported buffer type");
		}
	}
}
