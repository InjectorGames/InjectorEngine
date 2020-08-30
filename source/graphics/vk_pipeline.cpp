#include <injector/graphics/vk_pipeline.hpp>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
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
			throw std::runtime_error("Failed to create Vulkan pipeline cache");
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
		throw std::runtime_error("Not implemented Vulkan pipeline function");
	}
	void VkPipeline::flush(
		size_t imageIndex)
	{
		throw std::runtime_error("Not implemented Vulkan pipeline function");
	}
	void VkPipeline::bind(
		vk::CommandBuffer commandBuffer,
		size_t imageIndex)
	{
		bindedCommandBuffer = commandBuffer;
	}
}
