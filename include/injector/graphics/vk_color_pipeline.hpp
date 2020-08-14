#pragma once
#include <injector/graphics/vk_pipeline.hpp>
#include <injector/graphics/color_pipeline.hpp>

namespace INJECTOR_NAMESPACE
{
	class VkColorPipeline : public VkPipeline, public ColorPipeline
	{
	protected:
		vk::PipelineLayout pipelineLayout;
		vk::Pipeline pipeline;
	public:
		VkColorPipeline(
			vk::Device device,
			vk::RenderPass renderPass,
			vk::Extent2D surfaceExtent);
		virtual ~VkColorPipeline();

		void bind(vk::CommandBuffer commandBuffer) override;
	};

	using VkPipelineHandle = std::shared_ptr<VkPipeline>;
}
