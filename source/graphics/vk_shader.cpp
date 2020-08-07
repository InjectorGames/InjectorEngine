#include <injector/graphics/vk_shader.hpp>
#include <injector/file_stream.hpp>

#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	vk::ShaderModule VkShader::createShaderModule(
		const vk::Device& device, const std::vector<char>& code)
	{
		auto shaderModuleCreateInfo = vk::ShaderModuleCreateInfo(
			{}, code.size(), reinterpret_cast<const uint32_t*>(code.data()));
		auto shaderModule = device.createShaderModule(shaderModuleCreateInfo);

		if (!shaderModule)
			throw std::runtime_error("Failed to create Vulkan shader module");

		return shaderModule;
	}

	VkShader::VkShader(ShaderStage stage, 
		const vk::Device& _device, const std::string& path) :
		Shader(stage), device(_device)
	{
		std::string extension;

		switch (stage)
		{
		case ShaderStage::Vertex:
			extension = ".vert.spv";
			break;
		case ShaderStage::TessellationControl:
			extension = ".tesc.spv";
			break;
		case ShaderStage::TessellationEvaluation:
			extension = ".tese.spv";
			break;
		case ShaderStage::Geometry:
			extension = ".geom.spv";
			break;
		case ShaderStage::Fragment:
			extension = ".frag.spv";
			break;
		case ShaderStage::Compute:
			extension = ".comp.spv";
			break;
		case ShaderStage::Raygen:
			extension = ".rgen.spv";
			break;
		case ShaderStage::AnyHit:
			extension = ".rahit.spv";
			break;
		case ShaderStage::ClosestHit:
			extension = ".rchit.spv";
			break;
		case ShaderStage::Miss:
			extension = ".rmiss.spv";
			break;
		case ShaderStage::Intersection:
			extension = ".rint.spv";
			break;
		case ShaderStage::Callable:
			extension = ".rcall.spv";
			break;
		case ShaderStage::Task:
			extension = ".task.spv";
			break;
		case ShaderStage::Mesh:
			extension = ".mesh.spv";
			break;
		default:
			throw std::runtime_error("Unsupported Vulkan shader stage");
		}

		auto fileStream = FileStream(path + extension, 
			std::ios::in | std::ios::binary | std::ios::ate);

		if (!fileStream.is_open())
			throw std::runtime_error("Failed to open shader file: " + path + extension);

		auto size = static_cast<size_t>(fileStream.tellg());
		fileStream.seekg(0, fileStream.beg);

		auto code = std::vector<char>(size);
		fileStream.read(code.data(), size);

		shaderModule = createShaderModule(_device, code);
	}
	VkShader::~VkShader()
	{
		device.destroyShaderModule(shaderModule);
		device = nullptr;
	}

	const vk::Device& VkShader::getDevice() const noexcept
	{
		return device;
	}
	const vk::ShaderModule& VkShader::getShaderModule() const noexcept
	{
		return shaderModule;
	}
}
