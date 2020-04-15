#include <injector_engine/vulkan.hpp>

namespace InjectorEngine
{
	// TODO: remove this class

	const std::string VkShader::DefaultMainName = "main";

	VkShader::VkShader(vk::Device _device, const std::vector<uint32_t>& shaderCode)
	{
		device = _device;
		vk::ShaderModuleCreateInfo shaderModuleCreateInfo({}, shaderCode.size(), shaderCode.data());
		instance = _device.createShaderModule(shaderModuleCreateInfo);
	}
	VkShader::VkShader(vk::Device _device, const std::vector<uint8_t>& shaderCode)
	{
		device = _device;
		vk::ShaderModuleCreateInfo shaderModuleCreateInfo({}, shaderCode.size(), reinterpret_cast<const uint32_t*>(shaderCode.data()));
		instance = _device.createShaderModule(shaderModuleCreateInfo);
	}
	VkShader::VkShader(vk::Device _device, const std::string& filePath)
	{
		device = _device;
		auto shaderCode = Engine::ReadBytesFromFile(filePath);
		vk::ShaderModuleCreateInfo shaderModuleCreateInfo({}, shaderCode.size(), reinterpret_cast<const uint32_t*>(shaderCode.data()));
		instance = _device.createShaderModule(shaderModuleCreateInfo);
	}

	VkShader::~VkShader()
	{
		device.destroyShaderModule(instance);
	}

	vk::Device VkShader::GetDevice() const
	{
		return device;
	}
	vk::ShaderModule VkShader::GetInstance() const
	{
		return instance;
	}

	vk::PipelineShaderStageCreateInfo VkShader::CreatePipelineStageCreateInfo(vk::ShaderStageFlagBits stage, const std::string& name, const vk::SpecializationInfo* info) const
	{
		return vk::PipelineShaderStageCreateInfo({}, stage, instance, name.c_str(), info);
	}
}
