#include "Injector/Graphics/Vulkan/VkGpuPipeline.hpp"
#include "Injector/Exception/NullException.hpp"

namespace Injector
{
	VkGpuPipeline::VkGpuPipeline(
		vk::Device _device,
		PrimitiveTopology primitiveTopology) :
		GpuPipeline(primitiveTopology),
		device(_device),
		bindedCommandBuffer()
	{
		if(!_device)
		{
			throw NullException(
				"VkGpuPipeline",
				"VkGpuPipeline",
				"device");
		}

		auto pipelineCacheCreateInfo =
			vk::PipelineCacheCreateInfo();

		auto result = _device.createPipelineCache(
			&pipelineCacheCreateInfo,
			nullptr,
			&pipelineCache);

		if (result != vk::Result::eSuccess)
		{
			throw Exception(
				"VkGpuPipeline",
				"VkGpuPipeline",
				"Failed to create pipeline cache");
		}
	}
	VkGpuPipeline::~VkGpuPipeline()
	{
		device.destroyPipelineCache(
			pipelineCache);
	}

	vk::Device VkGpuPipeline::getDevice()
	{
		return device;
	}
	vk::PipelineCache VkGpuPipeline::getPipelineCache()
	{
		return pipelineCache;
	}

	void VkGpuPipeline::bind(
		vk::CommandBuffer commandBuffer,
		size_t imageIndex)
	{
		bindedCommandBuffer = commandBuffer;
	}

	vk::PrimitiveTopology VkGpuPipeline::toVkPrimitiveTopology(
		PrimitiveTopology primitiveTopology)
	{
		switch (primitiveTopology)
		{
		case PrimitiveTopology::PointList:
			return vk::PrimitiveTopology::ePointList;
		case PrimitiveTopology::LineList:
			return vk::PrimitiveTopology::eLineList;
		case PrimitiveTopology::LineStrip:
			return vk::PrimitiveTopology::eLineStrip;
		case PrimitiveTopology::TriangleList:
			return vk::PrimitiveTopology::eTriangleList;
		case PrimitiveTopology::TriangleStrip:
			return vk::PrimitiveTopology::eTriangleStrip;
		case PrimitiveTopology::LineListWithAdjacency:
			return vk::PrimitiveTopology::eLineListWithAdjacency;
		case PrimitiveTopology::LineStripWithAdjacency:
			return vk::PrimitiveTopology::eLineStripWithAdjacency;
		case PrimitiveTopology::TriangleListWithAdjacency:
			return vk::PrimitiveTopology::eTriangleListWithAdjacency;
		case PrimitiveTopology::TriangleStripWithAdjacency:
			return vk::PrimitiveTopology::eTriangleStripWithAdjacency;
		case PrimitiveTopology::PatchList:
			return vk::PrimitiveTopology::ePatchList;
		default:
			throw Exception(
				"VkGpuPipeline",
				"toVkPrimitiveTopology",
				"Unsupported primitive topology");
		}
	}
}
