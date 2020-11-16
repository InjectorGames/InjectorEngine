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
			FloatVector4 objectColor;
			FloatVector4 ambientColor;
			FloatVector4 lightColor;
			FloatVector3 lightDirection;
			float alignment;
			FloatVector2 imageScale;
			FloatVector2 imageOffset;

			explicit UniformBufferObject(
				const FloatVector4& _objectColor,
				const FloatVector4& _ambientColor,
				const FloatVector4& _lightColor,
				const FloatVector3& _lightDirection,
				const FloatVector2& _imageScale,
				const FloatVector2& _imageOffset) :
				objectColor(_objectColor),
				ambientColor(_ambientColor),
				lightColor(_lightColor),
				lightDirection(_lightDirection),
				alignment(),
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

		GpuImageFilter imageMinFilter;
		GpuImageFilter imageMagFilter;
		GpuImageFilter mipmapFilter;
		GpuImageWrap imageWrapU;
		GpuImageWrap imageWrapV;
		GpuImageWrap imageWrapW;

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
		static vk::Sampler createImageSampler(
			vk::Device device,
			vk::Filter magFilter,
			vk::Filter minFilter,
			vk::SamplerMipmapMode mipmapMode,
			vk::SamplerAddressMode addressModeU,
			vk::SamplerAddressMode addressModeV,
			vk::SamplerAddressMode addressModeW);
		static std::vector<std::shared_ptr<VkGpuBuffer>> createUniformBuffers(
			VmaAllocator allocator,
			uint32_t imageCount);
		static std::vector<vk::DescriptorSet> createDescriptorSets(
			vk::Device device,
			vk::DescriptorPool descriptorPool,
			vk::DescriptorSetLayout descriptorSetLayout,
			vk::ImageView imageView,
			vk::Sampler sampler,
			size_t imageCount,
			const std::vector<std::shared_ptr<VkGpuBuffer>>& uniformBuffers);
	 public:
		VkImageDiffuseGpuPipeline(
			vk::Device device,
			VmaAllocator allocator,
			vk::RenderPass renderPass,
			uint32_t imageCount,
			const vk::Extent2D& surfaceExtent,
			GpuDrawMode drawMode,
			GpuImageFilter imageMinFilter,
			GpuImageFilter imageMagFilter,
			GpuImageFilter mipmapFilter,
			GpuImageWrap imageWrapU,
			GpuImageWrap imageWrapV,
			GpuImageWrap imageWrapW,
			const std::shared_ptr<VkGpuShader>& vertexShader,
			const std::shared_ptr<VkGpuShader>& fragmentShader,
			const std::shared_ptr<VkGpuImage>& image,
			const UniformBufferObject& ubo);
		~VkImageDiffuseGpuPipeline() override;

		GpuImageFilter getImageMinFilter() const override;
		GpuImageFilter getImageMagFilter() const override;
		GpuImageFilter getMipmapFilter() const override;

		GpuImageWrap getImageWrapU() const override;
		GpuImageWrap getImageWrapV() const override;
		GpuImageWrap getImageWrapW() const override;

		std::shared_ptr<GpuImage> getImage() const override;

		const FloatVector4& getObjectColor() const override;
		void setObjectColor(const FloatVector4& color) override;

		const FloatVector4& getAmbientColor() const override;
		void setAmbientColor(const FloatVector4& color) override;

		const FloatVector4& getLightColor() const override;
		void setLightColor(const FloatVector4& color) override;

		const FloatVector3& getLightDirection() const override;
		void setLightDirection(const FloatVector3& direction) override;

		const FloatVector2& getImageScale() const override;
		void setImageScale(const FloatVector2& scale) override;

		const FloatVector2& getImageOffset() const override;
		void setImageOffset(const FloatVector2& offset) override;

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
