#include <injector/graphics/vk_shader.hpp>
#include <injector/file_stream.hpp>

#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	VkShader::VkShader(
		const vk::Device& _device, 
		const std::string& path,
		ShaderStage stage) :
		Shader(stage),
		device(_device)
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
		fileStream.close();

		auto shaderModuleCreateInfo = vk::ShaderModuleCreateInfo(
			{}, code.size(), reinterpret_cast<const uint32_t*>(code.data()));
		shaderModule = device.createShaderModule(shaderModuleCreateInfo);

		if (!shaderModule)
			throw std::runtime_error("Failed to create Vulkan shader module");
	}
	VkShader::~VkShader()
	{
		device.destroyShaderModule(shaderModule);
		device = nullptr;
	}

	vk::Device VkShader::getDevice() const noexcept
	{
		return device;
	}
	vk::ShaderModule VkShader::getShaderModule() const noexcept
	{
		return shaderModule;
	}

	vk::ShaderStageFlagBits VkShader::toVkStage(ShaderStage stage)
	{
		switch (stage)
		{
		case ShaderStage::Vertex:
			return vk::ShaderStageFlagBits::eVertex;
		case ShaderStage::TessellationControl:
			return vk::ShaderStageFlagBits::eTessellationControl;
		case ShaderStage::TessellationEvaluation:
			return vk::ShaderStageFlagBits::eTessellationEvaluation;
		case ShaderStage::Geometry:
			return vk::ShaderStageFlagBits::eGeometry;
		case ShaderStage::Fragment:
			return vk::ShaderStageFlagBits::eFragment;
		case ShaderStage::Compute:
			return vk::ShaderStageFlagBits::eCompute;
		case ShaderStage::Raygen:
			return vk::ShaderStageFlagBits::eRaygenKHR;
		case ShaderStage::AnyHit:
			return vk::ShaderStageFlagBits::eAnyHitKHR;
		case ShaderStage::ClosestHit:
			return vk::ShaderStageFlagBits::eClosestHitKHR;
		case ShaderStage::Miss:
			return vk::ShaderStageFlagBits::eMissKHR;
		case ShaderStage::Intersection:
			return vk::ShaderStageFlagBits::eIntersectionKHR;
		case ShaderStage::Callable:
			return vk::ShaderStageFlagBits::eCallableKHR;
		case ShaderStage::Task:
			return vk::ShaderStageFlagBits::eTaskNV;
		case ShaderStage::Mesh:
			return vk::ShaderStageFlagBits::eMeshNV;
		default:
			throw std::runtime_error("Unsupported Vulkan shader stage");
		}
	}
	ShaderStage VkShader::toStage(vk::ShaderStageFlagBits stage)
	{
		switch (stage)
		{
		case vk::ShaderStageFlagBits::eVertex:
			return ShaderStage::Vertex;
		case vk::ShaderStageFlagBits::eTessellationControl:
			return ShaderStage::TessellationControl;
		case vk::ShaderStageFlagBits::eTessellationEvaluation:
			return ShaderStage::TessellationEvaluation;
		case vk::ShaderStageFlagBits::eGeometry:
			return ShaderStage::Geometry;
		case vk::ShaderStageFlagBits::eFragment:
			return ShaderStage::Fragment;
		case vk::ShaderStageFlagBits::eCompute:
			return ShaderStage::Compute;
		case vk::ShaderStageFlagBits::eRaygenKHR:
			return ShaderStage::Raygen;
		case vk::ShaderStageFlagBits::eAnyHitKHR:
			return ShaderStage::AnyHit;
		case vk::ShaderStageFlagBits::eClosestHitKHR:
			return ShaderStage::ClosestHit;
		case vk::ShaderStageFlagBits::eMissKHR:
			return ShaderStage::Miss;
		case vk::ShaderStageFlagBits::eIntersectionKHR:
			return ShaderStage::Intersection;
		case vk::ShaderStageFlagBits::eCallableKHR:
			return ShaderStage::Callable;
		case vk::ShaderStageFlagBits::eTaskNV:
			return ShaderStage::Task;
		case vk::ShaderStageFlagBits::eMeshNV:
			return ShaderStage::Mesh;
		default:
			throw std::runtime_error("Unsupported Vulkan shader stage");
		}
	}
}
