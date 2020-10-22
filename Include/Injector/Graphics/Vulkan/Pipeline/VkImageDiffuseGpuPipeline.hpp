#pragma once
#include "Injector/Graphics/Vulkan/VkGpuPipeline.hpp"
#include "Injector/Graphics/Pipeline/ImageDiffuseGpuPipeline.hpp"
#include "Injector/Graphics/Vulkan/VkGpuImage.hpp"
#include "Injector/Graphics/Vulkan/VkGpuShader.hpp"
#include "Injector/Graphics/Vulkan/VkGpuBuffer.hpp"

#include <vector>
#include <memory>

namespace Injector
{
	class VkImageDiffuseGpuPipeline :
		public VkGpuPipeline,
		public ImageDiffuseGpuPipeline
	{
	 public:
		struct UniformBufferObject
		{
			Vector4 objectColor;
			Vector4 ambientColor;
			Vector4 lightColor;
			alignas(16) Vector3 lightDirection;
			Vector2 imageScale;
			Vector2 imageOffset;

			explicit UniformBufferObject(
				const Vector4& _objectColor = Vector4::one,
				const Vector4& _ambientColor = Vector4::one / 2.0f,
				const Vector4& _lightColor = Vector4::one,
				const Vector3& _lightDirection =
				Vector3(1.0f, 2.0f, 3.0f).getNormalized(),
				const Vector2& _imageScale = Vector2::one,
				const Vector2& _imageOffset = Vector2::zero) :
				objectColor(_objectColor),
				ambientColor(_ambientColor),
				lightColor(_lightColor),
				lightDirection(_lightDirection),
				imageScale(_imageScale),
				imageOffset(_imageOffset)
			{
			}
		};
	 protected:
		vk::DescriptorSetLayout descriptorSetLayout;
		vk::PipelineLayout pipelineLayout;
		vk::Pipeline pipeline;
		vk::DescriptorPool descriptorPool;
		vk::ImageView imageView;
		vk::Sampler imageSampler;
		std::shared_ptr<VkGpuShader> vertexShader;
		std::shared_ptr<VkGpuShader> fragmentShader;
		std::shared_ptr<VkGpuImage> image;
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
		static vk::ImageView createImageView(
			vk::Device,
			vk::Image);
		static vk::Sampler createImageSampler();
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
		VkImageDiffuseGpuPipeline(
			vk::Device device,
			VmaAllocator allocator,
			vk::RenderPass renderPass,
			uint32_t imageCount,
			const vk::Extent2D& surfaceExtent,
			PrimitiveTopology primitiveTopology,
			const std::shared_ptr<VkGpuShader>& vertexShader,
			const std::shared_ptr<VkGpuShader>& fragmentShader,
			const std::shared_ptr<VkGpuImage>& image,
			const UniformBufferObject& ubo = UniformBufferObject());
		~VkImageDiffuseGpuPipeline() override;

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

		const Vector2& getImageScale() const override;
		void setImageScale(const Vector2& scale) override;

		const Vector2& getImageOffset() const override;
		void setImageOffset(const Vector2& offset) override;
	};
}
