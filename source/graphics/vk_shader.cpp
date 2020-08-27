#include <injector/graphics/vk_shader.hpp>
#include <stdexcept>

namespace INJECTOR_NAMESPACE
{
	VkShader::VkShader(
		const vk::Device& _device, 
		const std::vector<uint32_t>& code) :
		device(_device)
	{
		auto shaderModuleCreateInfo = vk::ShaderModuleCreateInfo(
			{}, code.size(), code.data());
		 auto result = device.createShaderModule(
			 &shaderModuleCreateInfo, nullptr, &shaderModule);

		if (result != vk::Result::eSuccess)
			throw std::runtime_error("Failed to create Vulkan shader module");
	}
	VkShader::VkShader(
		const vk::Device& _device,
		const std::vector<char>& code) :
		device(_device)
	{
		auto shaderModuleCreateInfo = vk::ShaderModuleCreateInfo(
			{}, code.size(), reinterpret_cast<const uint32_t*>(code.data()));
		auto result = device.createShaderModule(
			&shaderModuleCreateInfo, nullptr, &shaderModule);

		if (result != vk::Result::eSuccess)
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
}
