#pragma once
#include "Injector/Graphics/GpuPipeline.hpp"
#include "Injector/Graphics/Vulkan/VmaDefines.hpp"

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
		explicit VkGpuPipeline(vk::Device device);
		~VkGpuPipeline() override;

		vk::Device getDevice();
		vk::PipelineCache getPipelineCache();

		virtual void bind(
			vk::CommandBuffer commandBuffer,
			size_t imageIndex);

		virtual void recreate(
			VmaAllocator allocator,
			vk::RenderPass renderPass,
			uint32_t imageCount,
			const vk::Extent2D& surfaceExtent) = 0;
		virtual void flush(
			size_t imageIndex) = 0;
	};
}
