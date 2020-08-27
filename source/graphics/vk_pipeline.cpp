#include <injector/graphics/vk_pipeline.hpp>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	VkPipeline::VkPipeline(
		vk::Device _device) :
		device(_device)
	{
		auto pipelineCacheCreateInfo = vk::PipelineCacheCreateInfo();
		auto result = _device.createPipelineCache(
			&pipelineCacheCreateInfo, nullptr, &pipelineCache);

		if (result != vk::Result::eSuccess)
			throw std::runtime_error("Failed to create Vulkan pipeline cache");
	}
	VkPipeline::~VkPipeline()
	{
		device.destroyPipelineCache(pipelineCache);
	}

	void VkPipeline::recreate(
		uint32_t imageCount,
		vk::RenderPass renderPass,
		vk::Extent2D surfaceExtent)
	{
		throw std::runtime_error("Not implemented Vulkan pipeline function");
	}
	void VkPipeline::bind(
		uint32_t imageIndex,
		vk::CommandBuffer commandBuffer)
	{
		throw std::runtime_error("Not implemented Vulkan pipeline function");
	}

	/*vk::Pipeline VkPipeline::createPipeline(
		vk::Device device,
		vk::PipelineLayout layout,
		vk::PipelineCache cache,
		vk::RenderPass renderPass,
		const vk::Extent2D& surfaceExtent,
		const std::vector<ShaderHandle>& shaders,
		const std::vector<VertexBinding>& vertexBindings,
		const std::vector<VertexAttribute>& vertexAttributes)
	{
		auto pipelineShaderStageCreateInfos =
			std::vector<vk::PipelineShaderStageCreateInfo>(shaders.size());

		for (size_t i = 0; i < shaders.size(); i++)
		{
			auto& shader = shaders[i];
			auto vkShader = std::dynamic_pointer_cast<VkShader>(shader);

			if (!vkShader)
				throw std::runtime_error("Failed to cast Vulkan pipeline shader");

			pipelineShaderStageCreateInfos[i] = vk::PipelineShaderStageCreateInfo(
				{}, VkShader::toVkStage(vkShader->getStage()),
				vkShader->getShaderModule(),
				"main", nullptr);
		}

		auto vertexInputBindingDescriptions =
			std::vector<vk::VertexInputBindingDescription>(vertexBindings.size());

		for (size_t i = 0; i < vertexBindings.size(); i++)
		{
			auto& vertexBinding = vertexBindings[i];

			vertexInputBindingDescriptions[i] = vk::VertexInputBindingDescription(
				vertexBinding.binding,
				vertexBinding.stride,
				toVkVertexInput(vertexBinding.input));
		}

		auto vertexInputAttributeDescriptions =
			std::vector<vk::VertexInputAttributeDescription>(vertexAttributes.size());


		for (size_t i = 0; i < vertexAttributes.size(); i++)
		{
			auto& vertexAttribute = vertexAttributes[i];

			vertexInputAttributeDescriptions[i] = vk::VertexInputAttributeDescription(
				vertexAttribute.location,
				vertexAttribute.binding,
				toVkVertexFormat(vertexAttribute.format),
				vertexAttribute.offset);
		}

		auto pipelineVertexInputStateCreateInfo = vk::PipelineVertexInputStateCreateInfo({},
			static_cast<uint32_t>(vertexInputBindingDescriptions.size()),
			vertexInputBindingDescriptions.data(),
			static_cast<uint32_t>(vertexInputAttributeDescriptions.size()),
			vertexInputAttributeDescriptions.data());

		auto pipelineInputAssemblyStateCreateInfo =
			vk::PipelineInputAssemblyStateCreateInfo({}, vk::PrimitiveTopology::eTriangleList, false);

		auto viewport = vk::Viewport(
			0.0f, 0.0f, surfaceExtent.width, surfaceExtent.height, 0.0f, 1.0f);
		auto scissor = vk::Rect2D(vk::Offset2D(0, 0), surfaceExtent);

		auto pipelineViewportStateCreateInfo = vk::PipelineViewportStateCreateInfo(
			{}, 1, &viewport, 1, &scissor);

		auto pipelineRasterizationStateCreateInfo = vk::PipelineRasterizationStateCreateInfo(
			{}, false, false,
			vk::PolygonMode::eFill, vk::CullModeFlagBits::eNone, vk::FrontFace::eClockwise,
			false, 0.0f, 0.0f, 0.0f, 1.0f);

		auto pipelineMultisampleStateCreateInfo = vk::PipelineMultisampleStateCreateInfo(
			{}, vk::SampleCountFlagBits::e1, false, 1.0f, nullptr, false, false);

		auto pielineColorBlendAttacmentStateCreateInfo = vk::PipelineColorBlendAttachmentState(
			false,
			vk::BlendFactor::eOne,
			vk::BlendFactor::eZero,
			vk::BlendOp::eAdd,
			vk::BlendFactor::eOne,
			vk::BlendFactor::eZero,
			vk::BlendOp::eAdd,
			vk::ColorComponentFlagBits::eR |
			vk::ColorComponentFlagBits::eG |
			vk::ColorComponentFlagBits::eB |
			vk::ColorComponentFlagBits::eA);

		auto pipelineColorBlendStateCreateInfo =
			vk::PipelineColorBlendStateCreateInfo({}, false, vk::LogicOp::eCopy,
				1, &pielineColorBlendAttacmentStateCreateInfo);

		auto graphicsPipelineCreateInfo = vk::GraphicsPipelineCreateInfo({},
			static_cast<uint32_t>(pipelineShaderStageCreateInfos.size()),
			pipelineShaderStageCreateInfos.data(),
			&pipelineVertexInputStateCreateInfo,
			&pipelineInputAssemblyStateCreateInfo,
			nullptr,
			&pipelineViewportStateCreateInfo,
			&pipelineRasterizationStateCreateInfo,
			&pipelineMultisampleStateCreateInfo,
			nullptr,
			&pipelineColorBlendStateCreateInfo,
			nullptr,
			layout,
			renderPass, 0,
			nullptr, -1);

		auto resultValue = device.createGraphicsPipeline(cache, graphicsPipelineCreateInfo);

		if (resultValue.result != vk::Result::eSuccess)
			throw std::runtime_error("Failed to create Vulkan pipeline");

		return resultValue.value;
	}
	vk::DescriptorPool VkPipeline::createDescriptorPool(
		vk::Device device,
		uint32_t imageCount)
	{
		vk::DescriptorPool descriptorPool;

		auto descriptorPoolSize = vk::DescriptorPoolSize(
			vk::DescriptorType::eUniformBuffer, imageCount);
		auto descriptorPoolCreateInfo = vk::DescriptorPoolCreateInfo({},
			imageCount, 1, &descriptorPoolSize);

		auto result = device.createDescriptorPool(
			&descriptorPoolCreateInfo, nullptr, &descriptorPool);

		if (result != vk::Result::eSuccess)
			throw std::runtime_error("Failed to create Vulkan descriptor pool");

		return descriptorPool;
	}
	std::vector<vk::DescriptorSet> VkPipeline::createDescriptorSets(
		vk::Device device,
		vk::DescriptorSetLayout descriptorSetLayout,
		vk::DescriptorPool descriptorPool,
		uint32_t imageCount,
		const std::vector<VkBufferHandle>& uniformBuffers)
	{
		auto descriptorSetLayouts = std::vector<vk::DescriptorSetLayout>(
			imageCount, descriptorSetLayout);
		auto descriptorSetAllocateInfo = vk::DescriptorSetAllocateInfo(
			descriptorPool, imageCount, descriptorSetLayouts.data());

		auto descriptorSets = std::vector<vk::DescriptorSet>(imageCount);

		auto result = device.allocateDescriptorSets(
			&descriptorSetAllocateInfo, descriptorSets.data());

		if (result != vk::Result::eSuccess)
			throw std::runtime_error("Failed to allocate Vulkan descriptor sets");

		auto descriptorBufferInfo = vk::DescriptorBufferInfo(
			nullptr, );

		VkWriteDescriptorSet descriptorWrite {};
		descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		descriptorWrite.dstSet = descriptorSets[i];
		descriptorWrite.dstBinding = 0;
		descriptorWrite.dstArrayElement = 0;
		descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
		descriptorWrite.descriptorCount = 1;
		descriptorWrite.pBufferInfo = descriptorBufferInfo.data();
		descriptorWrite.pImageInfo = nullptr; // Optional
		descriptorWrite.pTexelBufferView = nullptr; // Optional

		for (size_t i = 0; i < imageCount; i++)
		{
			descriptorBufferInfo.buffer = uniformBuffers[i]->getBuffer();
			vkUpdateDescriptorSets(device, 1, &descriptorWrite, 0, nullptr);
		}

		return descriptorSets;
	}

	VkPipeline::VkPipeline(
		vk::Device _device,
		vk::RenderPass renderPass,
		uint32_t imageCount,
		const vk::Extent2D& surfaceExtent,
		const std::vector<DescriptorBinding>& descriptorBindings,
		const std::vector<ShaderHandle>& shaders,
		const std::vector<VertexBinding>& vertexBindings,
		const std::vector<VertexAttribute>& vertexAttributes) :
		Pipeline(shaders, vertexBindings, vertexAttributes),
		device(_device)
	{
		auto pipelineCacheCreateInfo = vk::PipelineCacheCreateInfo();
		auto result = _device.createPipelineCache(
			&pipelineCacheCreateInfo, nullptr, &pipelineCache);

		if (result != vk::Result::eSuccess)
			throw std::runtime_error("Failed to create Vulkan pipeline cache");

		auto descriptorSetLayoutBindings = std::vector<vk::DescriptorSetLayoutBinding>(
			descriptorBindings.size());

		for (size_t i = 0; i < descriptorBindings.size(); i++)
		{
			auto& descriptorBinding = descriptorBindings[i];

			vk::ShaderStageFlags shaderStages;

			for (size_t i = 0; i < descriptorBinding.shaderStages.size(); i++)
				shaderStages |= VkShader::toVkStage(descriptorBinding.shaderStages[i]);

			descriptorSetLayoutBindings[i] = vk::DescriptorSetLayoutBinding(
				descriptorBinding.binding,
				toVkDescriptorType(descriptorBinding.type),
				descriptorBinding.count,
				shaderStages);
		}

		auto descriptorSetLayoutCreateInfo = vk::DescriptorSetLayoutCreateInfo({},
			descriptorSetLayoutBindings.size(), descriptorSetLayoutBindings.data());
		result = _device.createDescriptorSetLayout(
			&descriptorSetLayoutCreateInfo, nullptr, &descriptorSetLayout);

		if (result != vk::Result::eSuccess)
			throw std::runtime_error("Failed to create Vulkan descriptor set layout");

		auto pipelineLayoutCreateInfo = vk::PipelineLayoutCreateInfo({},
			1, &descriptorSetLayout, 0, nullptr);
		result = device.createPipelineLayout(
			&pipelineLayoutCreateInfo, nullptr, &pipelineLayout);

		if (result != vk::Result::eSuccess)
			throw std::runtime_error("Failed to create Vulkan pipeline layout");

		pipeline = createPipeline(
			_device,
			pipelineLayout,
			nullptr,
			renderPass,
			surfaceExtent,
			shaders,
			vertexBindings,
			vertexAttributes);
		descriptorPool = createDescriptorPool(
			_device,
			imageCount);
		descriptorSets = createDescriptorSets(
			_device,
			descriptorSetLayout,
			descriptorPool,
			imageCount);
	}
	VkPipeline::~VkPipeline()
	{
		uniformBuffers.clear();
		device.destroyDescriptorPool(descriptorPool);
		device.destroyPipeline(pipeline);
		device.destroyPipelineLayout(pipelineLayout);
		device.destroyDescriptorSetLayout(descriptorSetLayout);
		device.destroyPipelineCache(pipelineCache);
	}

	void VkPipeline::recreate(
		uint32_t imageCount,
		VmaAllocator allocator,
		vk::RenderPass renderPass,
		vk::Extent2D surfaceExtent)
	{
		uniformBuffers.clear();
		device.destroyDescriptorPool(descriptorPool);
		device.destroyPipeline(pipeline);

		pipeline = createPipeline(
			device,
			pipelineLayout,
			pipelineCache,
			renderPass,
			surfaceExtent,
			shaders,
			vertexBindings,
			vertexAttributes);
		descriptorPool = createDescriptorPool(
			device,
			imageCount);
		descriptorSets = createDescriptorSets(
			device,
			descriptorSetLayout,
			descriptorPool,
			imageCount);

		uniformBuffers = std::vector<VkBufferHandle>(imageCount);

		for (size_t i = 0; i < imageCount; i++)
		{
			//uniformBuffers[i] = std::make_shared<VkBuffer>(allocator, );
		}
	}
	void VkPipeline::bind(vk::CommandBuffer commandBuffer)
	{
		commandBuffer.bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline);
		commandBuffer.pushConstants(layout,
			vk::ShaderStageFlagBits::eVertex, 0, sizeof(Matrix4), &mvp);
		commandBuffer.pushConstants(layout,
			vk::ShaderStageFlagBits::eFragment, sizeof(Matrix4), sizeof(Vector4), &color);
	}

	vk::DescriptorType VkPipeline::toVkDescriptorType(DescriptorType type)
	{
		switch (type)
		{
		case DescriptorType::Sampler:
			return vk::DescriptorType::eSampler;
		case DescriptorType::CombinedImageSampler:
			return vk::DescriptorType::eCombinedImageSampler;
		case DescriptorType::SampledImage:
			return vk::DescriptorType::eSampledImage;
		case DescriptorType::StorageImage:
			return vk::DescriptorType::eStorageImage;
		case DescriptorType::UniformTexelBuffer:
			return vk::DescriptorType::eUniformTexelBuffer;
		case DescriptorType::StorageTexelBuffer:
			return vk::DescriptorType::eStorageTexelBuffer;
		case DescriptorType::UniformBuffer:
			return vk::DescriptorType::eUniformBuffer;
		case DescriptorType::StorageBuffer:
			return vk::DescriptorType::eStorageBuffer;
		case DescriptorType::UniformBufferDynamic:
			return vk::DescriptorType::eUniformBufferDynamic;
		case DescriptorType::StorageBufferDynamic:
			return vk::DescriptorType::eStorageBufferDynamic;
		case DescriptorType::InputAttachment:
			return vk::DescriptorType::eInputAttachment;
		case DescriptorType::InlineUniformBlock:
			return vk::DescriptorType::eInlineUniformBlockEXT;
		case DescriptorType::AccelerationStructure:
			return vk::DescriptorType::eAccelerationStructureKHR;
		default:
			throw std::runtime_error("Unsupported Vulkan descriptor type");
		}
	}
	DescriptorType VkPipeline::toDescriptorType(vk::DescriptorType type)
	{
		switch (type)
		{
		case vk::DescriptorType::eSampler:
			return DescriptorType::Sampler;
		case vk::DescriptorType::eCombinedImageSampler:
			return DescriptorType::CombinedImageSampler;
		case vk::DescriptorType::eSampledImage:
			return DescriptorType::SampledImage;
		case vk::DescriptorType::eStorageImage:
			return DescriptorType::StorageImage;
		case vk::DescriptorType::eUniformTexelBuffer:
			return DescriptorType::UniformTexelBuffer;
		case vk::DescriptorType::eStorageTexelBuffer:
			return DescriptorType::StorageTexelBuffer;
		case vk::DescriptorType::eUniformBuffer:
			return DescriptorType::UniformBuffer;
		case vk::DescriptorType::eStorageBuffer:
			return DescriptorType::StorageBuffer;
		case vk::DescriptorType::eUniformBufferDynamic:
			return DescriptorType::UniformBufferDynamic;
		case vk::DescriptorType::eStorageBufferDynamic:
			return DescriptorType::StorageBufferDynamic;
		case vk::DescriptorType::eInputAttachment:
			return DescriptorType::InputAttachment;
		case vk::DescriptorType::eInlineUniformBlockEXT:
			return DescriptorType::InlineUniformBlock;
		case vk::DescriptorType::eAccelerationStructureKHR:
			return DescriptorType::AccelerationStructure;
		default:
			throw std::runtime_error("Unsupported Vulkan descriptor type");
		}
	}

	vk::VertexInputRate VkPipeline::toVkVertexInput(VertexInput input)
	{
		if (input == VertexInput::Vertex)
			return vk::VertexInputRate::eVertex;
		else if (input == VertexInput::Instance)
			return vk::VertexInputRate::eInstance;
		else
			throw std::runtime_error("Unsupported Vulkan vertex input rate");
	}
	VertexInput VkPipeline::toVertexInput(vk::VertexInputRate input)
	{
		if (input == vk::VertexInputRate::eVertex)
			return VertexInput::Vertex;
		else if (input == vk::VertexInputRate::eInstance)
			return VertexInput::Instance;
		else
			throw std::runtime_error("Unsupported Vulkan vertex input rate");
	}

	vk::Format VkPipeline::toVkVertexFormat(VertexFormat format)
	{
		switch (format)
		{
		case VertexFormat::SignedByte1:
			return vk::Format::eR8Sint;
		case VertexFormat::SignedByte2:
			return vk::Format::eR8G8Sint;
		case VertexFormat::SignedByte3:
			return vk::Format::eR8G8B8Sint;
		case VertexFormat::SignedByte4:
			return vk::Format::eR8G8B8A8Sint;
		case VertexFormat::UnsignedByte1:
			return vk::Format::eR8Uint;
		case VertexFormat::UnsignedByte2:
			return vk::Format::eR8G8Uint;
		case VertexFormat::UnsignedByte3:
			return vk::Format::eR8G8B8Uint;
		case VertexFormat::UnsignedByte4:
			return vk::Format::eR8G8B8A8Uint;
		case VertexFormat::SignedShort1:
			return vk::Format::eR16Sint;
		case VertexFormat::SignedShort2:
			return vk::Format::eR16G16Sint;
		case VertexFormat::SignedShort3:
			return vk::Format::eR16G16B16Sint;
		case VertexFormat::SignedShort4:
			return vk::Format::eR16G16B16A16Sint;
		case VertexFormat::UnsignedShort1:
			return vk::Format::eR16Uint;
		case VertexFormat::UnsignedShort2:
			return vk::Format::eR16G16Uint;
		case VertexFormat::UnsignedShort3:
			return vk::Format::eR16G16B16Uint;
		case VertexFormat::UnsignedShort4:
			return vk::Format::eR16G16B16A16Uint;
		case VertexFormat::SignedInt1:
			return vk::Format::eR32Sint;
		case VertexFormat::SignedInt2:
			return vk::Format::eR32G32Sint;
		case VertexFormat::SignedInt3:
			return vk::Format::eR32G32B32Sint;
		case VertexFormat::SignedInt4:
			return vk::Format::eR32G32B32A32Sint;
		case VertexFormat::UnsignedInt1:
			return vk::Format::eR32Uint;
		case VertexFormat::UnsignedInt2:
			return vk::Format::eR32G32Uint;
		case VertexFormat::UnsignedInt3:
			return vk::Format::eR32G32B32Uint;
		case VertexFormat::UnsignedInt4:
			return vk::Format::eR32G32B32A32Uint;
		case VertexFormat::SignedLong1:
			return vk::Format::eR64Sint;
		case VertexFormat::SignefLong2:
			return vk::Format::eR64G64Sint;
		case VertexFormat::SignedLong3:
			return vk::Format::eR64G64B64Sint;
		case VertexFormat::SignedLong4:
			return vk::Format::eR64G64B64A64Sint;
		case VertexFormat::UnsignedLong1:
			return vk::Format::eR64Uint;
		case VertexFormat::UnsignedLong2:
			return vk::Format::eR64G64Uint;
		case VertexFormat::UnsignedLong3:
			return vk::Format::eR64G64B64Uint;
		case VertexFormat::UnsignedLong4:
			return vk::Format::eR64G64B64A64Uint;
		case VertexFormat::SignedHalfFloat1:
			return vk::Format::eR16Sfloat;
		case VertexFormat::SignefHalfFloat2:
			return vk::Format::eR16G16Sfloat;
		case VertexFormat::SignedHalfFloat3:
			return vk::Format::eR16G16B16Sfloat;
		case VertexFormat::SignedHalfFloat4:
			return vk::Format::eR16G16B16A16Sfloat;
		case VertexFormat::SignedFloat1:
			return vk::Format::eR32Sfloat;
		case VertexFormat::SignefFloat2:
			return vk::Format::eR32G32Sfloat;
		case VertexFormat::SignedFloat3:
			return vk::Format::eR32G32B32Sfloat;
		case VertexFormat::SignedFloat4:
			return vk::Format::eR32G32B32A32Sfloat;
		case VertexFormat::SignedDouble1:
			return vk::Format::eR64Sfloat;
		case VertexFormat::SignefDouble2:
			return vk::Format::eR64G64Sfloat;
		case VertexFormat::SignedDouble3:
			return vk::Format::eR64G64B64Sfloat;
		case VertexFormat::SignedDouble4:
			return vk::Format::eR64G64B64A64Sfloat;
		default:
			throw std::runtime_error("Unsupported Vulkan vertex format");
		}
	}
	VertexFormat VkPipeline::toVertexFormat(vk::Format format)
	{
		switch (format)
		{
		case vk::Format::eR8Sint:
			return VertexFormat::SignedByte1;
		case vk::Format::eR8G8Sint:
			return VertexFormat::SignedByte2;
		case vk::Format::eR8G8B8Sint:
			return VertexFormat::SignedByte3;
		case vk::Format::eR8G8B8A8Sint:
			return VertexFormat::SignedByte4;
		case vk::Format::eR8Uint:
			return VertexFormat::UnsignedByte1;
		case vk::Format::eR8G8Uint:
			return VertexFormat::UnsignedByte2;
		case vk::Format::eR8G8B8Uint:
			return VertexFormat::UnsignedByte3;
		case vk::Format::eR8G8B8A8Uint:
			return VertexFormat::UnsignedByte4;
		case vk::Format::eR16Sint:
			return VertexFormat::SignedShort1;
		case vk::Format::eR16G16Sint:
			return VertexFormat::SignedShort2;
		case vk::Format::eR16G16B16Sint:
			return VertexFormat::SignedShort3;
		case vk::Format::eR16G16B16A16Sint:
			return VertexFormat::SignedShort4;
		case vk::Format::eR16Uint:
			return VertexFormat::UnsignedShort1;
		case vk::Format::eR16G16Uint:
			return VertexFormat::UnsignedShort2;
		case vk::Format::eR16G16B16Uint:
			return VertexFormat::UnsignedShort3;
		case vk::Format::eR16G16B16A16Uint:
			return VertexFormat::UnsignedShort4;
		case vk::Format::eR32Sint:
			return VertexFormat::SignedInt1;
		case vk::Format::eR32G32Sint:
			return VertexFormat::SignedInt2;
		case vk::Format::eR32G32B32Sint:
			return VertexFormat::SignedInt3;
		case vk::Format::eR32G32B32A32Sint:
			return VertexFormat::SignedInt4;
		case vk::Format::eR32Uint:
			return VertexFormat::UnsignedInt1;
		case vk::Format::eR32G32Uint:
			return VertexFormat::UnsignedInt2;
		case vk::Format::eR32G32B32Uint:
			return VertexFormat::UnsignedInt3;
		case vk::Format::eR32G32B32A32Uint:
			return VertexFormat::UnsignedInt4;
		case vk::Format::eR64Sint:
			return VertexFormat::SignedLong1;
		case vk::Format::eR64G64Sint:
			return VertexFormat::SignefLong2;
		case vk::Format::eR64G64B64Sint:
			return VertexFormat::SignedLong3;
		case vk::Format::eR64G64B64A64Sint:
			return VertexFormat::SignedLong4;
		case vk::Format::eR64Uint:
			return VertexFormat::UnsignedLong1;
		case vk::Format::eR64G64Uint:
			return VertexFormat::UnsignedLong2;
		case vk::Format::eR64G64B64Uint:
			return VertexFormat::UnsignedLong3;
		case vk::Format::eR64G64B64A64Uint:
			return VertexFormat::UnsignedLong4;
		case vk::Format::eR16Sfloat:
			return VertexFormat::SignedHalfFloat1;
		case vk::Format::eR16G16Sfloat:
			return VertexFormat::SignefHalfFloat2;
		case vk::Format::eR16G16B16Sfloat:
			return VertexFormat::SignedHalfFloat3;
		case vk::Format::eR16G16B16A16Sfloat:
			return VertexFormat::SignedHalfFloat4;
		case vk::Format::eR32Sfloat:
			return VertexFormat::SignedFloat1;
		case vk::Format::eR32G32Sfloat:
			return VertexFormat::SignefFloat2;
		case vk::Format::eR32G32B32Sfloat:
			return VertexFormat::SignedFloat3;
		case vk::Format::eR32G32B32A32Sfloat:
			return VertexFormat::SignedFloat4;
		case vk::Format::eR64Sfloat:
			return VertexFormat::SignedDouble1;
		case vk::Format::eR64G64Sfloat:
			return VertexFormat::SignefDouble2;
		case vk::Format::eR64G64B64Sfloat:
			return VertexFormat::SignedDouble3;
		case vk::Format::eR64G64B64A64Sfloat:
			return VertexFormat::SignedDouble4;
		default:
			throw std::runtime_error("Unsupported Vulkan vertex format");
		}
	}*/
}
