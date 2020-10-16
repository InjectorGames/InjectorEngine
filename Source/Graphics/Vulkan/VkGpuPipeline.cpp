#include "Injector/Graphics/Vulkan/VkGpuPipeline.hpp"
#include "Injector/Exception/NullException.hpp"

namespace Injector
{
	VkGpuPipeline::VkGpuPipeline(
		vk::Device _device) :
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

		auto pipelineCacheCreateInfo = vk::PipelineCacheCreateInfo();

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

	void VkGpuPipeline::bind(
		vk::CommandBuffer commandBuffer,
		size_t imageIndex)
	{
		bindedCommandBuffer = commandBuffer;
	}
}
