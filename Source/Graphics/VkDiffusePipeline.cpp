#include "Injector/Graphics/VkDiffusePipeline.hpp"
#include "Injector/Storage/FileStream.hpp"
#include "Injector/Graphics/GraphicsException.hpp"
#include "Injector/Graphics/VkShader.hpp"

namespace Injector
{
	vk::Pipeline VkDiffusePipeline::createPipeline(
		vk::Device device,
		vk::PipelineCache pipelineCache,
		vk::PipelineLayout pipelineLayout,
		vk::RenderPass renderPass,
		const vk::Extent2D& surfaceExtent)
	{
		auto vertexCode = FileStream::readAllBytes(
			"resources/shaders/diffuse.vert.spv");
		auto vertexShader = VkShader(device, vertexCode);

		auto fragmentCode = FileStream::readAllBytes(
			"resources/shaders/diffuse.frag.spv");
		auto fragmentShader = VkShader(device, fragmentCode);

		auto pipelineShaderStageCreateInfos = std::vector<vk::PipelineShaderStageCreateInfo>
		{
			vk::PipelineShaderStageCreateInfo({}, vk::ShaderStageFlagBits::eVertex,
				vertexShader.getShaderModule(), "main", nullptr),
			vk::PipelineShaderStageCreateInfo({}, vk::ShaderStageFlagBits::eFragment,
				fragmentShader.getShaderModule(), "main", nullptr),
		};

		auto vertexInputBindingDescription = vk::VertexInputBindingDescription(
			0, sizeof(Vector3) * 2, vk::VertexInputRate::eVertex);

		auto vertexInputAttributeDescriptions = std::vector<vk::VertexInputAttributeDescription>
		{
			vk::VertexInputAttributeDescription(
				0, 0, vk::Format::eR32G32B32Sfloat, 0),
			vk::VertexInputAttributeDescription(
				1, 0, vk::Format::eR32G32B32Sfloat, sizeof(Vector3)),
		};

		auto pipelineVertexInputStateCreateInfo = vk::PipelineVertexInputStateCreateInfo({},
			1, &vertexInputBindingDescription,
			static_cast<uint32_t>(vertexInputAttributeDescriptions.size()),
			vertexInputAttributeDescriptions.data());

		auto pipelineInputAssemblyStateCreateInfo =
			vk::PipelineInputAssemblyStateCreateInfo({}, vk::PrimitiveTopology::eTriangleList, false);

		auto viewport = vk::Viewport(
			0.0f, 0.0f, surfaceExtent.width, surfaceExtent.height, 0.0f, 1.0f);
		auto scissor = vk::Rect2D(
			vk::Offset2D(0, 0), surfaceExtent);
		auto pipelineViewportStateCreateInfo = vk::PipelineViewportStateCreateInfo(
			{}, 1, &viewport, 1, &scissor);

		auto pipelineRasterizationStateCreateInfo = vk::PipelineRasterizationStateCreateInfo(
			{}, false, false,
			vk::PolygonMode::eFill, vk::CullModeFlagBits::eBack, vk::FrontFace::eClockwise,
			false, 0.0f, 0.0f, 0.0f, 1.0f);

		auto pipelineMultisampleStateCreateInfo = vk::PipelineMultisampleStateCreateInfo(
			{}, vk::SampleCountFlagBits::e1, false, {}, {}, false, false);

		auto pielineColorBlendAttacmentStateCreateInfo = vk::PipelineColorBlendAttachmentState(
			false, {}, {}, {}, {}, {}, {},
			vk::ColorComponentFlagBits::eR |
			vk::ColorComponentFlagBits::eG |
			vk::ColorComponentFlagBits::eB |
			vk::ColorComponentFlagBits::eA);

		auto pipelineColorBlendStateCreateInfo =
			vk::PipelineColorBlendStateCreateInfo({}, false, {},
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
			pipelineLayout,
			renderPass, 0,
			nullptr, -1);

		auto resultValue = device.createGraphicsPipeline(pipelineCache, graphicsPipelineCreateInfo);

		if (resultValue.result != vk::Result::eSuccess)
			throw GraphicsException("Failed to create Vulkan diffuse pipeline");

		return resultValue.value;
	}
	vk::DescriptorPool VkDiffusePipeline::createDescriptorPool(
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
			throw GraphicsException("Failed to create Vulkan descriptor pool");

		return descriptorPool;
	}
	std::vector<std::shared_ptr<VkBuffer>> VkDiffusePipeline::createUniformBuffers(
		VmaAllocator allocator,
		uint32_t imageCount)
	{
		auto uniformBuffers = std::vector<std::shared_ptr<VkBuffer>>(imageCount);

		for (size_t i = 0; i < imageCount; i++)
		{
			uniformBuffers[i] = std::make_shared<VkBuffer>(
				BufferType::Uniform, sizeof(UniformBufferObject),
				allocator, static_cast<vk::BufferUsageFlags>(0),
				VMA_MEMORY_USAGE_CPU_TO_GPU);
		}

		return uniformBuffers;
	}
	std::vector<vk::DescriptorSet> VkDiffusePipeline::createDescriptorSets(
		vk::Device device,
		vk::DescriptorPool descriptorPool,
		vk::DescriptorSetLayout descriptorSetLayout,
		size_t imageCount,
		const std::vector<std::shared_ptr<VkBuffer>>& uniformBuffers)
	{
		auto descriptorSetLayouts = std::vector<vk::DescriptorSetLayout>(
			imageCount, descriptorSetLayout);
		auto descriptorSetAllocateInfo = vk::DescriptorSetAllocateInfo(
			descriptorPool, imageCount, descriptorSetLayouts.data());

		auto descriptorSets = std::vector<vk::DescriptorSet>(imageCount);

		auto result = device.allocateDescriptorSets(
			&descriptorSetAllocateInfo, descriptorSets.data());

		if (result != vk::Result::eSuccess)
			throw GraphicsException("Failed to allocate Vulkan descriptor sets");

		for (size_t i = 0; i < imageCount; i++)
		{
			auto descriptorBufferInfo = vk::DescriptorBufferInfo(
				uniformBuffers[i]->getBuffer(),
				0, sizeof(Vector4) * 3 + sizeof(Vector3));
			auto writeDescriptorSet = vk::WriteDescriptorSet(
				descriptorSets[i], 0, 0, 1,
				vk::DescriptorType::eUniformBuffer,
				nullptr, &descriptorBufferInfo, nullptr);

			device.updateDescriptorSets(1, &writeDescriptorSet, 0, nullptr);
		}

		return descriptorSets;
	}

	VkDiffusePipeline::VkDiffusePipeline(
		vk::Device device,
		VmaAllocator allocator,
		vk::RenderPass renderPass,
		uint32_t imageCount,
		const vk::Extent2D& surfaceExtent,
		const Vector4& objectColor,
		const Vector4& ambientColor,
		const Vector4& lightColor,
		const Vector3& lightDirection) :
		VkPipeline(device),
		ubo(objectColor, ambientColor, lightColor, lightDirection)
	{
		auto descriptorSetLayoutBinding = vk::DescriptorSetLayoutBinding(0,
			vk::DescriptorType::eUniformBuffer, 1,
			vk::ShaderStageFlagBits::eFragment, nullptr);
		auto descriptorSetLayoutCreateInfo = vk::DescriptorSetLayoutCreateInfo(
			{}, 1, &descriptorSetLayoutBinding);

		auto result = device.createDescriptorSetLayout(
			&descriptorSetLayoutCreateInfo, nullptr, &descriptorSetLayout);

		auto pushConstantRange = vk::PushConstantRange(
			vk::ShaderStageFlagBits::eVertex, 0, sizeof(Matrix4) + sizeof(Matrix3));

		auto pipelineLayoutCreateInfo = vk::PipelineLayoutCreateInfo({},
			1, &descriptorSetLayout,
			1, &pushConstantRange);

		result = device.createPipelineLayout(
			&pipelineLayoutCreateInfo, nullptr, &pipelineLayout);

		if (result != vk::Result::eSuccess)
			throw GraphicsException("Failed to create Vulkan pipeline layout");

		pipeline = createPipeline(
			device, pipelineCache, pipelineLayout, renderPass, surfaceExtent);
		descriptorPool = createDescriptorPool(
			device, imageCount);
		uniformBuffers = createUniformBuffers(
			allocator, imageCount);
		descriptorSets = createDescriptorSets(
			device, descriptorPool, descriptorSetLayout, imageCount, uniformBuffers);
	}
	VkDiffusePipeline::~VkDiffusePipeline()
	{
		device.destroyDescriptorPool(descriptorPool);
		device.destroyPipeline(pipeline);
		device.destroyPipelineLayout(pipelineLayout);
		device.destroyDescriptorSetLayout(descriptorSetLayout);
	}

	void VkDiffusePipeline::recreate(
		VmaAllocator allocator,
		vk::RenderPass renderPass,
		uint32_t imageCount,
		const vk::Extent2D& surfaceExtent)
	{
		device.destroyDescriptorPool(descriptorPool);
		device.destroyPipeline(pipeline);

		pipeline = createPipeline(
			device, pipelineCache, pipelineLayout, renderPass, surfaceExtent);
		descriptorPool = createDescriptorPool(
			device, imageCount);
		uniformBuffers = createUniformBuffers(
			allocator, imageCount);
		descriptorSets = createDescriptorSets(
			device, descriptorPool, descriptorSetLayout, imageCount, uniformBuffers);
	}
	void VkDiffusePipeline::flush(
		size_t imageIndex)
	{
		auto uniformBuffer = uniformBuffers[imageIndex];
		auto mappedData = uniformBuffer->map(BufferAccess::WriteOnly);
		memcpy(mappedData, &ubo, sizeof(UniformBufferObject));
		uniformBuffer->unmap();
	}
	void VkDiffusePipeline::bind(
		vk::CommandBuffer commandBuffer,
		size_t imageIndex)
	{
		VkPipeline::bind(commandBuffer, imageIndex);
		commandBuffer.bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline);
		commandBuffer.bindDescriptorSets(vk::PipelineBindPoint::eGraphics, 
			pipelineLayout, 0, 1, &descriptorSets[imageIndex], 0, nullptr);
	}

	void VkDiffusePipeline::setUniforms(
		const Matrix4& model,
		const Matrix4& view,
		const Matrix4& proj,
		const Matrix4& viewProj,
		const Matrix4& mvp)
	{
		auto normal = model.getInversed().getTransposed().getMatrix3();
		bindedCommandBuffer.pushConstants(pipelineLayout,
			vk::ShaderStageFlagBits::eVertex, 0, sizeof(Matrix4), &mvp);
		bindedCommandBuffer.pushConstants(pipelineLayout,
			vk::ShaderStageFlagBits::eVertex, sizeof(Matrix4), sizeof(Matrix3), &normal);
	}

	const Vector4& VkDiffusePipeline::getObjectColor() const
	{
		return ubo.objectColor;
	}
	void VkDiffusePipeline::setObjectColor(const Vector4& objectColor)
	{
		ubo.objectColor = Vector4(objectColor);
	}

	const Vector4& VkDiffusePipeline::getAmbientColor() const
	{
		return ubo.ambientColor;
	}
	void VkDiffusePipeline::setAmbientColor(const Vector4& ambientColor)
	{
		ubo.ambientColor = Vector4(ambientColor);
	}

	const Vector4& VkDiffusePipeline::getLightColor() const
	{
		return ubo.lightColor;
	}
	void VkDiffusePipeline::setLightColor(const Vector4& lightColor)
	{
		ubo.lightColor = Vector4(lightColor);
	}

	const Vector3& VkDiffusePipeline::getLightDirection() const
	{
		return ubo.lightDirection;
	}
	void VkDiffusePipeline::setLightDirection(const Vector3& lightDirection)
	{
		ubo.lightDirection = Vector3(lightDirection.getNormalized());
	}
}
