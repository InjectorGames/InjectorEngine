#pragma once
#include <injector/graphics/vk_pipeline.hpp>
#include <injector/graphics/diffuse_pipeline.hpp>

namespace INJECTOR_NAMESPACE
{
	class VkDiffusePipeline : public VkPipeline, public DiffusePipeline
	{
	protected:
		vk::PipelineLayout pipelineLayout;
		vk::Pipeline pipeline;

		Matrix4 model;
		Matrix4 mvp;
		Vector4 objectColor;
		Vector4 ambientColor;
		Vector4 lightColor;
		Vector3 lightDirection;

		static vk::Pipeline createPipeline(
			vk::Device device,
			vk::PipelineCache pipelineCache,
			vk::PipelineLayout pipelineLayout,
			vk::RenderPass renderPass,
			const vk::Extent2D& surfaceExtent);
	public:
		VkDiffusePipeline(
			vk::Device device,
			vk::RenderPass renderPass,
			const vk::Extent2D& surfaceExtent);
		virtual ~VkDiffusePipeline();

		void recreate(
			uint32_t imageCount,
			vk::RenderPass renderPass,
			vk::Extent2D surfaceExtent) override;
		void bind(
			uint32_t imageIndex,
			vk::CommandBuffer commandBuffer) override;

		const Matrix4& getModel() const;
		void setModel(const Matrix4& model);

		const Matrix4& getMVP() const;
		void setMVP(const Matrix4& mvp);

		const Vector4& getObjectColor() const;
		void setObjectColor(const Vector4& objectColor);

		const Vector4& getAmbientColor() const;
		void setAmbientColor(const Vector4& ambientColor);

		const Vector4& getLightColor() const;
		void setLightColor(const Vector4& lightColor);

		const Vector3& getLightDirection() const;
		void setLightDirection(const Vector3& lightDirection);
	};

	using VkDiffusePipelineHandle = std::shared_ptr<VkDiffusePipeline>;
}
