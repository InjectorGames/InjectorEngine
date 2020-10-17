#include "Injector/Graphics/Vulkan/Pipeline/VkDiffuseGpuPipeline.hpp"
#include "Injector/Storage/FileStream.hpp"
#include "Injector/Exception/NullException.hpp"

namespace Injector
{
	vk::Pipeline VkDiffuseGpuPipeline::createPipeline(
		vk::Device device,
		vk::PipelineCache pipelineCache,
		vk::PipelineLayout pipelineLayout,
		vk::RenderPass renderPass,
		const vk::Extent2D& surfaceExtent,
		const std::shared_ptr<VkGpuShader>& vertexShader,
		const std::shared_ptr<VkGpuShader>& fragmentShader)
	{
		auto pipelineShaderStageCreateInfos = std::vector<vk::PipelineShaderStageCreateInfo>{
			vk::PipelineShaderStageCreateInfo(
				{},
				vk::ShaderStageFlagBits::eVertex,
				vertexShader->getShaderModule(),
				"main",
				nullptr),
			vk::PipelineShaderStageCreateInfo(
				{},
				vk::ShaderStageFlagBits::eFragment,
				fragmentShader->getShaderModule(),
				"main",
				nullptr),
		};

		auto vertexInputBindingDescription = vk::VertexInputBindingDescription(
			0,
			sizeof(Vector3) * 2,
			vk::VertexInputRate::eVertex);

		auto vertexInputAttributeDescriptions = std::vector<vk::VertexInputAttributeDescription>{
			vk::VertexInputAttributeDescription(
				0,
				0,
				vk::Format::eR32G32B32Sfloat,
				0),
			vk::VertexInputAttributeDescription(
				1,
				0,
				vk::Format::eR32G32B32Sfloat,
				sizeof(Vector3)),
		};

		auto pipelineVertexInputStateCreateInfo = vk::PipelineVertexInputStateCreateInfo(
			{},
			1,
			&vertexInputBindingDescription,
			static_cast<uint32_t>(vertexInputAttributeDescriptions.size()),
			vertexInputAttributeDescriptions.data());

		auto pipelineInputAssemblyStateCreateInfo = vk::PipelineInputAssemblyStateCreateInfo(
			{},
			vk::PrimitiveTopology::eTriangleList,
			false);

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
			{},
			1,
			&viewport,
			1,
			&scissor);

		auto pipelineRasterizationStateCreateInfo = vk::PipelineRasterizationStateCreateInfo(
			{},
			false,
			false,
			vk::PolygonMode::eFill,
			vk::CullModeFlagBits::eBack,
			vk::FrontFace::eClockwise,
			false,
			0.0f,
			0.0f,
			0.0f,
			1.0f);

		auto pipelineMultisampleStateCreateInfo = vk::PipelineMultisampleStateCreateInfo(
			{},
			vk::SampleCountFlagBits::e1,
			false,
			{},
			{},
			false,
			false);

		auto pipelineColorBlendAttachmentStateCreateInfo = vk::PipelineColorBlendAttachmentState(
			false,
			{},
			{},
			{},
			{},
			{},
			{},
			vk::ColorComponentFlagBits::eR |
			vk::ColorComponentFlagBits::eG |
			vk::ColorComponentFlagBits::eB |
			vk::ColorComponentFlagBits::eA);

		auto pipelineColorBlendStateCreateInfo = vk::PipelineColorBlendStateCreateInfo(
				{},
				false,
				{},
				1,
				&pipelineColorBlendAttachmentStateCreateInfo);

		auto graphicsPipelineCreateInfo = vk::GraphicsPipelineCreateInfo(
			{},
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
				"VkDiffuseGpuPipeline",
				"createPipeline",
				"Failed to create pipeline");
		}

		return resultValue.value;
	}
	vk::DescriptorPool VkDiffuseGpuPipeline::createDescriptorPool(
		vk::Device device,
		uint32_t imageCount)
	{
		vk::DescriptorPool descriptorPool;

		auto descriptorPoolSize = vk::DescriptorPoolSize(
			vk::DescriptorType::eUniformBuffer,
			imageCount);
		auto descriptorPoolCreateInfo = vk::DescriptorPoolCreateInfo(
			{},
			imageCount,
			1,
			&descriptorPoolSize);

		auto result = device.createDescriptorPool(
			&descriptorPoolCreateInfo,
			nullptr,
			&descriptorPool);

		if (result != vk::Result::eSuccess)
		{
			throw Exception(
				"VkDiffuseGpuPipeline",
				"createDescriptorPool",
				"Failed to create descriptor pool");
		}

		return descriptorPool;
	}
	std::vector<std::shared_ptr<VkGpuBuffer>> VkDiffuseGpuPipeline::createUniformBuffers(
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
	std::vector<vk::DescriptorSet> VkDiffuseGpuPipeline::createDescriptorSets(
		vk::Device device,
		vk::DescriptorPool descriptorPool,
		vk::DescriptorSetLayout descriptorSetLayout,
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
				"VkDiffuseGpuPipeline",
				"createDescriptorSets",
				"Failed to allocate descriptor sets");
		}

		for (size_t i = 0; i < imageCount; i++)
		{
			auto descriptorBufferInfo = vk::DescriptorBufferInfo(
				uniformBuffers[i]->getBuffer(),
				0,
				sizeof(Vector4) * 3 + sizeof(Vector3));
			auto writeDescriptorSet = vk::WriteDescriptorSet(
				descriptorSets[i],
				0,
				0,
				1,
				vk::DescriptorType::eUniformBuffer,
				nullptr,
				&descriptorBufferInfo,
				nullptr);

			device.updateDescriptorSets(
				1,
				&writeDescriptorSet,
				0,
				nullptr);
		}

		return descriptorSets;
	}

	VkDiffuseGpuPipeline::VkDiffuseGpuPipeline(
		vk::Device device,
		VmaAllocator allocator,
		vk::RenderPass renderPass,
		uint32_t imageCount,
		const vk::Extent2D& surfaceExtent,
		const std::shared_ptr<VkGpuShader>& _vertexShader,
		const std::shared_ptr<VkGpuShader>& _fragmentShader,
		const UniformBufferObject& _ubo) :
		VkGpuPipeline(device),
		vertexShader(_vertexShader),
		fragmentShader(_fragmentShader),
		ubo(_ubo)
	{
		if(!allocator)
		{
			throw NullException(
				"VkColorGpuPipeline",
				"VkColorGpuPipeline",
				"allocator");
		}
		if(!renderPass)
		{
			throw NullException(
				"VkColorGpuPipeline",
				"VkColorGpuPipeline",
				"renderPass");
		}
		if (!_vertexShader)
		{
			throw NullException(
				"VkDiffuseGpuPipeline",
				"VkDiffuseGpuPipeline",
				"vertexShader");
		}
		if (!_fragmentShader)
		{
			throw NullException(
				"VkDiffuseGpuPipeline",
				"VkDiffuseGpuPipeline",
				"fragmentShader");
		}

		auto descriptorSetLayoutBinding = vk::DescriptorSetLayoutBinding(
			0,
			vk::DescriptorType::eUniformBuffer,
			1,
			vk::ShaderStageFlagBits::eFragment,
			nullptr);
		auto descriptorSetLayoutCreateInfo = vk::DescriptorSetLayoutCreateInfo(
			{},
			1,
			&descriptorSetLayoutBinding);

		auto result = device.createDescriptorSetLayout(
			&descriptorSetLayoutCreateInfo,
			nullptr,
			&descriptorSetLayout);

		auto pushConstantRange = vk::PushConstantRange(
			vk::ShaderStageFlagBits::eVertex,
			0,
			sizeof(Matrix4) + sizeof(Matrix3));

		auto pipelineLayoutCreateInfo = vk::PipelineLayoutCreateInfo(
			{},
			1,
			&descriptorSetLayout,
			1,
			&pushConstantRange);

		result = device.createPipelineLayout(
			&pipelineLayoutCreateInfo,
			nullptr,
			&pipelineLayout);

		if (result != vk::Result::eSuccess)
		{
			throw Exception(
				"VkDiffuseGpuPipeline",
				"VkDiffuseGpuPipeline",
				"Failed to create pipeline layout");
		}

		pipeline = createPipeline(
			device,
			pipelineCache,
			pipelineLayout,
			renderPass,
			surfaceExtent,
			_vertexShader,
			_fragmentShader);
		descriptorPool = createDescriptorPool(
			device,
			imageCount);
		uniformBuffers = createUniformBuffers(
			allocator,
			imageCount);
		descriptorSets = createDescriptorSets(
			device,
			descriptorPool,
			descriptorSetLayout,
			imageCount,
			uniformBuffers);
	}
	VkDiffuseGpuPipeline::~VkDiffuseGpuPipeline()
	{
		device.destroyDescriptorPool(descriptorPool);
		device.destroyPipeline(pipeline);
		device.destroyPipelineLayout(pipelineLayout);
		device.destroyDescriptorSetLayout(descriptorSetLayout);
	}

	void VkDiffuseGpuPipeline::recreate(
		VmaAllocator allocator,
		vk::RenderPass renderPass,
		uint32_t imageCount,
		const vk::Extent2D& extent)
	{
		device.destroyDescriptorPool(descriptorPool);
		device.destroyPipeline(pipeline);

		pipeline = createPipeline(
			device,
			pipelineCache,
			pipelineLayout,
			renderPass,
			extent,
			vertexShader,
			fragmentShader);
		descriptorPool = createDescriptorPool(
			device,
			imageCount);
		uniformBuffers = createUniformBuffers(
			allocator,
			imageCount);
		descriptorSets = createDescriptorSets(
			device,
			descriptorPool,
			descriptorSetLayout,
			imageCount,
			uniformBuffers);
	}
	void VkDiffuseGpuPipeline::flush(
		size_t imageIndex)
	{
		auto uniformBuffer = uniformBuffers[imageIndex];
		auto mappedData = uniformBuffer->map(GpuBufferAccess::WriteOnly);
		memcpy(mappedData, &ubo, sizeof(UniformBufferObject));
		uniformBuffer->unmap();
	}
	void VkDiffuseGpuPipeline::bind(
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

	void VkDiffuseGpuPipeline::setUniforms(
		const Matrix4& model,
		const Matrix4& view,
		const Matrix4& proj,
		const Matrix4& viewProj,
		const Matrix4& mvp)
	{
		auto normal = model.getInverted().getInverted().getMatrix3();

		bindedCommandBuffer.pushConstants(
			pipelineLayout,
			vk::ShaderStageFlagBits::eVertex,
			0,
			sizeof(Matrix4),
			&mvp);
		bindedCommandBuffer.pushConstants(
			pipelineLayout,
			vk::ShaderStageFlagBits::eVertex,
			sizeof(Matrix4),
			sizeof(Matrix3),
			&normal);
	}

	const Vector4& VkDiffuseGpuPipeline::getObjectColor() const
	{
		return ubo.objectColor;
	}
	void VkDiffuseGpuPipeline::setObjectColor(const Vector4& color)
	{
		ubo.objectColor = Vector4(color);
	}

	const Vector4& VkDiffuseGpuPipeline::getAmbientColor() const
	{
		return ubo.ambientColor;
	}
	void VkDiffuseGpuPipeline::setAmbientColor(const Vector4& color)
	{
		ubo.ambientColor = Vector4(color);
	}

	const Vector4& VkDiffuseGpuPipeline::getLightColor() const
	{
		return ubo.lightColor;
	}
	void VkDiffuseGpuPipeline::setLightColor(const Vector4& color)
	{
		ubo.lightColor = Vector4(color);
	}

	const Vector3& VkDiffuseGpuPipeline::getLightDirection() const
	{
		return ubo.lightDirection;
	}
	void VkDiffuseGpuPipeline::setLightDirection(const Vector3& direction)
	{
		ubo.lightDirection = Vector3(direction.getNormalized());
	}
}
