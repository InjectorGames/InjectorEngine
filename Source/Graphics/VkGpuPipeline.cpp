#include "Injector/Graphics/VkGpuPipeline.hpp"
#include "Injector/Exception/NotImplementedException.hpp"

namespace Injector
{
	VkGpuPipeline::VkGpuPipeline(
		vk::Device _device) :
		device(_device),
		bindedCommandBuffer()
	{
		auto pipelineCacheCreateInfo = vk::PipelineCacheCreateInfo();
		auto result = _device.createPipelineCache(
			&pipelineCacheCreateInfo, nullptr, &pipelineCache);

		if (result != vk::Result::eSuccess)
			throw Exception("VkGpuPipeline", "VkGpuPipeline", "Failed to create pipeline cache");
	}
	VkGpuPipeline::~VkGpuPipeline()
	{
		device.destroyPipelineCache(pipelineCache);
	}

	vk::Device VkGpuPipeline::getDevice()
	{
		return device;
	}
	vk::PipelineCache VkGpuPipeline::getPipelineCache()
	{
		return pipelineCache;
	}

	void VkGpuPipeline::recreate(
		VmaAllocator allocator,
		vk::RenderPass renderPass,
		uint32_t imageCount,
		const vk::Extent2D& surfaceExtent)
	{
		throw NotImplementedException("VkGpuPipeline", "recreate");
	}
	void VkGpuPipeline::flush(
		size_t imageIndex)
	{
		throw NotImplementedException("VkGpuPipeline", "flush");
	}
	void VkGpuPipeline::bind(
		vk::CommandBuffer commandBuffer,
		size_t imageIndex)
	{
		bindedCommandBuffer = commandBuffer;
	}
}
