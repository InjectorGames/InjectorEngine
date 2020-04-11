#include <injector_engine.hpp>

namespace Injector
{
	const std::string VulkanShader::DefaultMainName = "main";

	VulkanShader::VulkanShader(vk::Device _device, const std::vector<uint32_t>& shaderCode, Type type) : Shader(type)
	{
		device = _device;
		vk::ShaderModuleCreateInfo shaderModuleCreateInfo({}, shaderCode.size(), shaderCode.data());
		instance = _device.createShaderModule(shaderModuleCreateInfo);
	}
	VulkanShader::VulkanShader(vk::Device _device, const std::vector<uint8_t>& shaderCode, Type type) : Shader(type)
	{
		device = _device;
		vk::ShaderModuleCreateInfo shaderModuleCreateInfo({}, shaderCode.size(), reinterpret_cast<const uint32_t*>(shaderCode.data()));
		instance = _device.createShaderModule(shaderModuleCreateInfo);
	}
	VulkanShader::VulkanShader(vk::Device _device, const std::string& filePath, Type type) : Shader(type)
	{
		device = _device;
		auto shaderCode = Engine::ReadBytesFromFile(filePath);
		vk::ShaderModuleCreateInfo shaderModuleCreateInfo({}, shaderCode.size(), reinterpret_cast<const uint32_t*>(shaderCode.data()));
		instance = _device.createShaderModule(shaderModuleCreateInfo);
	}

	VulkanShader::~VulkanShader()
	{
		device.destroyShaderModule(instance);
	}

	vk::Device VulkanShader::GetDevice() const
	{
		return device;
	}
	vk::ShaderModule VulkanShader::GetInstance() const
	{
		return instance;
	}

	vk::PipelineShaderStageCreateInfo VulkanShader::CreatePipelineStageCreateInfo(vk::ShaderStageFlagBits stage, const std::string& name, const vk::SpecializationInfo* info) const
	{
		return vk::PipelineShaderStageCreateInfo({}, stage, instance, name.c_str(), info);
	}
}
