#pragma once
#include <injector/graphics/vk_pipeline.hpp>
#include <injector/graphics/vk_buffer.hpp>
#include <injector/graphics/diffuse_pipeline.hpp>

#include <vector>

namespace INJECTOR_NAMESPACE
{
	class VkDiffusePipeline : public VkPipeline, public DiffusePipeline
	{
	public:
		struct UniformBufferObject
		{
			Vector4 objectColor;
			Vector4 ambientColor;
			Vector4 lightColor;
			Vector3 lightDirection;

			UniformBufferObject(
				const Vector4& _objectColor,
				const Vector4& _ambientColor,
				const Vector4& _lightColor,
				const Vector3& _lightDirection) :
				objectColor(_objectColor),
				ambientColor(_ambientColor),
				lightColor(_lightColor),
				lightDirection(_lightDirection)
			{}
		};
	protected:
		vk::DescriptorSetLayout descriptorSetLayout;
		vk::PipelineLayout pipelineLayout;
		vk::Pipeline pipeline;
		vk::DescriptorPool descriptorPool;
		std::vector<VkBufferHandle> uniformBuffers;
		std::vector<vk::DescriptorSet> descriptorSets;

		UniformBufferObject ubo;

		static vk::Pipeline createPipeline(
			vk::Device device,
			vk::PipelineCache pipelineCache,
			vk::PipelineLayout pipelineLayout,
			vk::RenderPass renderPass,
			const vk::Extent2D& surfaceExtent);
		static vk::DescriptorPool createDescriptorPool(
			vk::Device device,
			uint32_t imageCount);
		static std::vector<VkBufferHandle> createUniformBuffers(
			VmaAllocator allocator,
			uint32_t imageCount);
		static std::vector<vk::DescriptorSet> createDescriptorSets(
			vk::Device device,
			vk::DescriptorPool descriptorPool,
			vk::DescriptorSetLayout descriptorSetLayout,
			size_t imageCount,
			const std::vector<VkBufferHandle>& uniformBuffers);
	public:
		VkDiffusePipeline(
			vk::Device device,
			VmaAllocator allocator,
			vk::RenderPass renderPass,
			uint32_t imageCount,
			const vk::Extent2D& surfaceExtent,
			const Vector4& objectColor = Vector4::one,
			const Vector4& ambientColor = Vector4::one / 4.0f,
			const Vector4& lightColor = Vector4::one,
			const Vector3& lightDirection = Vector3(1.0f, 2.0f, 4.0f));
		virtual ~VkDiffusePipeline();

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

		const Vector4& getObjectColor() const override;
		void setObjectColor(const Vector4& objectColor) override;

		const Vector4& getAmbientColor() const override;
		void setAmbientColor(const Vector4& ambientColor) override;

		const Vector4& getLightColor() const override;
		void setLightColor(const Vector4& lightColor) override;

		const Vector3& getLightDirection() const override;
		void setLightDirection(const Vector3& lightDirection) override;
	};

	using VkDiffusePipelineHandle = std::shared_ptr<VkDiffusePipeline>;
}
