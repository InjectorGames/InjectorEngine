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
			Vector4 objectColor;
			Vector4 ambientColor;
			Vector4 lightColor;
			alignas(16) Vector3 lightDirection;

			UniformBufferObject(
				const Vector4& _objectColor,
				const Vector4& _ambientColor,
				const Vector4& _lightColor,
				const Vector3& _lightDirection) :
				objectColor(_objectColor),
				ambientColor(_ambientColor),
				lightColor(_lightColor),
				lightDirection(_lightDirection)
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

		static vk::Pipeline createPipeline(
			vk::Device device,
			vk::PipelineCache pipelineCache,
			vk::PipelineLayout pipelineLayout,
			vk::RenderPass renderPass,
			const vk::Extent2D& surfaceExtent,
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
			const std::shared_ptr<VkGpuShader>& vertexShader,
			const std::shared_ptr<VkGpuShader>& fragmentShader,
			const Vector4& objectColor = Vector4::one,
			const Vector4& ambientColor = Vector4::one / 4.0f,
			const Vector4& lightColor = Vector4::one,
			const Vector3& lightDirection = Vector3(1.0f, 2.0f, 3.0f));
		~VkDiffuseGpuPipeline() override;

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
			const Matrix4& model,
			const Matrix4& view,
			const Matrix4& proj,
			const Matrix4& viewProj,
			const Matrix4& mvp) override;

		const Vector4& getObjectColor() const override;
		void setObjectColor(const Vector4& color) override;

		const Vector4& getAmbientColor() const override;
		void setAmbientColor(const Vector4& color) override;

		const Vector4& getLightColor() const override;
		void setLightColor(const Vector4& color) override;

		const Vector3& getLightDirection() const override;
		void setLightDirection(const Vector3& direction) override;
	};
}
