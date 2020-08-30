#pragma once
#include <injector/graphics/pipeline.hpp>
#include <injector/graphics/vma_defines.hpp>

#include <vulkan/vulkan.hpp>

namespace INJECTOR_NAMESPACE
{
	class VkPipeline : public Pipeline
	{
	protected:
		vk::Device device;
		vk::PipelineCache pipelineCache;
		vk::CommandBuffer bindedCommandBuffer;
	public:
		VkPipeline(vk::Device device);
		virtual ~VkPipeline();

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

	using VkPipelineHandle = std::shared_ptr<VkPipeline>;
}
