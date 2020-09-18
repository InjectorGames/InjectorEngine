#include "Injector/Graphics/VkGpuShader.hpp"
#include "Injector/Exception/Exception.hpp"

namespace Injector
{
	VkGpuShader::VkGpuShader(
		const vk::Device& _device, 
		const std::vector<uint32_t>& code) :
		device(_device)
	{
		auto shaderModuleCreateInfo = vk::ShaderModuleCreateInfo(
			{}, code.size(), code.data());
		 auto result = device.createShaderModule(
			 &shaderModuleCreateInfo, nullptr, &shaderModule);

		if (result != vk::Result::eSuccess)
			throw Exception("VkGpuShader", "VkGpuShader", "Failed to create shader module");
	}
	VkGpuShader::VkGpuShader(
		const vk::Device& _device,
		const std::vector<char>& code) :
		device(_device)
	{
		auto shaderModuleCreateInfo = vk::ShaderModuleCreateInfo(
			{}, code.size(), reinterpret_cast<const uint32_t*>(code.data()));
		auto result = device.createShaderModule(
			&shaderModuleCreateInfo, nullptr, &shaderModule);

		if (result != vk::Result::eSuccess)
			throw Exception("VkGpuShader", "VkGpuShader", "Failed to create shader module");
	}
	VkGpuShader::~VkGpuShader()
	{
		device.destroyShaderModule(shaderModule);
		device = nullptr;
	}

	vk::Device VkGpuShader::getDevice() const noexcept
	{
		return device;
	}
	vk::ShaderModule VkGpuShader::getShaderModule() const noexcept
	{
		return shaderModule;
	}
}
