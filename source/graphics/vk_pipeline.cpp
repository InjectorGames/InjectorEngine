#include <injector/graphics/vk_pipeline.hpp>

namespace INJECTOR_NAMESPACE
{
	VkPipeline::VkPipeline(vk::Device _device) :
		device(_device)
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

	void VkPipeline::bind(vk::CommandBuffer commandBuffer)
	{
		throw std::runtime_error("Not implemented Vulkan pipeline function");
	}
	void VkPipeline::recreate(vk::RenderPass renderPass, vk::Extent2D surfaceExtent)
	{
		throw std::runtime_error("Not implemented Vulkan pipeline function");
	}
}
