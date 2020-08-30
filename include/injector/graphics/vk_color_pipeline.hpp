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
			const Vector4& color = Vector4::one);
		virtual ~VkColorPipeline();

		const Vector4& getColor() const override;
		void setColor(const Vector4& color) override;

		void recreate(
			VmaAllocator allocator,
			vk::RenderPass renderPass,
			uint32_t imageCount,
			const vk::Extent2D& surfaceExtent) override;
		void flush(
			size_t imageIndex) override;
		void bind(
			vk::CommandBuffer commandBuffer,
			size_t imageIndex) override;
		void setUniforms(
			const Matrix4& model,
			const Matrix4& view,
			const Matrix4& proj,
			const Matrix4& viewProj,
			const Matrix4& mvp) override;
	};

	using VkColorPipelineHandle = std::shared_ptr<VkColorPipeline>;
}
