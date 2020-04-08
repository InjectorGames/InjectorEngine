#include <injector_engine.hpp>

namespace Injector
{
	const std::string VulkanShader::DefaultMainName = "main";

	vk::ShaderModule VulkanShader::CreateInstance(const vk::Device& device, const std::vector<uint32_t>& shaderCode)
	{
		vk::ShaderModuleCreateInfo shaderModuleCreateInfo({}, shaderCode.size(), shaderCode.data());
		return device.createShaderModule(shaderModuleCreateInfo);
	}
	vk::ShaderModule VulkanShader::CreateInstance(const vk::Device& device, const std::vector<uint8_t>& shaderCode)
	{
		vk::ShaderModuleCreateInfo shaderModuleCreateInfo({}, shaderCode.size(), reinterpret_cast<const uint32_t*>(shaderCode.data()));
		return device.createShaderModule(shaderModuleCreateInfo);
	}
	vk::ShaderModule VulkanShader::CreateInstance(const vk::Device& device, const std::string& filePath)
	{
		auto shaderCode = Engine::ReadBytesFromFile(filePath);
		return CreateInstance(device, shaderCode);
	}

	VulkanShader::VulkanShader(vk::Device _device, const std::vector<uint32_t>& shaderCode, Type type) : Shader(type), device(_device), instance(CreateInstance(_device, shaderCode)) {}
	VulkanShader::VulkanShader(vk::Device _device, const std::vector<uint8_t>& shaderCode, Type type) : Shader(type), device(_device), instance(CreateInstance(_device, shaderCode)) {}
	VulkanShader::VulkanShader(vk::Device _device, const std::string& filePath, Type type) : Shader(type), device(_device), instance(CreateInstance(_device, filePath)) {}

	VulkanShader::~VulkanShader()
	{
		device.destroyShaderModule(instance);
	}

	vk::PipelineShaderStageCreateInfo VulkanShader::GetPipelineStageCreateInfo(vk::ShaderStageFlagBits stage, const std::string& name, const vk::SpecializationInfo* info)
	{
		return vk::PipelineShaderStageCreateInfo({}, stage, instance, name.c_str(), info);
	}
}
