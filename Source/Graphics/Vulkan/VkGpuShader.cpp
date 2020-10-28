#include "Injector/Graphics/Vulkan/VkGpuShader.hpp"
#include "Injector/Exception/NullException.hpp"

namespace Injector
{
	VkGpuShader::VkGpuShader(
		vk::Device _device,
		GpuShaderStage stage,
		const std::shared_ptr<ShaderData>& data) :
		GpuShader(stage),
		device(_device)
	{
		if(!_device)
		{
			throw NullException(
				THIS_FUNCTION_NAME,
				"device");
		}
		if(!data)
		{
			throw NullException(
				THIS_FUNCTION_NAME,
				"data");
		}

		auto shaderModuleCreateInfo = vk::ShaderModuleCreateInfo(
			vk::ShaderModuleCreateFlags(),
			data->code.size(),
			reinterpret_cast<const uint32_t*>(data->code.data()));
		auto result = device.createShaderModule(
			&shaderModuleCreateInfo,
			nullptr,
			&shaderModule);

		if (result != vk::Result::eSuccess)
		{
			throw Exception(
				THIS_FUNCTION_NAME,
				"Failed to create shader module");
		}
	}
	VkGpuShader::~VkGpuShader()
	{
		device.destroyShaderModule(
			shaderModule);
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
