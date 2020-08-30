#include <injector/graphics/vk_color_pipeline.hpp>
#include <injector/graphics/vk_shader.hpp>
#include <injector/file_stream.hpp>

#include <vector>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	vk::Pipeline VkColorPipeline::createPipeline(
		vk::Device device,
		vk::PipelineCache pipelineCache,
		vk::PipelineLayout pipelineLayout,
		vk::RenderPass renderPass,
		const vk::Extent2D& surfaceExtent)
	{
		auto vertexCode = FileStream::readAllBytes(
			"resources/shaders/color.vert.spv");
		auto vertexShader = VkShader(device, vertexCode);

		auto fragmentCode = FileStream::readAllBytes(
			"resources/shaders/color.frag.spv");
		auto fragmentShader = VkShader(device, fragmentCode);

		auto pipelineShaderStageCreateInfos =
			std::vector<vk::PipelineShaderStageCreateInfo>
		{
			vk::PipelineShaderStageCreateInfo({}, vk::ShaderStageFlagBits::eVertex,
				vertexShader.getShaderModule(), "main", nullptr),
			vk::PipelineShaderStageCreateInfo({}, vk::ShaderStageFlagBits::eFragment,
				fragmentShader.getShaderModule(), "main", nullptr),
		};

		auto vertexInputBindingDescription = vk::VertexInputBindingDescription(
			0, sizeof(float) * 3, vk::VertexInputRate::eVertex);
		auto vertexInputAttributeDescription = vk::VertexInputAttributeDescription(
			0, 0, vk::Format::eR32G32B32Sfloat, 0);

		auto pipelineVertexInputStateCreateInfo = vk::PipelineVertexInputStateCreateInfo({},
			1, &vertexInputBindingDescription,
			1, &vertexInputAttributeDescription);

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
			throw std::runtime_error("Failed to create Vulkan color pipeline");

		return resultValue.value;
	}

	VkColorPipeline::VkColorPipeline(
		vk::Device device,
		vk::RenderPass renderPass,
		const vk::Extent2D& surfaceExtent,
		const Vector4& _color) :
		VkPipeline(device),
		color(_color)
	{
		auto pushConstantRanges = std::vector<vk::PushConstantRange>
		{
			vk::PushConstantRange(vk::ShaderStageFlagBits::eVertex, 
				0, sizeof(Matrix4)),
			vk::PushConstantRange(vk::ShaderStageFlagBits::eFragment, 
				sizeof(Matrix4), sizeof(Vector4)),
		};

		auto pipelineLayoutCreateInfo = vk::PipelineLayoutCreateInfo({},
			0, nullptr,
			static_cast<uint32_t>(pushConstantRanges.size()),
			pushConstantRanges.data());

		auto result = device.createPipelineLayout(
			&pipelineLayoutCreateInfo, nullptr, &pipelineLayout);

		if (result != vk::Result::eSuccess)
			throw std::runtime_error("Failed to create Vulkan pipeline layout");

		pipeline = createPipeline(
			device, pipelineCache, pipelineLayout, renderPass, surfaceExtent);
	}
	VkColorPipeline::~VkColorPipeline()
	{
		device.destroyPipeline(pipeline);
		device.destroyPipelineLayout(pipelineLayout);
	}

	const Vector4& VkColorPipeline::getColor() const
	{
		return color;
	}
	void VkColorPipeline::setColor(const Vector4& _color)
	{
		color = Vector4(_color);
	}

	void VkColorPipeline::recreate(
		VmaAllocator allocator,
		vk::RenderPass renderPass,
		uint32_t imageCount,
		const vk::Extent2D& surfaceExtent)
	{
		device.destroyPipeline(pipeline);

		pipeline = createPipeline(
			device, pipelineCache, pipelineLayout, renderPass, surfaceExtent);
	}
	void VkColorPipeline::flush(
		size_t imageIndex)
	{}
	void VkColorPipeline::bind(
		vk::CommandBuffer commandBuffer,
		size_t imageIndex)
	{
		VkPipeline::bind(commandBuffer, imageIndex);
		commandBuffer.bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline);
	}
	void VkColorPipeline::setUniforms(
		const Matrix4& model,
		const Matrix4& view,
		const Matrix4& proj,
		const Matrix4& viewProj,
		const Matrix4& mvp)
	{
		bindedCommandBuffer.pushConstants(pipelineLayout, 
			vk::ShaderStageFlagBits::eVertex, 0, sizeof(Matrix4), &mvp);
		bindedCommandBuffer.pushConstants(pipelineLayout,
			vk::ShaderStageFlagBits::eFragment, sizeof(Matrix4), sizeof(Vector4), &color);
	}
}
