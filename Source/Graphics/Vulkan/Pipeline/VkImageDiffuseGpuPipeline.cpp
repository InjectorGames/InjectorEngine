#include "Injector/Graphics/Vulkan/Pipeline/VkImageDiffuseGpuPipeline.hpp"
#include "Injector/Exception/NullException.hpp"
#include "Injector/Graphics/Vulkan/VkGpuDrawMode.hpp"
#include "Injector/Graphics/Vulkan/VkGpuImageWrap.hpp"
#include "Injector/Graphics/Vulkan/VkGpuImageFilter.hpp"

namespace Injector
{
	vk::DescriptorSetLayout VkImageDiffuseGpuPipeline::createDescriptorSetLayout(
		vk::Device device)
	{
		vk::DescriptorSetLayout descriptorSetLayout;

		vk::DescriptorSetLayoutBinding descriptorSetLayoutBindings[2] =
		{
			vk::DescriptorSetLayoutBinding(
				0,
				vk::DescriptorType::eUniformBuffer,
				1,
				vk::ShaderStageFlagBits::eFragment,
				nullptr),
			vk::DescriptorSetLayoutBinding(
				1,
				vk::DescriptorType::eCombinedImageSampler,
				1,
				vk::ShaderStageFlagBits::eFragment,
				nullptr),
		};

		auto descriptorSetLayoutCreateInfo = vk::DescriptorSetLayoutCreateInfo(
			vk::DescriptorSetLayoutCreateFlags(),
			2,
			descriptorSetLayoutBindings);

		auto result = device.createDescriptorSetLayout(
			&descriptorSetLayoutCreateInfo,
			nullptr,
			&descriptorSetLayout);

		if(result != vk::Result::eSuccess)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to create descriptor set layout");
		}

		return descriptorSetLayout;
	}
	vk::PipelineLayout VkImageDiffuseGpuPipeline::createPipelineLayout(
		vk::Device device,
		vk::DescriptorSetLayout descriptorSetLayout)
	{
		vk::PipelineLayout pipelineLayout;

		auto pushConstantRange = vk::PushConstantRange(
			vk::ShaderStageFlagBits::eVertex,
			0,
			sizeof(FloatMatrix4) * 2);

		auto pipelineLayoutCreateInfo = vk::PipelineLayoutCreateInfo(
			vk::PipelineLayoutCreateFlags(),
			1,
			&descriptorSetLayout,
			1,
			&pushConstantRange);

		auto result = device.createPipelineLayout(
			&pipelineLayoutCreateInfo,
			nullptr,
			&pipelineLayout);

		if (result != vk::Result::eSuccess)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to create pipeline layout");
		}

		return pipelineLayout;
	}
	vk::Pipeline VkImageDiffuseGpuPipeline::createPipeline(
		vk::Device device,
		vk::PipelineCache pipelineCache,
		vk::PipelineLayout pipelineLayout,
		vk::RenderPass renderPass,
		const vk::Extent2D& surfaceExtent,
		vk::PrimitiveTopology primitiveTopology,
		const std::shared_ptr<VkGpuShader>& vertexShader,
		const std::shared_ptr<VkGpuShader>& fragmentShader)
	{
		vk::PipelineShaderStageCreateInfo pipelineShaderStageCreateInfos[2] =
		{
			vk::PipelineShaderStageCreateInfo(
				vk::PipelineShaderStageCreateFlags(),
				vk::ShaderStageFlagBits::eVertex,
				vertexShader->getShaderModule(),
				"main",
				nullptr),
			vk::PipelineShaderStageCreateInfo(
				vk::PipelineShaderStageCreateFlags(),
				vk::ShaderStageFlagBits::eFragment,
				fragmentShader->getShaderModule(),
				"main",
				nullptr),
		};

		auto vertexInputBindingDescription = vk::VertexInputBindingDescription(
			0,
			sizeof(FloatVector3) * 2 + sizeof(FloatVector2),
			vk::VertexInputRate::eVertex);

		vk::VertexInputAttributeDescription vertexInputAttributeDescriptions[3] =
		{
			vk::VertexInputAttributeDescription(
				0,
				0,
				vk::Format::eR32G32B32Sfloat,
				0),
			vk::VertexInputAttributeDescription(
				1,
				0,
				vk::Format::eR32G32B32Sfloat,
				sizeof(FloatVector3)),
			vk::VertexInputAttributeDescription(
				2,
				0,
				vk::Format::eR32G32Sfloat,
				sizeof(FloatVector3) * 2),
		};

		auto pipelineVertexInputStateCreateInfo = vk::PipelineVertexInputStateCreateInfo(
			vk::PipelineVertexInputStateCreateFlags(),
			1,
			&vertexInputBindingDescription,
			3,
			vertexInputAttributeDescriptions);

		auto pipelineInputAssemblyStateCreateInfo = vk::PipelineInputAssemblyStateCreateInfo(
			vk::PipelineInputAssemblyStateCreateFlags(),
			primitiveTopology,
			VK_FALSE);

		auto viewport = vk::Viewport(
			0.0f,
			0.0f,
			static_cast<float>(surfaceExtent.width),
			static_cast<float>(surfaceExtent.height),
			0.0f,
			1.0f);
		auto scissor = vk::Rect2D(
			vk::Offset2D(0, 0),
			surfaceExtent);
		auto pipelineViewportStateCreateInfo = vk::PipelineViewportStateCreateInfo(
			vk::PipelineViewportStateCreateFlags(),
			1,
			&viewport,
			1,
			&scissor);

		auto pipelineRasterizationStateCreateInfo = vk::PipelineRasterizationStateCreateInfo(
			vk::PipelineRasterizationStateCreateFlags(),
			VK_FALSE,
			VK_FALSE,
			vk::PolygonMode::eFill,
			vk::CullModeFlagBits::eBack,
			vk::FrontFace::eClockwise,
			VK_FALSE,
			0.0f,
			0.0f,
			0.0f,
			1.0f);

		auto pipelineMultisampleStateCreateInfo = vk::PipelineMultisampleStateCreateInfo(
			vk::PipelineMultisampleStateCreateFlags(),
			vk::SampleCountFlagBits::e1,
			VK_FALSE,
			0.0f,
			nullptr,
			VK_FALSE,
			VK_FALSE);

		auto pipelineDepthStencilStateCreateInfo = vk::PipelineDepthStencilStateCreateInfo(
			vk::PipelineDepthStencilStateCreateFlags(),
			VK_TRUE,
			VK_TRUE,
			vk::CompareOp::eLess,
			VK_FALSE,
			VK_FALSE,
			vk::StencilOpState(),
			vk::StencilOpState(),
			0.0f,
			0.0f);

		auto pipelineColorBlendAttachmentStateCreateInfo = vk::PipelineColorBlendAttachmentState(
			VK_FALSE,
			vk::BlendFactor(),
			vk::BlendFactor(),
			vk::BlendOp(),
			vk::BlendFactor(),
			vk::BlendFactor(),
			vk::BlendOp(),
			vk::ColorComponentFlagBits::eR |
			vk::ColorComponentFlagBits::eG |
			vk::ColorComponentFlagBits::eB |
			vk::ColorComponentFlagBits::eA);

		auto pipelineColorBlendStateCreateInfo = vk::PipelineColorBlendStateCreateInfo(
			vk::PipelineColorBlendStateCreateFlags(),
			VK_FALSE,
			vk::LogicOp(),
			1,
			&pipelineColorBlendAttachmentStateCreateInfo);

		auto graphicsPipelineCreateInfo = vk::GraphicsPipelineCreateInfo(
			vk::PipelineCreateFlags(),
			2,
			pipelineShaderStageCreateInfos,
			&pipelineVertexInputStateCreateInfo,
			&pipelineInputAssemblyStateCreateInfo,
			nullptr,
			&pipelineViewportStateCreateInfo,
			&pipelineRasterizationStateCreateInfo,
			&pipelineMultisampleStateCreateInfo,
			&pipelineDepthStencilStateCreateInfo,
			&pipelineColorBlendStateCreateInfo,
			nullptr,
			pipelineLayout,
			renderPass,
			0,
			nullptr,
			-1);

		auto resultValue = device.createGraphicsPipeline(
			pipelineCache,
			graphicsPipelineCreateInfo);

		if (resultValue.result != vk::Result::eSuccess)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to create pipeline");
		}

		return resultValue.value;
	}
	vk::DescriptorPool VkImageDiffuseGpuPipeline::createDescriptorPool(
		vk::Device device,
		uint32_t imageCount)
	{
		vk::DescriptorPool descriptorPool;

		vk::DescriptorPoolSize descriptorPoolSizes[2] =
		{
			vk::DescriptorPoolSize(
				vk::DescriptorType::eUniformBuffer,
				imageCount),
			vk::DescriptorPoolSize(
				vk::DescriptorType::eCombinedImageSampler,
				imageCount),
		};

		auto descriptorPoolCreateInfo = vk::DescriptorPoolCreateInfo(
			vk::DescriptorPoolCreateFlags(),
			imageCount,
			2,
			descriptorPoolSizes);

		auto result = device.createDescriptorPool(
			&descriptorPoolCreateInfo,
			nullptr,
			&descriptorPool);

		if (result != vk::Result::eSuccess)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to create descriptor pool");
		}

		return descriptorPool;
	}
	vk::ImageView VkImageDiffuseGpuPipeline::createImageView(
		vk::Device device,
		vk::Image image)
	{
		vk::ImageView imageView;

		auto imageViewCreateInfo = vk::ImageViewCreateInfo(
			vk::ImageViewCreateFlags(),
			image,
			vk::ImageViewType::e2D,
			vk::Format::eR8G8B8A8Srgb,
			vk::ComponentMapping(),
			vk::ImageSubresourceRange(
				vk::ImageAspectFlagBits::eColor,
				0,
				1,
				0,
				1));

		auto result = device.createImageView(
			&imageViewCreateInfo,
			nullptr,
			&imageView);

		if(result != vk::Result::eSuccess)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to create image view");
		}

		return imageView;
	}
	vk::Sampler VkImageDiffuseGpuPipeline::createImageSampler(
		vk::Device device,
		vk::Filter magFilter,
		vk::Filter minFilter,
		vk::SamplerMipmapMode mipmapMode,
		vk::SamplerAddressMode addressModeU,
		vk::SamplerAddressMode addressModeV,
		vk::SamplerAddressMode addressModeW)
	{
		vk::Sampler sampler;

		auto samplerCreateInfo = vk::SamplerCreateInfo(
			vk::SamplerCreateFlags(),
			magFilter,
			minFilter,
			mipmapMode,
			addressModeU,
			addressModeV,
			addressModeW,
			0.0f,
			VK_FALSE,
			0.0f,
			VK_FALSE,
			vk::CompareOp::eNever,
			0.0f,
			0.0f,
			vk::BorderColor::eFloatOpaqueBlack,
			VK_FALSE);

		auto result = device.createSampler(
			&samplerCreateInfo,
			nullptr,
			&sampler);

		if(result != vk::Result::eSuccess)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to create sampler");
		}

		return sampler;
	}
	std::vector<std::shared_ptr<VkGpuBuffer>> VkImageDiffuseGpuPipeline::createUniformBuffers(
		VmaAllocator allocator,
		uint32_t imageCount)
	{
		auto uniformBuffers = std::vector<std::shared_ptr<VkGpuBuffer>>(imageCount);

		for (size_t i = 0; i < imageCount; i++)
		{
			uniformBuffers[i] = std::make_shared<VkGpuBuffer>(
				allocator,
				static_cast<vk::BufferUsageFlags>(0),
				VMA_MEMORY_USAGE_CPU_TO_GPU,
				GpuBufferType::Uniform,
				sizeof(UniformBufferObject));
		}

		return uniformBuffers;
	}
	std::vector<vk::DescriptorSet> VkImageDiffuseGpuPipeline::createDescriptorSets(
		vk::Device device,
		vk::DescriptorPool descriptorPool,
		vk::DescriptorSetLayout descriptorSetLayout,
		vk::ImageView imageView,
		vk::Sampler sampler,
		size_t imageCount,
		const std::vector<std::shared_ptr<VkGpuBuffer>>& uniformBuffers)
	{
		auto descriptorSetLayouts = std::vector<vk::DescriptorSetLayout>(
			imageCount,
			descriptorSetLayout);
		auto descriptorSetAllocateInfo = vk::DescriptorSetAllocateInfo(
			descriptorPool,
			static_cast<uint32_t>(imageCount),
			descriptorSetLayouts.data());

		auto descriptorSets = std::vector<vk::DescriptorSet>(imageCount);

		auto result = device.allocateDescriptorSets(
			&descriptorSetAllocateInfo,
			descriptorSets.data());

		if (result != vk::Result::eSuccess)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to allocate descriptor sets");
		}

		for (size_t i = 0; i < imageCount; i++)
		{
			auto descriptorBufferInfo = vk::DescriptorBufferInfo(
				uniformBuffers[i]->getBuffer(),
				0,
				sizeof(UniformBufferObject));
			auto descriptorImageInfo = vk::DescriptorImageInfo(
				sampler,
				imageView,
				vk::ImageLayout::eShaderReadOnlyOptimal);


			vk::WriteDescriptorSet writeDescriptorSets[2] =
			{
				vk::WriteDescriptorSet(
					descriptorSets[i],
					0,
					0,
					1,
					vk::DescriptorType::eUniformBuffer,
					nullptr,
					&descriptorBufferInfo,
					nullptr),
				vk::WriteDescriptorSet(
					descriptorSets[i],
					1,
					0,
					1,
					vk::DescriptorType::eCombinedImageSampler,
					&descriptorImageInfo,
					nullptr,
					nullptr),
			};

			device.updateDescriptorSets(
				2,
				writeDescriptorSets,
				0,
				nullptr);
		}

		return descriptorSets;
	}

	VkImageDiffuseGpuPipeline::VkImageDiffuseGpuPipeline(
		vk::Device device,
		VmaAllocator allocator,
		vk::RenderPass renderPass,
		uint32_t imageCount,
		const vk::Extent2D& surfaceExtent,
		GpuDrawMode drawMode,
		GpuImageFilter _imageMinFilter,
		GpuImageFilter _imageMagFilter,
		GpuImageFilter _mipmapFilter,
		GpuImageWrap _imageWrapU,
		GpuImageWrap _imageWrapV,
		GpuImageWrap _imageWrapW,
		const std::shared_ptr<VkGpuShader>& _vertexShader,
		const std::shared_ptr<VkGpuShader>& _fragmentShader,
		const std::shared_ptr<VkGpuImage>& _image,
		const UniformBufferObject& _ubo) :
		VkGpuPipeline(device, drawMode),
		imageMinFilter(_imageMinFilter),
		imageMagFilter(_imageMagFilter),
		mipmapFilter(_mipmapFilter),
		imageWrapU(_imageWrapU),
		imageWrapV(_imageWrapV),
		imageWrapW(_imageWrapW),
		vertexShader(_vertexShader),
		fragmentShader(_fragmentShader),
		image(_image),
		ubo(_ubo)
	{
		if(!allocator)
		{
			throw NullException(
				THIS_FUNCTION_NAME,
				"allocator");
		}
		if(!renderPass)
		{
			throw NullException(
				THIS_FUNCTION_NAME,
				"renderPass");
		}
		if (!_vertexShader)
		{
			throw NullException(
				THIS_FUNCTION_NAME,
				"vertexShader");
		}
		if (!_fragmentShader)
		{
			throw NullException(
				THIS_FUNCTION_NAME,
				"fragmentShader");
		}
		if (!_image)
		{
			throw NullException(
				THIS_FUNCTION_NAME,
				"image");
		}

		descriptorSetLayout = createDescriptorSetLayout(
			device);
		pipelineLayout = createPipelineLayout(
			device,
			descriptorSetLayout);
		pipeline = createPipeline(
			device,
			pipelineCache,
			pipelineLayout,
			renderPass,
			surfaceExtent,
			toVkGpuDrawMode(drawMode),
			_vertexShader,
			_fragmentShader);
		descriptorPool = createDescriptorPool(
			device,
			imageCount);
		imageView = createImageView(
			device,
			_image->getImage());
		imageSampler = createImageSampler(
			device,
			toVkGpuImageFilter(_imageMinFilter),
			toVkGpuImageFilter(_imageMagFilter),
			toVkGpuMipmapFilter(_mipmapFilter),
			toVkGpuImageWrap(_imageWrapU),
			toVkGpuImageWrap(_imageWrapV),
			toVkGpuImageWrap(_imageWrapW));
		uniformBuffers = createUniformBuffers(
			allocator,
			imageCount);
		descriptorSets = createDescriptorSets(
			device,
			descriptorPool,
			descriptorSetLayout,
			imageView,
			imageSampler,
			imageCount,
			uniformBuffers);
	}
	VkImageDiffuseGpuPipeline::~VkImageDiffuseGpuPipeline()
	{
		device.destroySampler(
			imageSampler);
		device.destroyImageView(
			imageView);
		device.destroyDescriptorPool(
			descriptorPool);
		device.destroyPipeline(
			pipeline);
		device.destroyPipelineLayout(
			pipelineLayout);
		device.destroyDescriptorSetLayout(
			descriptorSetLayout);
	}

	GpuImageFilter VkImageDiffuseGpuPipeline::getImageMinFilter() const
	{
		return imageMinFilter;
	}
	GpuImageFilter VkImageDiffuseGpuPipeline::getImageMagFilter() const
	{
		return imageMagFilter;
	}
	GpuImageFilter VkImageDiffuseGpuPipeline::getMipmapFilter() const
	{
		return mipmapFilter;
	}

	GpuImageWrap VkImageDiffuseGpuPipeline::getImageWrapU() const
	{
		return imageWrapU;
	}
	GpuImageWrap VkImageDiffuseGpuPipeline::getImageWrapV() const
	{
		return imageWrapV;
	}
	GpuImageWrap VkImageDiffuseGpuPipeline::getImageWrapW() const
	{
		return imageWrapW;
	}

	std::shared_ptr<GpuImage> VkImageDiffuseGpuPipeline::getImage() const
	{
		return image;
	}

	const FloatVector4& VkImageDiffuseGpuPipeline::getObjectColor() const
	{
		return ubo.objectColor;
	}
	void VkImageDiffuseGpuPipeline::setObjectColor(const FloatVector4& color)
	{
		ubo.objectColor = Vector4(color);
	}

	const FloatVector4& VkImageDiffuseGpuPipeline::getAmbientColor() const
	{
		return ubo.ambientColor;
	}
	void VkImageDiffuseGpuPipeline::setAmbientColor(const FloatVector4& color)
	{
		ubo.ambientColor = Vector4(color);
	}

	const FloatVector4& VkImageDiffuseGpuPipeline::getLightColor() const
	{
		return ubo.lightColor;
	}
	void VkImageDiffuseGpuPipeline::setLightColor(const FloatVector4& color)
	{
		ubo.lightColor = Vector4(color);
	}

	const FloatVector3& VkImageDiffuseGpuPipeline::getLightDirection() const
	{
		return ubo.lightDirection;
	}
	void VkImageDiffuseGpuPipeline::setLightDirection(const FloatVector3& direction)
	{
		ubo.lightDirection = Vector3(direction.getNormalized());
	}

	const FloatVector2& VkImageDiffuseGpuPipeline::getImageScale() const
	{
		return ubo.imageScale;
	}
	void VkImageDiffuseGpuPipeline::setImageScale(const FloatVector2& scale)
	{
		ubo.imageScale = Vector2(scale);
	}

	const FloatVector2& VkImageDiffuseGpuPipeline::getImageOffset() const
	{
		return ubo.imageOffset;
	}
	void VkImageDiffuseGpuPipeline::setImageOffset(const FloatVector2& offset)
	{
		ubo.imageOffset = Vector2(offset);
	}

	void VkImageDiffuseGpuPipeline::recreate(
		VmaAllocator allocator,
		vk::RenderPass renderPass,
		uint32_t imageCount,
		const vk::Extent2D& extent)
	{
		if(!allocator)
		{
			throw NullException(
				THIS_FUNCTION_NAME,
				"allocator");
		}
		if(!renderPass)
		{
			throw NullException(
				THIS_FUNCTION_NAME,
				"renderPass");
		}

		device.destroyDescriptorPool(
			descriptorPool);
		device.destroyPipeline(
			pipeline);

		pipeline = createPipeline(
			device,
			pipelineCache,
			pipelineLayout,
			renderPass,
			extent,
			toVkGpuDrawMode(drawMode),
			vertexShader,
			fragmentShader);
		descriptorPool = createDescriptorPool(
			device,
			imageCount);
		imageView = createImageView(
			device,
			image->getImage());
		uniformBuffers = createUniformBuffers(
			allocator,
			imageCount);
		descriptorSets = createDescriptorSets(
			device,
			descriptorPool,
			descriptorSetLayout,
			imageView,
			imageSampler,
			imageCount,
			uniformBuffers);
	}
	void VkImageDiffuseGpuPipeline::flush(
		size_t imageIndex)
	{
		auto uniformBuffer = uniformBuffers.at(imageIndex);
		auto mappedData = uniformBuffer->map(GpuBufferAccess::WriteOnly);
		memcpy(mappedData, &ubo, sizeof(UniformBufferObject));
		uniformBuffer->unmap();
	}
	void VkImageDiffuseGpuPipeline::bind(
		vk::CommandBuffer commandBuffer,
		size_t imageIndex)
	{
		VkGpuPipeline::bind(commandBuffer, imageIndex);

		commandBuffer.bindPipeline(
			vk::PipelineBindPoint::eGraphics,
			pipeline);
		commandBuffer.bindDescriptorSets(
			vk::PipelineBindPoint::eGraphics,
			pipelineLayout,
			0,
			1,
			&descriptorSets[imageIndex],
			0,
			nullptr);
	}

	void VkImageDiffuseGpuPipeline::setUniforms(
		const FloatMatrix4& model,
		const FloatMatrix4& view,
		const FloatMatrix4& proj,
		const FloatMatrix4& viewProj,
		const FloatMatrix4& mvp)
	{
		auto normal = model.getInverted().getTransposed();

		bindedCommandBuffer.pushConstants(
			pipelineLayout,
			vk::ShaderStageFlagBits::eVertex,
			0,
			sizeof(FloatMatrix4),
			&mvp);
		bindedCommandBuffer.pushConstants(
			pipelineLayout,
			vk::ShaderStageFlagBits::eVertex,
			sizeof(FloatMatrix4),
			sizeof(FloatMatrix4),
			&normal);
	}
}
