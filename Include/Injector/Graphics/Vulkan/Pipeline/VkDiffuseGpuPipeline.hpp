#pragma once
#include "Injector/Graphics/Vulkan/VkGpuPipeline.hpp"
#include "Injector/Graphics/Pipeline/DiffuseGpuPipeline.hpp"
#include "Injector/Graphics/Vulkan/VkGpuShader.hpp"
#include "Injector/Graphics/Vulkan/VkGpuBuffer.hpp"

#include <vector>
#include <memory>

namespace Injector
{
	class VkDiffuseGpuPipeline :
		public VkGpuPipeline,
		public DiffuseGpuPipeline
	{
	 public:
		struct UniformBufferObject
		{
			FloatVector4 objectColor;
			FloatVector4 ambientColor;
			FloatVector4 lightColor;
			FloatVector3 lightDirection;
			float alignment;

			explicit UniformBufferObject(
				const FloatVector4& _objectColor,
				const FloatVector4& _ambientColor,
				const FloatVector4& _lightColor,
				const FloatVector3& _lightDirection) :
				objectColor(_objectColor),
				ambientColor(_ambientColor),
				lightColor(_lightColor),
				lightDirection(_lightDirection),
				alignment()
			{
			}
		};
	 protected:
		vk::DescriptorSetLayout descriptorSetLayout;
		vk::PipelineLayout pipelineLayout;
		vk::Pipeline pipeline;
		vk::DescriptorPool descriptorPool;

		std::shared_ptr<VkGpuShader> vertexShader;
		std::shared_ptr<VkGpuShader> fragmentShader;

		std::vector<std::shared_ptr<VkGpuBuffer>> uniformBuffers;
		std::vector<vk::DescriptorSet> descriptorSets;

		UniformBufferObject ubo;

		static vk::DescriptorSetLayout createDescriptorSetLayout(
			vk::Device device);
		static vk::PipelineLayout createPipelineLayout(
			vk::Device device,
			vk::DescriptorSetLayout descriptorSetLayout);
		static vk::Pipeline createPipeline(
			vk::Device device,
			vk::PipelineCache pipelineCache,
			vk::PipelineLayout pipelineLayout,
			vk::RenderPass renderPass,
			const vk::Extent2D& surfaceExtent,
			vk::PrimitiveTopology primitiveTopology,
			const std::shared_ptr<VkGpuShader>& vertexShader,
			const std::shared_ptr<VkGpuShader>& fragmentShader);
		static vk::DescriptorPool createDescriptorPool(
			vk::Device device,
			uint32_t imageCount);
		static std::vector<std::shared_ptr<VkGpuBuffer>> createUniformBuffers(
			VmaAllocator allocator,
			uint32_t imageCount);
		static std::vector<vk::DescriptorSet> createDescriptorSets(
			vk::Device device,
			vk::DescriptorPool descriptorPool,
			vk::DescriptorSetLayout descriptorSetLayout,
			size_t imageCount,
			const std::vector<std::shared_ptr<VkGpuBuffer>>& uniformBuffers);
	 public:
		VkDiffuseGpuPipeline(
			vk::Device device,
			VmaAllocator allocator,
			vk::RenderPass renderPass,
			uint32_t imageCount,
			const vk::Extent2D& surfaceExtent,
			GpuDrawMode drawMode,
			const std::shared_ptr<VkGpuShader>& vertexShader,
			const std::shared_ptr<VkGpuShader>& fragmentShader,
			const UniformBufferObject& ubo);
		~VkDiffuseGpuPipeline() override;

		const FloatVector4& getObjectColor() const override;
		void setObjectColor(const FloatVector4& color) override;

		const FloatVector4& getAmbientColor() const override;
		void setAmbientColor(const FloatVector4& color) override;

		const FloatVector4& getLightColor() const override;
		void setLightColor(const FloatVector4& color) override;

		const FloatVector3& getLightDirection() const override;
		void setLightDirection(const FloatVector3& direction) override;

		void recreate(
			VmaAllocator allocator,
			vk::RenderPass renderPass,
			uint32_t imageCount,
			const vk::Extent2D& extent) override;
		void flush(
			size_t imageIndex) override;
		void bind(
			vk::CommandBuffer commandBuffer,
			size_t imageIndex) override;
		void setUniforms(
			const FloatMatrix4& model,
			const FloatMatrix4& view,
			const FloatMatrix4& proj,
			const FloatMatrix4& viewProj,
			const FloatMatrix4& mvp) override;
	};
}
