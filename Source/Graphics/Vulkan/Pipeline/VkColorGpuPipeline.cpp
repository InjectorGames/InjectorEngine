#include "Injector/Graphics/Vulkan/Pipeline/VkColorGpuPipeline.hpp"
#include "Injector/Exception/NullException.hpp"
#include "Injector/Graphics/Vulkan/VkGpuDrawMode.hpp"

namespace Injector
{
	vk::PipelineLayout VkColorGpuPipeline::createPipelineLayout(
		vk::Device device)
	{
		vk::PipelineLayout pipelineLayout;

		auto pushConstantRanges = std::vector<vk::PushConstantRange>{
			vk::PushConstantRange(
				vk::ShaderStageFlagBits::eVertex,
				0,
				sizeof(Matrix4)),
			vk::PushConstantRange(
				vk::ShaderStageFlagBits::eFragment,
				sizeof(Matrix4),
				sizeof(Vector4)),
		};

		auto pipelineLayoutCreateInfo = vk::PipelineLayoutCreateInfo(
			vk::PipelineLayoutCreateFlags(),
			0,
			nullptr,
			static_cast<uint32_t>(pushConstantRanges.size()),
			pushConstantRanges.data());

		auto result = device.createPipelineLayout(
			&pipelineLayoutCreateInfo,
			nullptr,
			&pipelineLayout);

		if (result != vk::Result::eSuccess)
		{
			throw Exception(
				"VkColorGpuPipeline",
				"createPipelineLayout",
				"Failed to create pipeline layout");
		}

		return pipelineLayout;
	}
	vk::Pipeline VkColorGpuPipeline::createPipeline(
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
			sizeof(float) * 3,
			vk::VertexInputRate::eVertex);
		auto vertexInputAttributeDescription = vk::VertexInputAttributeDescription(
			0,
			0,
			vk::Format::eR32G32B32Sfloat,
			0);

		auto pipelineVertexInputStateCreateInfo = vk::PipelineVertexInputStateCreateInfo(
			vk::PipelineVertexInputStateCreateFlags(),
			1,
			&vertexInputBindingDescription,
			1,
			&vertexInputAttributeDescription);

		auto pipelineInputAssemblyStateCreateInfo = vk::PipelineInputAssemblyStateCreateInfo(
			vk::PipelineInputAssemblyStateCreateFlags(),
			primitiveTopology,
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
			vk::PipelineViewportStateCreateFlags(),
			1,
			&viewport,
			1,
			&scissor);

		auto pipelineRasterizationStateCreateInfo = vk::PipelineRasterizationStateCreateInfo(
			vk::PipelineRasterizationStateCreateFlags(),
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
			vk::PipelineMultisampleStateCreateFlags(),
			vk::SampleCountFlagBits::e1,
			false,
			0.0f,
			nullptr,
			false,
			false);

		auto pipelineColorBlendAttachmentStateCreateInfo = vk::PipelineColorBlendAttachmentState(
			false,
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
			false,
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
				"VkColorGpuPipeline",
				"createPipeline",
				"Failed to create pipeline");
		}

		return resultValue.value;
	}

	VkColorGpuPipeline::VkColorGpuPipeline(
		vk::Device device,
		vk::RenderPass renderPass,
		const vk::Extent2D& surfaceExtent,
		GpuDrawMode drawMode,
		const std::shared_ptr<VkGpuShader>& _vertexShader,
		const std::shared_ptr<VkGpuShader>& _fragmentShader,
		const Vector4& _color) :
		VkGpuPipeline(device, drawMode),
		vertexShader(_vertexShader),
		fragmentShader(_fragmentShader),
		color(_color)
	{
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
				"VkColorGpuPipeline",
				"VkColorGpuPipeline",
				"vertexShader");
		}
		if (!_fragmentShader)
		{
			throw NullException(
				"VkColorGpuPipeline",
				"VkColorGpuPipeline",
				"fragmentShader");
		}

		pipelineLayout = createPipelineLayout(
			device);
		pipeline = createPipeline(
			device,
			pipelineCache,
			pipelineLayout,
			renderPass,
			surfaceExtent,
			toVkGpuDrawMode(drawMode),
			_vertexShader,
			_fragmentShader);
	}
	VkColorGpuPipeline::~VkColorGpuPipeline()
	{
		device.destroyPipeline(
			pipeline);
		device.destroyPipelineLayout(
			pipelineLayout);
	}

	const Vector4& VkColorGpuPipeline::getColor() const
	{
		return color;
	}
	void VkColorGpuPipeline::setColor(const Vector4& _color)
	{
		color = Vector4(_color);
	}

	void VkColorGpuPipeline::recreate(
		VmaAllocator allocator,
		vk::RenderPass renderPass,
		uint32_t imageCount,
		const vk::Extent2D& surfaceExtent)
	{
		device.destroyPipeline(
			pipeline);

		pipeline = createPipeline(
			device,
			pipelineCache,
			pipelineLayout,
			renderPass,
			surfaceExtent,
			toVkGpuDrawMode(drawMode),
			vertexShader,
			fragmentShader);
	}
	void VkColorGpuPipeline::flush(
		size_t imageIndex)
	{
	}
	void VkColorGpuPipeline::bind(
		vk::CommandBuffer commandBuffer,
		size_t imageIndex)
	{
		VkGpuPipeline::bind(
			commandBuffer,
			imageIndex);
		commandBuffer.bindPipeline(
			vk::PipelineBindPoint::eGraphics,
			pipeline);
	}
	void VkColorGpuPipeline::setUniforms(
		const Matrix4& model,
		const Matrix4& view,
		const Matrix4& proj,
		const Matrix4& viewProj,
		const Matrix4& mvp)
	{
		bindedCommandBuffer.pushConstants(
			pipelineLayout,
			vk::ShaderStageFlagBits::eVertex,
			0,
			sizeof(Matrix4),
			&mvp);
		bindedCommandBuffer.pushConstants(
			pipelineLayout,
			vk::ShaderStageFlagBits::eFragment,
			sizeof(Matrix4),
			sizeof(Vector4),
			&color);
	}
}
