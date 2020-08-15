#include <injector/graphics/vk_color_pipeline.hpp>
#include <injector/graphics/vk_shader.hpp>

namespace INJECTOR_NAMESPACE
{
	VkColorPipeline::VkColorPipeline(
		vk::Device device,
		vk::RenderPass renderPass,
		vk::Extent2D surfaceExtent) :
		VkPipeline(device)
	{
		auto pushConstantRanges = std::vector<vk::PushConstantRange>
		{
			vk::PushConstantRange(vk::ShaderStageFlagBits::eVertex,
				0, sizeof(Matrix4)),
			vk::PushConstantRange(vk::ShaderStageFlagBits::eFragment,
				sizeof(Matrix4), sizeof(Vector4)),
		};

		auto pipelineLayoutCreateInfo = vk::PipelineLayoutCreateInfo({},
			0, nullptr, pushConstantRanges.size(), pushConstantRanges.data());
		auto result = device.createPipelineLayout(
			&pipelineLayoutCreateInfo, nullptr, &pipelineLayout);

		if (result != vk::Result::eSuccess)
			throw std::runtime_error("Failed to create Vulkan pipeline layout");

		pipeline = nullptr;
		recreate(renderPass, surfaceExtent);
	}
	VkColorPipeline::~VkColorPipeline()
	{
		device.destroyPipeline(pipeline);
		device.destroyPipelineLayout(pipelineLayout);
	}

	void VkColorPipeline::bind(
		vk::CommandBuffer commandBuffer)
	{
		commandBuffer.bindPipeline(vk::PipelineBindPoint::eGraphics, pipeline);
		commandBuffer.pushConstants(pipelineLayout,
			vk::ShaderStageFlagBits::eVertex, 0, sizeof(Matrix4), &mvp);
		commandBuffer.pushConstants(pipelineLayout,
			vk::ShaderStageFlagBits::eFragment, sizeof(Matrix4), sizeof(Vector4), &color);
	}
	void VkColorPipeline::recreate(
		vk::RenderPass renderPass,
		vk::Extent2D surfaceExtent)
	{
		if(pipeline)
			device.destroyPipeline(pipeline);

		auto vertexShader = VkShader(device, vk::ShaderStageFlagBits::eVertex,
			"resources/shaders/vulkan/color");
		auto fragmentShader = VkShader(device, vk::ShaderStageFlagBits::eFragment,
			"resources/shaders/vulkan/color");

		auto pipelineShaderStageCreateInfos = std::vector<vk::PipelineShaderStageCreateInfo>
		{
			vk::PipelineShaderStageCreateInfo
			(
				{}, vk::ShaderStageFlagBits::eVertex,
				vertexShader.getShaderModule(),
				"main", nullptr
			),
			vk::PipelineShaderStageCreateInfo
			(
				{}, vk::ShaderStageFlagBits::eFragment,
				fragmentShader.getShaderModule(),
				"main", nullptr
			),
		};

		auto vertexInputBindingDescription = vk::VertexInputBindingDescription(
			0, sizeof(float) * 3, vk::VertexInputRate::eVertex);
		auto vertexInputAttributeDescriptions =
			std::vector<vk::VertexInputAttributeDescription>
		{
			vk::VertexInputAttributeDescription(
				0, 0, vk::Format::eR32G32B32Sfloat, 0),
		};
		auto pipelineVertexInputStateCreateInfo = vk::PipelineVertexInputStateCreateInfo({},
			1, &vertexInputBindingDescription,
			vertexInputAttributeDescriptions.size(),
			vertexInputAttributeDescriptions.data());

		auto pipelineInputAssemblyStateCreateInfo =
			vk::PipelineInputAssemblyStateCreateInfo({}, vk::PrimitiveTopology::eTriangleList, false);

		auto viewport = vk::Viewport(
			0.0f, 0.0f,
			surfaceExtent.width,
			surfaceExtent.height,
			0.0f, 1.0f);

		auto scissor = vk::Rect2D(
			vk::Offset2D(0, 0), surfaceExtent);

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

		// TODO: rewrite
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
			pipelineLayout,
			renderPass,
			0,
			nullptr,
			-1);

		auto resultValue = device.createGraphicsPipeline(
			pipelineCache, graphicsPipelineCreateInfo);

		if (resultValue.result != vk::Result::eSuccess)
			throw std::runtime_error("Failed to create Vulkan pipeline");

		pipeline = resultValue.value;
	}
}
