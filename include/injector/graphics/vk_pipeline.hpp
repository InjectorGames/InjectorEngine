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
	public:
		VkPipeline(vk::Device device);
		virtual ~VkPipeline();

		virtual void recreate(
			uint32_t imageCount,
			vk::RenderPass renderPass,
			vk::Extent2D surfaceExtent);
		virtual void bind(
			uint32_t imageIndex,
			vk::CommandBuffer commandBuffer);
	};

	using VkPipelineHandle = std::shared_ptr<VkPipeline>;
}
