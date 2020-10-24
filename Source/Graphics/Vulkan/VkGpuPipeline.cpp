#include "Injector/Graphics/Vulkan/VkGpuPipeline.hpp"
#include "Injector/Exception/NullException.hpp"

namespace Injector
{
	VkGpuPipeline::VkGpuPipeline(
		vk::Device _device,
		GpuDrawMode drawMode) :
		GpuPipeline(drawMode),
		device(_device),
		bindedCommandBuffer()
	{
		if(!_device)
		{
			throw NullException(
				std::string(typeid(VkGpuPipeline).name()),
				std::string(__func__),
				std::to_string(__LINE__),
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
				std::string(typeid(VkGpuPipeline).name()),
				std::string(__func__),
				std::to_string(__LINE__),
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
		if(!commandBuffer)
		{
			throw NullException(
				std::string(typeid(VkGpuPipeline).name()),
				std::string(__func__),
				std::to_string(__LINE__),
				"commandBuffer");
		}

		bindedCommandBuffer = commandBuffer;
	}
}
