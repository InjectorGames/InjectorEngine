#include "Injector/Graphics/VkPipeline.hpp"
#include "Injector/Exception/NotImplementedException.hpp"

namespace Injector
{
	VkPipeline::VkPipeline(
		vk::Device _device) :
		device(_device),
		bindedCommandBuffer()
	{
		auto pipelineCacheCreateInfo = vk::PipelineCacheCreateInfo();
		auto result = _device.createPipelineCache(
			&pipelineCacheCreateInfo, nullptr, &pipelineCache);

		if (result != vk::Result::eSuccess)
			throw Exception("VkPipeline", "VkPipeline", "Failed to create pipeline cache");
	}
	VkPipeline::~VkPipeline()
	{
		device.destroyPipelineCache(pipelineCache);
	}

	vk::Device VkPipeline::getDevice()
	{
		return device;
	}
	vk::PipelineCache VkPipeline::getPipelineCache()
	{
		return pipelineCache;
	}

	void VkPipeline::recreate(
		VmaAllocator allocator,
		vk::RenderPass renderPass,
		uint32_t imageCount,
		const vk::Extent2D& surfaceExtent)
	{
		throw NotImplementedException("VkPipeline", "recreate");
	}
	void VkPipeline::flush(
		size_t imageIndex)
	{
		throw NotImplementedException("VkPipeline", "flush");
	}
	void VkPipeline::bind(
		vk::CommandBuffer commandBuffer,
		size_t imageIndex)
	{
		bindedCommandBuffer = commandBuffer;
	}
}
