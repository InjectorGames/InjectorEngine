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

		Matrix4 mvp;
		Vector4 color;

		static vk::Pipeline createPipeline(
			vk::Device device,
			vk::PipelineCache pipelineCache,
			vk::PipelineLayout pipelineLayout,
			vk::RenderPass renderPass,
			const vk::Extent2D& surfaceExtent);
	public:
		VkColorPipeline(
			vk::Device device,
			vk::RenderPass renderPass,
			const vk::Extent2D& surfaceExtent,
			const Matrix4& mvp = Matrix4::identity,
			const Vector4& color = Vector4::one);
		virtual ~VkColorPipeline();

		const Matrix4& getMVP() const override;
		void setMVP(const Matrix4& mvp) override;

		const Vector4& getColor() const override;
		void setColor(const Vector4& color) override;

		void recreate(
			uint32_t imageCount,
			vk::RenderPass renderPass,
			vk::Extent2D surfaceExtent) override;
		void bind(
			uint32_t imageIndex,
			vk::CommandBuffer commandBuffer) override;
	};

	using VkColorPipelineHandle = std::shared_ptr<VkColorPipeline>;
}
