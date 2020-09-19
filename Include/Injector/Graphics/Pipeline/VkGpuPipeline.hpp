#pragma once
#include "Injector/Graphics/Pipeline/GpuPipeline.hpp"
#include "Injector/Graphics/VmaDefines.hpp"

#include "vulkan/vulkan.hpp"

namespace Injector
{
	class VkGpuPipeline : public GpuPipeline
	{
	protected:
		vk::Device device;
		vk::PipelineCache pipelineCache;
		vk::CommandBuffer bindedCommandBuffer;
	public:
		VkGpuPipeline(vk::Device device);
		virtual ~VkGpuPipeline();

		vk::Device getDevice();
		vk::PipelineCache getPipelineCache();

		virtual void recreate(
			VmaAllocator allocator,
			vk::RenderPass renderPass,
			uint32_t imageCount,
			const vk::Extent2D& surfaceExtent);
		virtual void flush(
			size_t imageIndex);
		virtual void bind(
			vk::CommandBuffer commandBuffer,
			size_t imageIndex);
	};
}
